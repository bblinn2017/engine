#ifndef BVH_H
#define BVH_H

#include "engine/util/CommonIncludes.h"
#include "spatialstructures.h"

struct bbox_t {
    glm::vec3 min;
    glm::vec3 max;

    bbox_t() {
        min = glm::vec3(1,1,1) * INFINITY;
        max = glm::vec3(1,1,1) * (-INFINITY);
    }

    bbox_t(glm::vec3 p) {
        min = p;
        max = p;
    }

    bbox_t(glm::vec3 bmin, glm::vec3 bmax) {
        min = bmin;
        max = bmax;
    }

    void expandToInclude(glm::vec3 p) {
        min = cmin(min,p);
        max = cmax(max,p);
    }

    void expandToInclude(glm::vec3 bmin, glm::vec3 bmax) {
        min = cmin(min,bmin);
        max = cmax(max,bmax);
    }

    int maxDimension() {
        int argmax = 0;
        float val = 0.;
        glm::vec3 extent = max - min;
        for (int i = 0; i < 3; i++) {
            if (extent[i] > val) {
                val = extent[i];
                argmax = i;
            }
        }
        return argmax;
    }

    bool intersect(glm::vec3 omin, glm::vec3 omax) {
        for (int i = 0; i < 3; i++) {
            if ((min[i] <= omax[i]) && (omin[i] <= max[i])) {continue;}
            return false;
        }
        return true;
    }

    float distance2(glm::vec3 p) {
        glm::vec3 vec = cmax(cmin(p,max),min) - p;
        return glm::dot(vec,vec);
    }

    glm::vec3 center() {
        return (min + max)/2.f;
    }
};

struct flatNode_t {
    bbox_t bbox;
    int start;
    int nPrims;
    int rightOffset;
};

struct buildEntry_t {
    char parent;
    int start;
    int end;
};

template <typename Collidable, typename CollSorter>
class BVH : public CollisionStructure<Collidable> {
public:
    BVH(bool dynamic) :
        CollisionStructure<Collidable>(dynamic)
    {
        m_flatTree = std::vector<flatNode_t>();
    }

    void build() override {
        m_nLeafs = 0;
        if (!this->m_spatials.size()) return;

        std::vector<buildEntry_t> todo;
        todo.reserve(128);

        int stackptr = 0;

        todo[stackptr].start = 0;
        todo[stackptr].end = this->m_spatials.size();
        todo[stackptr++].parent = ROOT;

        flatNode_t node;
        Collidable curr;
        glm::vec3 pos;

        buildEntry_t bnode;
        int start, end, mid, nPrims, split_dim;
        bbox_t bb, bc;

        while (stackptr > 0) {
            stackptr -= 1;
            bnode = todo[stackptr];
            start = bnode.start;
            end = bnode.end;
            nPrims = end - start;

            node.start = start;
            node.nPrims = nPrims;
            node.rightOffset = UNTOUCHED;

            curr = this->m_spatials[start];
            bb = {};
            bc = {};

            for (int k = start; k < end; k++) {
                curr = this->m_spatials[k];
                bb.expandToInclude(this->getMin(curr),this->getMax(curr));
                bc.expandToInclude(this->getPos(curr));
            }

            node.bbox = bb;

            if (nPrims <= LEAF_SIZE) {
                node.rightOffset = 0;
                m_nLeafs++;
            }

            m_flatTree.push_back(node);

            if (bnode.parent != ROOT) {
                m_flatTree[bnode.parent].rightOffset -= 1;
                if (m_flatTree[bnode.parent].rightOffset == TOUCHED_TWICE) {
                    m_flatTree[bnode.parent].rightOffset = m_flatTree.size() - 1 - bnode.parent;
                }
            }

            if (!node.rightOffset) {
                continue;
            }

            split_dim = bc.maxDimension();
            CollSorter comp = CollSorter(split_dim);
            std::sort(this->m_spatials.begin()+start,this->m_spatials.begin()+end,comp);

            mid = (start + end) / 2;

            todo[stackptr].start = mid;
            todo[stackptr].end = end;
            todo[stackptr].parent = m_flatTree.size() - 1;
            stackptr++;

            todo[stackptr].start = start;
            todo[stackptr].end = mid;
            todo[stackptr].parent = m_flatTree.size() - 1;
            stackptr++;
         }
    }

    std::vector<Collidable> intersectedCollidables(glm::vec3 bmin, glm::vec3 bmax) override {
        std::vector<Collidable> intersected;
        if (!m_flatTree.size()) return intersected;

        int todo[64];
        int stackptr = 0;

        todo[stackptr] = 0;

        int ni;
        flatNode_t node, n0, n1;
        Collidable obj;

        while (stackptr >= 0) {
            ni = todo[stackptr--];
            node = m_flatTree[ni];

            // If this is a leaf node
            if (!node.rightOffset) {
                for (int k = 0; k < node.nPrims; k++) {
                    obj = this->m_spatials[node.start+k];
                    bbox_t obj_bbox = bbox_t(this->getMin(obj),this->getMax(obj));

                    if (obj_bbox.intersect(bmin,bmax)) intersected.push_back(obj);
                }
            } else {
                n0 = m_flatTree[ni+1];
                n1 = m_flatTree[ni+node.rightOffset];

                if (n0.bbox.intersect(bmin,bmax)) {
                    todo[++stackptr] = ni+1;
                }
                if (n1.bbox.intersect(bmin,bmax)) {
                    todo[++stackptr] = ni+node.rightOffset;
                }
            }
        }

        return intersected;
    }

    Collidable closestCollidable(glm::vec3 p) {
        Collidable closest;
        float closest_distance = INFINITY;

        if (!m_flatTree.size()) return closest;

        int todo[64];
        int stackptr = 0;

        todo[stackptr] = 0;

        int ni;
        flatNode_t node, n0, n1;
        float d0, d1;
        Collidable obj;

        while (stackptr >= 0) {
            ni = todo[stackptr--];
            node = m_flatTree[ni];

            // If this is a leaf node
            if (!node.rightOffset) {
                for (int k = 0; k < node.nPrims; k++) {
                    obj = this->m_spatials[node.start+k];
                    float dist = glm::length(this->getPos(obj) - p);
                    if (dist < closest_distance) {
                        closest = obj;
                        closest_distance = dist;
                    }
                }
            } else {
                n0 = m_flatTree[ni+1];
                n1 = m_flatTree[ni+node.rightOffset];

                bool hit0 = n0.bbox.intersect(p,p);
                bool hit1 = n1.bbox.intersect(p,p);

                if (hit0) {
                    todo[++stackptr] = ni+1;
                }
                if (hit1) {
                    todo[++stackptr] = ni+node.rightOffset;
                }

                if (!hit0 && !hit1) {
                    d0 = n0.bbox.distance2(p);
                    d1 = n1.bbox.distance2(p);
                    todo[++stackptr] = (d0 < d1) ? ni+1 : ni+node.rightOffset;
                }
            }
        }
        return closest;
    }
private:
    int m_nLeafs;
    std::vector<flatNode_t> m_flatTree;
};

#endif // BVH_H
