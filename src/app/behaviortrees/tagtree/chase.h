#ifndef CHASE_H
#define CHASE_H

#include "engine/util/CommonIncludes.h"
#include "behaviortree/basicsbehaviortree.h"
#include "common/gameobject.h"
#include "components/basiccomponents.h"
#include "isChasing.h"
#include "chase_hide.h"
#include "hide.h"

class Chase : public ChaseHide {
public:
    Chase(nodemap_p nodeMap, std::shared_ptr<GameObject> o, std::shared_ptr<GameObject> navigable, std::string isChasingKey, std::string hideKey) :
        ChaseHide(nodeMap,o,navigable,isChasingKey)
    {
        m_hideKey = hideKey;
    }

    void swapRole() override {
        m_nodeMap->getNode<isChasing>(m_isChasingKey)->setTagging(false);
        m_nodeMap->getNode<Hide>(m_hideKey)->setTarget(m_target);
    }

    glm::vec3 getStart() override {
        return m_o->getComponent<TransformComponent>()->getBase();
    }

    glm::vec3 getEnd() override {
        return m_target->getComponent<TransformComponent>()->getBase();
    }

    status_t collisionStatus() override {
        return SUCCESS;
    }

private:
    std::string m_hideKey;
};

#endif // CHASE_H
