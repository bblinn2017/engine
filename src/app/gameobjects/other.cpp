#include "other.h"

using namespace std;
using namespace glm;

Other::Other() {
    shared_ptr<Object> obj = static_pointer_cast<Object>(make_shared<Cylinder>(SCALE/2.,SCALE));

    // Make Components
    vec3 transl(10.,SCALE/2.f+3.+EPSILON,0.);

    addComponent(make_shared<ObjectComponent>(this,CYLINDER,obj));
    addComponent(make_shared<TransformComponent>(this,transl));
    addComponent(make_shared<DrawableComponent>(this));
    addComponent(make_shared<MovementComponent>(this));
    addComponent(make_shared<ObjCollisionComponent>(this));
    addComponent(make_shared<NavigationComponent>(this));
}

void Other::setDrawables() {
    // Shape
    auto shape = "cylinder";
    // Add material
    m_graphics->setDefaultMaterial();
    Material mat = m_graphics->getActiveMaterial();
    mat.color = vec3(0,0,1);
    m_graphics->addMaterial("other",mat);

    getComponent<DrawableComponent>()->addShape(shape,
                                                "other",
                                                false);
}
