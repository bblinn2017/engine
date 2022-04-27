#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "common/component.h"
#include "common/gameobject.h"
#include "transformcomponent.h"

class MovementComponent : public Component {
public:
    MovementComponent(GameObject *gameObject);
    void tick(float seconds) override;
    float getMax() {return m_transform->getMax().y;}
    float getMin() {return m_transform->getMin().y;}

    void noFriction() {onFrictionSurface = false;}
    void friction() {onFrictionSurface = true;}
    void moving() {isMoving = true;}
    void noMoving() {isMoving = false;}
    bool canMove() {return onFrictionSurface;}
private:
    std::shared_ptr<TransformComponent> m_transform;
    bool onFrictionSurface;
    bool isMoving;
};

#endif // MOVEMENTCOMPONENT_H
