#include "objectcomponent.h"

using namespace std;
using namespace glm;

ObjectComponent::ObjectComponent(GameObject *gameObject, obj_type_t objType, shared_ptr<Object> obj) :
    Component(gameObject),
    m_type(objType),
    m_object(obj)
{

}

void ObjectComponent::tick(float seconds) {}

vec3 ObjectComponent::getMin(glm::vec3 pos) {
    vec3 min;

    switch(m_type) {
    case CYLINDER:
        min = getObj<Cylinder>()->getMin();
        break;
    case COMPLEX:
        min = getObj<Complex>()->getMin();
        break;
    }
    return pos + min;
}

vec3 ObjectComponent::getMax(glm::vec3 pos) {
    vec3 max;

    switch(m_type) {
    case CYLINDER:
        max = getObj<Cylinder>()->getMax();
        break;
    case COMPLEX:
        max = getObj<Complex>()->getMax();
        break;
    }
    return pos + max;
}

vec3 ObjectComponent::getScale() {
    vec3 scale;

    switch(m_type) {
    case CYLINDER:
        scale = getObj<Cylinder>()->getScale();
        break;
    case COMPLEX:
        scale = getObj<Complex>()->getScale();
        break;
    }
    return scale;
}

vec3 ObjectComponent::getOrigin() {
    vec3 origin;

    switch(m_type) {
    case CYLINDER:
        origin = getObj<Cylinder>()->getOrigin();
        break;
    case COMPLEX:
        origin = getObj<Complex>()->getOrigin();
        break;
    }
    return origin;
}
