#include "drawsystem.h"

using namespace std;
using namespace glm;

DrawSystem::DrawSystem() {

}

void DrawSystem::draw() {
    for (auto i : m_gameObjects) {
        auto gO = i.second;
        if (gO->containsComponent<DrawableComponent>()) {
            gO->getComponent<DrawableComponent>()->draw();
        }
    }
}
