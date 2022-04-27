#include "movementcomponent.h"

using namespace std;
using namespace glm;

MovementComponent::MovementComponent(GameObject *gameObject) :
    Component(gameObject)
{
    m_transform = m_gameObject->getComponent<TransformComponent>();
    m_transform->setMovable();
    isMoving = false;
}

void MovementComponent::tick(float seconds) {
    vec3 *pos = m_transform->getPos();
    vec3 *oldPos = m_transform->getOldPos();
    vec3 *vel = m_transform->getVel();

    if (!onFrictionSurface) {
        vel->y += GRAVITY * seconds;
    } else if (isMoving) {
        vel->y = 0.;
    } else{
        *vel = glm::vec3(0,0,0);
        return;
    }

    if (!vel->length()) return;

    *oldPos = *pos;
    *pos += (*vel) * seconds;
}
