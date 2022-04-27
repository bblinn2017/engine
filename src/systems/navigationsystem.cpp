#include "navigationsystem.h"

using namespace std;
using namespace glm;

NavigationSystem::NavigationSystem() {

}

void NavigationSystem::addGameObject(string key, shared_ptr<GameObject> o) {
   m_gameObjects[key] = o;
   m_mesh = o->getComponent<NavmeshComponent>();
}

void NavigationSystem::navigate(shared_ptr<GameObject> o, vec3 dest) {
    vec3 start = (*o->getComponent<TransformComponent>()->getPos());
    o->getComponent<NavigationComponent>()->setPath(m_mesh->genPath(start,dest));
}
