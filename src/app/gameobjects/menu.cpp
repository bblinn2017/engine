#include "menu.h"

using namespace std;
using namespace glm;

Menu::Menu() {
    shared_ptr<Object> obj = static_pointer_cast<Object>(make_shared<Complex>(vec3(1,1,1)));

    // Components
    addComponent(make_shared<ObjectComponent>(this,COMPLEX,obj));
    addComponent(make_shared<TransformComponent>(this,vec3()));
    addComponent(make_shared<DrawableComponent>(this));
}

void Menu::setDrawables() {
    // Shape
    auto shape = "uiquad";
    // Material
    m_graphics->setDefaultMaterial();
    Material mat = m_graphics->getActiveMaterial();
    mat.color = vec3(0.5,0.5,0.5);
    m_graphics->addMaterial("menu",mat);

    getComponent<DrawableComponent>()->addShape(shape,
                                                "menu",
                                                false);
}
