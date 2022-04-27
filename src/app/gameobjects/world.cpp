#include "world.h"
#include <QFile>

using namespace std;
using namespace glm;

World::World()
{
    OBJLoader objLoader = OBJLoader();
    m_objData = objLoader.loadOBJ(WORLD_FILE);

    objData obj_data = processData(m_objData.positions);
    shared_ptr<Object> obj = static_pointer_cast<Object>(make_shared<Complex>(obj_data));

    // Add Components
    addComponent(make_shared<ObjectComponent>(this,COMPLEX,obj));
    addComponent(make_shared<NavmeshComponent>(this,obj_data));
    addComponent(make_shared<TransformComponent>(this,vec3()));
    addComponent(make_shared<DrawableComponent>(this));
    addComponent(make_shared<ObjCollisionComponent>(this));
}

void World::setDrawables() {
    // Shape
    m_graphics->addShape("level",m_objData.positions,m_objData.normals,m_objData.uvs);
    // Texture
    m_graphics->addTexture("level",TEX_FILE);

    getComponent<DrawableComponent>()->addShape("level",
                                                "level",
                                                true);
}
