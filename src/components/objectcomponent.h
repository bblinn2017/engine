#ifndef OBJECTCOMPONENT_H
#define OBJECTCOMPONENT_H

#include "common/component.h"
#include "common/gameobject.h"
#include "objects/basicobjects.h"

class ObjectComponent : public Component {
public:
    ObjectComponent(GameObject *gameObject, obj_type_t objType, std::shared_ptr<Object> obj);
    void tick(float seconds) override;
    glm::vec3 getMin(glm::vec3 pos);
    glm::vec3 getMax(glm::vec3 pos);
    glm::vec3 getScale();
    obj_type_t getType() {return m_type;}
    glm::vec3 getOrigin();

    template <typename ObjType>
    std::shared_ptr<ObjType> getObj() {
        return std::static_pointer_cast<ObjType>(m_object);
    }

private:
    obj_type_t m_type;
    std::shared_ptr<Object> m_object;
};

#endif // OBJECTCOMPONENT_H
