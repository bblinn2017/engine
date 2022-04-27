#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "engine/util/CommonIncludes.h"
#include "component.h"

class GameObject {
public:
    GameObject();

    template <typename Type>
    void addComponent(std::shared_ptr<Type> &&s) {
        m_components.put<Type>(std::forward<std::shared_ptr<Type>>(s));
    }
    template <typename Type>
    void removeComponent() {
        m_components.remove<Type>();
    }
    template <typename Type>
    std::shared_ptr<Type> getComponent() {
        return std::static_pointer_cast<Type>(m_components.find<Type>()->second);
    }

    template <typename Type>
    bool containsComponent() {
        return m_components.find<Type>() != m_components.end();
    }

    TypeMap<std::shared_ptr<Component>> getComponents() {
        return m_components;
    }

    void setGraphics(Graphics * graphics);
    virtual void setDrawables() {};
protected:
    TypeMap<std::shared_ptr<Component>> m_components;
    Graphics *m_graphics;
};

#endif // GAMEOBJECT_H
