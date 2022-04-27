#include "part.h"

using namespace std;
using namespace glm;

Part::Part(int index) :
    m_index(index)
{
//    OBJLoader objLoader = OBJLoader();
//    std::string part_obj = MANSION_FOLDER + std::to_string(m_index) + ".obj";
//    m_objData = objLoader.loadOBJ(WORLD_FILE);
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

void Part::setDrawables() {
    // Shape
    std::string key = std::to_string(m_index);
    m_graphics->addShape(key,m_objData.positions,m_objData.normals,m_objData.uvs);
    // Texture
//    m_graphics->addTexture(key,MANSION_FOLDER + std::to_string(m_index) + ".png");
    m_graphics->addTexture(key,TEX_FILE);

    getComponent<DrawableComponent>()->addShape(key,
                                                key,
                                                true);
}
