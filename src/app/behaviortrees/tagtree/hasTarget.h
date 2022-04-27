#ifndef HASTARGET_H
#define HASTARGET_H

#include "engine/util/CommonIncludes.h"
#include "behaviortree/basicsbehaviortree.h"
#include "chase.h"

class hasTarget : public Condition {
public:
    hasTarget(nodemap_p nodeMap, std::string chaseKey) : Condition(nodeMap) {
        m_chaseKey = chaseKey;
    }

    status_t determine() override {
        if (m_nodeMap->getNode<Chase>(m_chaseKey)->hasTarget()) return SUCCESS;
        return FAIL;
    }

    void reset() override {
    }
private:
    std::string m_chaseKey;
};

#endif // HASTARGET_H
