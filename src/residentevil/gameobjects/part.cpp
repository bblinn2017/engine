#include "part.h"

using namespace std;
using namespace glm;

Part::Part(int index) :
    m_index(index)
{
    OBJLoader objLoader = OBJLoader();
    std::string part_obj = MANSION_FOLDER + std::to_string(m_index) + ".obj";
    m_objData = objLoader.loadOBJ(part_obj.c_str());

    // Add Normals
    for (int i = 0; i < m_objData.positions.size(); i+=9) {
        vec3 v0, v1, v2;
        for (int j = 0; j < 3; j++) {
            v0[j] = m_objData.positions[i+j];
            v1[j] = m_objData.positions[i+3+j];
            v2[j] = m_objData.positions[i+6+j];
        }
        vec3 n = glm::cross(v2-v1,v1-v0);
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) m_objData.normals.push_back(n[k]);
        }
    }

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
    m_graphics->addTexture(key,MANSION_FOLDER + std::to_string(m_index) + ".png");

    getComponent<DrawableComponent>()->addShape(key,
                                                key,
                                                true);
}
