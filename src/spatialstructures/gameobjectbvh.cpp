#include "gameobjectbvh.h"

using namespace std;
using namespace glm;

GameObjectBVH::GameObjectBVH(bool dynamic) :
    BVH<shared_ptr<GameObject>,GameObjectComparator>(dynamic)
{

}

vector<shared_ptr<GameObject>> GameObjectBVH::intersectedGameObjects(shared_ptr<GameObject> o) {
    std::shared_ptr<TransformComponent> transform = o->getComponent<TransformComponent>();

    vec3 bmin = transform->getMin();
    vec3 bmax = transform->getMax();
    return intersectedCollidables(bmin,bmax);
}

vec3 GameObjectBVH::getMin(shared_ptr<GameObject> o) {
    std::shared_ptr<TransformComponent> transform = o->getComponent<TransformComponent>();
    return transform->getMin();
}

vec3 GameObjectBVH::getMax(shared_ptr<GameObject> o) {
    std::shared_ptr<TransformComponent> transform = o->getComponent<TransformComponent>();
    return transform->getMax();
}

vec3 GameObjectBVH::getPos(shared_ptr<GameObject> o) {
    std::shared_ptr<TransformComponent> transform = o->getComponent<TransformComponent>();
    return *(transform->getPos());
}
