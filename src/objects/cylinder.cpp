#include "cylinder.h"

using namespace std;
using namespace glm;

Cylinder::Cylinder(float radius, float height) :
    Object(vec3(radius*2,height,radius*2)),
    m_radius(radius), m_height(height) {}

vec3 Cylinder::getMax() {
    return vec3(m_radius,m_height/2.f,m_radius);
}
vec3 Cylinder::getMin() {
    return vec3(-m_radius,-m_height/2.f,-m_radius);
}
glm::vec3 Cylinder::getOrigin() {
    return vec3(0,-m_height/2.,0);
}

bool Cylinder::hasFriction(glm::vec3 v) {
    vec3 norm_v = glm::vec3(v.x/m_radius,v.y/(m_height/2.f),v.z/m_radius);
    norm_v /= glm::length(norm_v);
    return norm_v.y < m_height / length(vec2(m_radius,m_height));
}

float Cylinder::getRadius() {return m_radius;}
float Cylinder::getHeight() {return m_height;}
