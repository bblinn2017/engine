#ifndef COMPONENT_H
#define COMPONENT_H

#include "engine/util/CommonIncludes.h"

class GameObject;

class Component {
public:
    Component(GameObject *gameObject);

    virtual void tick(float seconds);
    virtual void setGraphics(Graphics * graphics);
protected:
    GameObject *m_gameObject;
};

#endif // COMPONENT_H
