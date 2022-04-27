#ifndef TRIBVH_H
#define TRIBVH_H

#include "engine/util/CommonIncludes.h"
#include "spatialstructures/bvh.h"
#include "common/triangle.h"

class TriComparator {
public:
    TriComparator(int split_dim) : m_dim(split_dim) {}
    bool operator()(std::shared_ptr<tri_t> &x, std::shared_ptr<tri_t> &y) {
        return x->pos()[m_dim] < y->pos()[m_dim];
    }
private:
    int m_dim;
};

class TriBVH : public BVH<std::shared_ptr<tri_t>,TriComparator> {
public:
    TriBVH(std::vector<std::shared_ptr<tri_t>> tris);

    glm::vec3 getPos(std::shared_ptr<tri_t> o) override;
    glm::vec3 getMin(std::shared_ptr<tri_t> o) override;
    glm::vec3 getMax(std::shared_ptr<tri_t> o) override;
};

#endif // TRIBVH_H
