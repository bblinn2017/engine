#ifndef CYLINDER_H
#define CYLINDER_H

#include "engine/util/CommonIncludes.h"
#include "objects.h"

class Cylinder : public Object {
public:
    Cylinder(float radius, float height);

    glm::vec3 getMax() override;
    glm::vec3 getMin() override;
    glm::vec3 getOrigin() override;

    bool hasFriction(glm::vec3 v);

    float getRadius();
    float getHeight();
private:
    float m_radius;
    float m_height;
};

#endif // CYLINDER_H
