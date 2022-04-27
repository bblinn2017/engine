#include "player.h"

using namespace std;
using namespace glm;

Player::Player(shared_ptr<Input> input, shared_ptr<Camera> camera)
{
    shared_ptr<Object> obj = static_pointer_cast<Object>(make_shared<Cylinder>(PLAYER_RADIUS,PLAYER_HEIGHT));
    // Make Components
    vec3 transl(0,PLAYER_HEIGHT/2.f+EPSILON,0);

    addComponent(make_shared<ObjectComponent>(this,CYLINDER,obj));
    addComponent(make_shared<TransformComponent>(this,transl));
    addComponent(make_shared<CameraComponent>(this,camera,input));
    addComponent(make_shared<DrawableComponent>(this));
    addComponent(make_shared<MovementComponent>(this));
    addComponent(make_shared<ObjCollisionComponent>(this));
    addComponent(make_shared<PlayerControlComponent>(this,input));
}

void Player::setDrawables() {
    // Shape
    auto shape = "cylinder";
    // Material
    m_graphics->setDefaultMaterial();
    Material mat = m_graphics->getActiveMaterial();
    mat.color = vec3(1,0,0);
    m_graphics->addMaterial("player",mat);

    getComponent<DrawableComponent>()->addShape(shape,
                                                "player",
                                                false);
}
