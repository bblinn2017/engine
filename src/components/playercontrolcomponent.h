#ifndef PLAYERCONTROLCOMPONENT_H
#define PLAYERCONTROLCOMPONENT_H

#include "engine/util/CommonIncludes.h"
#include "common/component.h"
#include "common/gameobject.h"

#include "components/objectcomponent.h"
#include "components/transformcomponent.h"
#include "components/movementcomponent.h"
#include "components/cameracomponent.h"

class PlayerControlComponent : public Component {
public:
    PlayerControlComponent(GameObject *gameObject, std::shared_ptr<Input> input);
    void tick(float seconds) override;
    bool canMove() {return m_move->canMove();}
private:
    std::shared_ptr<Input> m_input;
    std::shared_ptr<TransformComponent> m_transform;
    std::shared_ptr<ObjectComponent> m_obj;
    std::shared_ptr<CameraComponent> m_cam;
    std::shared_ptr<MovementComponent> m_move;
};

#endif // PLAYERCONTROLCOMPONENT_H
