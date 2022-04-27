#include "system.h"

using namespace std;
using namespace glm;

System::System() {

}

void System::addGameObject(std::string key, std::shared_ptr<GameObject> o) {
    m_gameObjects[key] = o;
}

void System::removeGameObject(std::string key) {
    if (m_gameObjects.find(key) != m_gameObjects.end()) m_gameObjects.erase(key);
}
