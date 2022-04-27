#include "playercontrolcomponent.h"

using namespace std;
using namespace glm;

PlayerControlComponent::PlayerControlComponent(GameObject *gameObject, shared_ptr<Input> input) :
    Component(gameObject),
    m_input(input)
{
    m_transform = m_gameObject->getComponent<TransformComponent>();
    m_obj = m_gameObject->getComponent<ObjectComponent>();
    m_cam = m_gameObject->getComponent<CameraComponent>();
    m_move = m_gameObject->getComponent<MovementComponent>();
}

void PlayerControlComponent::tick(float seconds) {
    // Change First/Third Person
    if (m_input->isKeyActive(Qt::Key_F)) {
        m_input->keyDeactivate(Qt::Key_F);
        m_cam->switchPerspective();
    }

    // Jump
    if (m_input->isKeyActive(Qt::Key_Space)) {
        if (canMove()) m_transform->getVel()->y = MOVE;
    }
    else {
        if (canMove() || STRAFING) {
            vec3 look = m_cam->getLook();
            vec3 perp = cross(look,m_cam->getUp());
            vec3 *vel = m_transform->getVel();
            vel->x = 0.; vel->z = 0;
            look.y = 0; perp.y = 0;

            m_move->noMoving();
            if (m_input->isKeyActive(Qt::Key_W)) {*vel += look * MOVE; m_move->moving();}
            if (m_input->isKeyActive(Qt::Key_S)) {*vel -= look * MOVE; m_move->moving();}
            if (m_input->isKeyActive(Qt::Key_D)) {*vel += perp * MOVE; m_move->moving();}
            if (m_input->isKeyActive(Qt::Key_A)) {*vel -= perp * MOVE; m_move->moving();}
        }
    }
}
