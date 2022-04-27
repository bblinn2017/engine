#ifndef BEHAVIORTREE_H
#define BEHAVIORTREE_H

#include "engine/util/CommonIncludes.h"
#include "behaviortree/basicsbehaviortree.h"

class BehaviorTree {
public:
    BehaviorTree() {
        m_nodeMap = std::make_shared<NodeMap>();
    }

    status_t update(float seconds) {
        return nodeCastUpdate(m_nodeMap->getRoot(), seconds);
    }
protected:
    nodemap_p m_nodeMap;
};

#endif // BEHAVIORTREE_H
