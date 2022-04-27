#ifndef WAIT_H
#define WAIT_H

#include "engine/util/CommonIncludes.h"
#include "behaviortree/basicsbehaviortree.h"
#include "components/basiccomponents.h"

class Wait : public Action {
public:
    Wait(nodemap_p nodeMap, float time) : Action(nodeMap) {
        m_time = time;
        delta = 0.;
    }

    status_t determine(float seconds) override {
        delta += seconds;
        return (delta >= m_time) ? SUCCESS : RUNNING;
    }

    void reset() override  {
        delta = 0.;
    }
private:
    float m_time;
    float delta;
};

#endif // WAIT_H
