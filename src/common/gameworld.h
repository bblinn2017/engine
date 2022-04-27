#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "engine/util/CommonIncludes.h"
#include "gameobject.h"
#include "system.h"

class GameWorld {
public:
    GameWorld();

    void addGameObject(std::string key, std::shared_ptr<GameObject> o) {
        m_gameObjects[key] = o;
    }
    bool containsGameObject(std::string key) {return m_gameObjects.find(key) != m_gameObjects.end();}

    template <typename Type>
    std::shared_ptr<Type> getGameObject(std::string key) {
        return std::static_pointer_cast<Type>(m_gameObjects[key]);
    }

    void removeGameObject(std::string key) {
        m_gameObjects.erase(key);
        for (auto s : m_systems) {
            s.second->removeGameObject(key);
        }
    }

    template <typename Type>
    void addSystem(std::shared_ptr<Type> &&s) {
        m_systems.put<Type>(std::forward<std::shared_ptr<Type>>(s));
    }
    template <typename Type>
    void removeSystem() {
        m_systems.remove<Type>();
    }
    template <typename Type>
    std::shared_ptr<Type> getSystem() {
        return std::static_pointer_cast<Type>(m_systems.find<Type>()->second);
    }

    void setGraphics(Graphics * graphics);
protected:
    std::map<std::string,std::shared_ptr<GameObject>> m_gameObjects;
    TypeMap<std::shared_ptr<System>> m_systems;
};

#endif // GAMEWORLD_H
