#include "cameracomponent.h"

using namespace std;
using namespace glm;

CameraComponent::CameraComponent(GameObject *gameObject, shared_ptr<Camera> camera, shared_ptr<Input> input) :
   Component(gameObject),
   isChanging(false),
   changeT(0.f),
   isFirstPerson(true),
   m_input(input),
   m_camera(camera)
{
    m_transform = m_gameObject->getComponent<TransformComponent>();
    m_obj = m_gameObject->getComponent<ObjectComponent>();
}

void CameraComponent::tick(float seconds) {
    // Change Look
    vec2 delta = m_input->getMouseDelta();
    int deltaX = delta.x - m_input->getWidth() / 2;
    int deltaY = delta.y - m_input->getHeight() / 2;

    if (deltaX != 0 || deltaY != 0) {
        rotate(deltaX / 100.f, deltaY / 100.f);
    }
    m_input->setMouseDelta(glm::vec2(m_input->getWidth()/2,m_input->getHeight()/2));

    m_camera->setEye(getPovEye(changeT));
    if (!isChanging) return;

    changeT += (isFirstPerson) ? -seconds : seconds;
    // Set Eye
    if (changeT >= 1.) {
        isChanging = false; changeT = 1.;
    }
    else if (changeT <= 0.) {
        isChanging = false; changeT = 0.;
    }
}

void CameraComponent::rotate(float dYaw, float dPitch) {
    if (dYaw == 0.f && dPitch == 0.f) return;
    m_camera->rotate(-dYaw,-dPitch);

    vec3 posToEye = getPovEye(changeT) - *m_transform->getPos();
    float angle = glm::sqrt(dYaw * dYaw + dPitch * dPitch);
    vec3 rot = vec3(dPitch,dYaw,0.f);
    rot /= glm::length(rot);

    vec4 temp = (glm::rotate(angle,rot) * glm::vec4(posToEye,0));
    vec3 newPosToEye = vec3(temp.x,temp.y,temp.z);

    m_camera->setEye(*m_transform->getPos() + newPosToEye);
}

void CameraComponent::switchPerspective() {
    isFirstPerson = !isFirstPerson;
    isChanging = true;
}

vec3 CameraComponent::getPovEye(float t) {
    vec3 eye = vec3(*(m_transform->getPos()));
    eye = eye - t * getPovTransl();
    return eye;
}
