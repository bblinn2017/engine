#include "gameobject.h"

using namespace std;
using namespace glm;

GameObject::GameObject()
{
}

void GameObject::setGraphics(Graphics * graphics) {
    m_graphics = graphics;
    for (auto c : m_components) {
        c.second->setGraphics(graphics);
    }
    setDrawables();
}
