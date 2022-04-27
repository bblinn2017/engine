#ifndef PICKTARGET_H
#define PICKTARGET_H

#include "engine/util/CommonIncludes.h"
#include "behaviortree/basicsbehaviortree.h"
#include "common/gameobject.h"
#include "components/basiccomponents.h"
#include "chase.h"

class pickTarget : public Action {
public:
    pickTarget(nodemap_p nodeMap, std::vector<std::shared_ptr<GameObject>> targets, std::string chaseKey) : Action(nodeMap) {
        m_targets = targets;
        m_chaseKey = chaseKey;
    }

    status_t determine(float seconds) override {
        std::shared_ptr<GameObject> target = m_targets[std::rand() % m_targets.size()];
        m_nodeMap->getNode<Chase>(m_chaseKey)->setTarget(target);
        return SUCCESS;
    }
    void reset() override {

    }
private:
    std::vector<std::shared_ptr<GameObject>> m_targets;
    std::string m_chaseKey;
};

#endif // PICKTARGET_H
