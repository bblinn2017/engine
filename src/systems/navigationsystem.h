#ifndef NAVIGATIONSYSTEM_H
#define NAVIGATIONSYSTEM_H

#include "engine/util/CommonIncludes.h"
#include "common/system.h"
#include "components/navmeshcomponent.h"
#include "components/navigationcomponent.h"
#include "components/transformcomponent.h"

class NavigationSystem : public System {
public:
    NavigationSystem();

    void addGameObject(std::string key, std::shared_ptr<GameObject> o);
    void navigate(std::shared_ptr<GameObject> o, glm::vec3 dest);

private:
    std::shared_ptr<NavmeshComponent> m_mesh;
};

#endif // NAVIGATIONSYSTEM_H
