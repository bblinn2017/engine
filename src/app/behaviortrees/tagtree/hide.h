#ifndef HIDE_H
#define HIDE_H

#include "engine/util/CommonIncludes.h"
#include "behaviortree/basicsbehaviortree.h"
#include "common/gameobject.h"
#include "components/basiccomponents.h"
#include "isChasing.h"
#include "chase_hide.h"

class Hide : public ChaseHide {
public:
    Hide(nodemap_p nodeMap, std::shared_ptr<GameObject> o, std::shared_ptr<GameObject> navigable, std::string isChasingKey) :
        ChaseHide(nodeMap,o,navigable,isChasingKey)
    {
    }

    void swapRole() override {
        m_nodeMap->getNode<isChasing>(m_isChasingKey)->setTagging(true);
    }

    glm::vec3 getStart() override {
        return m_o->getComponent<TransformComponent>()->getBase();
    }

    glm::vec3 getEnd() override {
        glm::vec3 start = m_o->getComponent<TransformComponent>()->getBase();
        glm::vec3 end = m_target->getComponent<TransformComponent>()->getBase();
        return start + (start - end) / glm::length(start - end) * 10.f;
    }

    status_t collisionStatus() override {
        return FAIL;
    }
};

#endif // HIDE_H
