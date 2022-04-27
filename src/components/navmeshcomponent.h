#ifndef NAVMESHCOMPONENT_H
#define NAVMESHCOMPONENT_H

#include "engine/util/CommonIncludes.h"
#include "common/gameobject.h"
#include "common/triangle.h"
#include "spatialstructures/tribvh.h"

inline float dist(tri_p a, tri_p b) {
    glm::vec3 vec = a->pos() - b->pos();
    return glm::dot(vec,vec);
}

typedef std::unordered_set<glm::vec3,vecFuncs,vecFuncs> vecSet;

inline glm::vec3 midpointEdge(tri_p a, tri_p b) {
    glm::vec3 vec = glm::vec3();
    vecSet a_set(a->positions.begin(),a->positions.end());
    for (auto b: b->positions) {
        if (a_set.find(b) != a_set.end()) {
            vec += b / 2.f;
        }
    }
    return vec;
}

class NavmeshComponent : public Component {
public:
    NavmeshComponent(GameObject *gameObject, objData obj);

    void buildGraph(objData obj);

    std::map<tri_p,tri_p> genNodes(tri_p start_tri, tri_p end_tri, tri_p &closest);
    std::vector<glm::vec3> genPath(glm::vec3 start, glm::vec3 end);
private:
    std::shared_ptr<TriBVH> m_triBVH;
    std::map<tri_p,std::set<tri_p>> m_faceMap;
};

#endif // NAVMESHCOMPONENT_H
