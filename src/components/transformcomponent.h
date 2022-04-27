#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "common/component.h"
#include "common/gameobject.h"
#include "objectcomponent.h"

class TransformComponent : public Component {
public:
    TransformComponent(GameObject *gameObject, glm::vec3 pos);

    void tick(float seconds) override;

    glm::vec3 * getVel() {return &vel;}
    glm::vec3 * getPos() {return &pos;}
    glm::vec3 * getOldPos() {return &oldPos;}

    glm::vec3 getMin() {return m_obj->getMin(pos);}
    glm::vec3 getMax() {return m_obj->getMax(pos);}

    glm::vec3 getBase() {
        glm::vec3 *pos = getPos();
        glm::vec3 min = getMin();
        return glm::vec3(pos->x,min.y,pos->z);
    }

    void setMovable() {m_movable = true;}
    bool isMovable() {return m_movable;}
private:
    glm::vec3 pos;
    glm::vec3 oldPos;
    glm::vec3 vel;
    std::shared_ptr<ObjectComponent> m_obj;
    bool m_movable;
};

#endif // TRANSFORMCOMPONENT_H
