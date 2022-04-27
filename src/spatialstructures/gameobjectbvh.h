#ifndef GAMEOBJECTBVH_H
#define GAMEOBJECTBVH_H

#include "spatialstructures/bvh.h"
#include "components/transformcomponent.h"

class GameObjectComparator {
public:
    GameObjectComparator(int split_dim) : m_dim(split_dim) {}
    bool operator()(const std::shared_ptr<GameObject> &x, const std::shared_ptr<GameObject> &y) {
        std::shared_ptr<TransformComponent> t_x = x->getComponent<TransformComponent>();
        std::shared_ptr<TransformComponent> t_y = y->getComponent<TransformComponent>();
        return (*(t_x->getPos()))[m_dim] < (*(t_y->getPos()))[m_dim];
    }
private:
    int m_dim;
};

class GameObjectBVH : public BVH<std::shared_ptr<GameObject>,GameObjectComparator> {
public:
    GameObjectBVH(bool dynamic);
    std::vector<std::shared_ptr<GameObject>> intersectedGameObjects(std::shared_ptr<GameObject> o);

    glm::vec3 getPos(std::shared_ptr<GameObject> o) override;
    glm::vec3 getMin(std::shared_ptr<GameObject> o) override;
    glm::vec3 getMax(std::shared_ptr<GameObject> o) override;
};

#endif // GAMEOBJECTBVH_H
