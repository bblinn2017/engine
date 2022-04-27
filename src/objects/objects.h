#ifndef OBJECTS_H
#define OBJECTS_H

#include "engine/util/CommonIncludes.h"
#include "spatialstructures/tribvh.h"

class Object {
public:
    Object(glm::vec3 scale) : m_scale(scale) {}

    virtual glm::vec3 getMax() {return glm::vec3();};
    virtual glm::vec3 getMin() {return glm::vec3();};
    virtual glm::vec3 getOrigin() {return glm::vec3();}
    glm::vec3 getScale() {return m_scale;}
private:
    glm::vec3 m_scale;
};

#endif // OBJECTS_H
