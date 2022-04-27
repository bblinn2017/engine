#include "drawcomponent.h"

using namespace std;
using namespace glm;

DrawableComponent::DrawableComponent(GameObject *gameObject) :

    Component(gameObject)
{
    m_transform = m_gameObject->getComponent<TransformComponent>();
    m_obj = m_gameObject->getComponent<ObjectComponent>();
}

void DrawableComponent::tick(float seconds) {

}

void DrawableComponent::draw() {
    // Material
    if (!m_hasTex) {
        m_graphics->setMaterial(m_matKey);
    } else {
        m_graphics->setTexture(m_matKey);
    }
    m_graphics->setUseTexture(m_hasTex);
    // Transform
    m_graphics->clearTransform();

    m_graphics->translate(*(m_transform->getPos()) + m_obj->getOrigin());
    m_graphics->scale(m_obj->getScale());
    // Draw Shape
    m_graphics->drawShape(m_shapeKey);
    m_graphics->clearTransform();
}

void DrawableComponent::setGraphics(Graphics *graphics) {
    m_graphics = graphics;
}
