#ifndef DRAWCOMPONENT_H
#define DRAWCOMPONENT_H

#include "common/component.h"
#include "common/gameobject.h"
#include "objectcomponent.h"
#include "transformcomponent.h"

class DrawableComponent : public Component {
public:
    DrawableComponent(GameObject *gameObject);
    void tick(float seconds) override;
    void setGraphics(Graphics *graphics) override;
    void draw();

    void addShape(std::string shapekey, std::string matkey, bool hasTex) {
        m_shapeKey = shapekey;
        m_matKey = matkey;
        m_hasTex = hasTex;
    }

private:
    Graphics *m_graphics;
    std::string m_shapeKey;
    std::string m_matKey;
    bool m_hasTex;
    std::shared_ptr<TransformComponent> m_transform;
    std::shared_ptr<ObjectComponent> m_obj;
};

#endif // DRAWCOMPONENT_H
