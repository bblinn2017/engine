#include "ticksystem.h"

using namespace std;
using namespace glm;

TickSystem::TickSystem() {

}

void TickSystem::tick(float seconds) {
    for (auto i : m_gameObjects) {
        for (auto j : i.second->getComponents()) {
            j.second->tick(seconds);
        }
    }
}
