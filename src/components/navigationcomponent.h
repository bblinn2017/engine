#ifndef NAVIGATIONCOMPONENT_H
#define NAVIGATIONCOMPONENT_H

#include "engine/util/CommonIncludes.h"
#include "common/gameobject.h"
#include "components/transformcomponent.h"

class NavigationComponent : public Component {
public:
    NavigationComponent(GameObject * o);

    void setPath(std::vector<glm::vec3> path);
    void tick(float seconds) override;

    void checkpoint();
private:
    bool pathSet;
    std::vector<glm::vec3> m_path;
    std::shared_ptr<TransformComponent> m_transform;
};

#endif // NAVIGATIONCOMPONENT_H
