#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "engine/util/CommonIncludes.h"

struct tri_t {
    std::vector<glm::vec3> positions;
    glm::vec3 normal;
    bool friction;

    tri_t() {}

    tri_t(std::vector<glm::vec3> ps) {
        positions = ps;
        normal = glm::cross(ps[1]-ps[0],ps[2]-ps[0]);
        normal /= glm::length(normal);
        friction = normal.y > 0.f;
    }

    glm::vec3 pos() {
        return (positions[0] + positions[1] + positions[2]) / 3.f;
    }

    glm::vec3 min() {
        return cmin(positions[0],cmin(positions[1],positions[2]));
    }

    glm::vec3 max() {
        return cmax(positions[0],cmax(positions[1],positions[2]));
    }
};
typedef std::shared_ptr<tri_t> tri_p;

struct objData {
    std::vector<std::shared_ptr<tri_t>> tris;
    std::vector<std::set<int>> faceMap;
    glm::vec3 min;
    glm::vec3 max;
};

typedef std::unordered_map<glm::vec3,int,vecFuncs,vecFuncs> vecMap;

inline objData processData(std::vector<float> positions) {
    objData obj;

    obj.min = glm::vec3(INFINITY,INFINITY,INFINITY);
    obj.max = -glm::vec3(INFINITY,INFINITY,INFINITY);

    std::vector<std::shared_ptr<tri_t>> tris;

    vecMap vMap;
    std::map<std::pair<int,int>,std::pair<int,int>> eToFMap;

    for (int i = 0; i < positions.size(); i+=9) {
        std::vector<glm::vec3> ps(3);
        for (int j = 0; j < 9; j++) {
            ps[j/3][j%3] = positions[i+j];

            obj.min[j%3] = std::min(positions[i+j],obj.min[j%3]);
            obj.max[j%3] = std::max(positions[i+j],obj.max[j%3]);
        }
        for (int j = 0; j < 3; j++) {
            if (vMap.find(ps[j]) == vMap.end()) vMap[ps[j]] = vMap.size();
        }
        for (int j = 0; j < 3; j++) {
            int a = vMap[ps[j]];
            int b = vMap[ps[(j+1)%3]];
            std::pair<int,int> key = std::pair<int,int>(std::min(a,b),std::max(a,b));
            if (eToFMap.find(key) == eToFMap.end()) {
                eToFMap[key] = std::pair<int,int>(i / 9,-1);
            } else {
                eToFMap[key].second = i / 9;
            }
        }
        obj.tris.push_back(std::make_shared<tri_t>(ps));
    }

    obj.faceMap = std::vector<std::set<int>>(obj.tris.size());

    for (auto i : eToFMap) {
        auto p = i.second;
        if (p.first < 0 || p.second < 0) continue;
        obj.faceMap[p.first].emplace(p.second);
        obj.faceMap[p.second].emplace(p.first);
    }

    return obj;
}

#endif // TRIANGLE_H
