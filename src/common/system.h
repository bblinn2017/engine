#ifndef SYSTEM_H
#define SYSTEM_H

#include "engine/util/CommonIncludes.h"
#include "gameobject.h"

class System {
public:
    System();

    virtual void addGameObject(std::string key, std::shared_ptr<GameObject> o);
    virtual void removeGameObject(std::string key);
protected:
    std::map<std::string,std::shared_ptr<GameObject>> m_gameObjects;
};

#endif // SYSTEM_H
