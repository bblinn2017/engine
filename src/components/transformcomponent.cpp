#include "transformcomponent.h"

using namespace std;
using namespace glm;

TransformComponent::TransformComponent(GameObject *gameObject, vec3 pos) :
    Component(gameObject),
    pos(pos),
    oldPos(pos),
    vel(),
    m_movable(false)
{
    m_obj = m_gameObject->getComponent<ObjectComponent>();
}

void TransformComponent::tick(float seconds) {

}
