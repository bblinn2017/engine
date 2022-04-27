#ifndef ISCHASING_H
#define ISCHASING_H

#include "engine/util/CommonIncludes.h"
#include "behaviortree/basicsbehaviortree.h"
#include "app/components/tagcomponent.h"

class isChasing : public Condition {
public:
    isChasing(nodemap_p nodeMap, std::shared_ptr<GameObject> o) : Condition(nodeMap) {
        m_o = o;
    }

    status_t determine(float seconds) override {
        if (m_o->getComponent<TagComponent>()->isTagger()) return SUCCESS;
        return FAIL;
    }

    void setTagging(bool val) {
        m_o->getComponent<TagComponent>()->setTagging(val);
    }

    void reset() override {
    }

private:
    std::shared_ptr<GameObject> m_o;
};

#endif // ISCHASING_H
