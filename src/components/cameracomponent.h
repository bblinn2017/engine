#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "common/component.h"
#include "common/gameobject.h"
#include "components/objectcomponent.h"
#include "components/transformcomponent.h"

class CameraComponent : public Component {
public:
    CameraComponent(GameObject *gameObject, std::shared_ptr<Camera> camera, std::shared_ptr<Input> input);
    void tick(float seconds) override;

    void rotate(float dX, float dY);
    glm::vec3 getLook() {return m_camera->getLook();}
    glm::vec3 getUp() {return m_camera->getUp();}
    glm::vec3 getPovEye(float t);
    glm::vec3 getPovTransl() {return CAMERA_M*m_camera->getLook();}

    void switchPerspective();

private:
    // Flowing perspective switching
    bool isChanging;
    float changeT;

    bool isFirstPerson;
    std::shared_ptr<Input> m_input;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<TransformComponent> m_transform;
    std::shared_ptr<ObjectComponent> m_obj;
};

#endif // CAMERACOMPONENT_H
