#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "engine/util/CommonIncludes.h"
#include "composite.h"

class Sequence : public Composite {
public:
    Sequence(nodemap_p nodeMap, status_t (*func) (node_p,float), bool negate) : Composite(nodeMap,SEQUENCE,func,negate) {}

    // Starts from previous child
    void setStart() override {
    }

    // Updates until child doesn't succeed;
    bool getContinue(status_t status) override {
        return status == SUCCESS;
    }

    // Reset previously running child if sequence completed
    void resetPrev(int prev, int curr, status_t status) override {

    }

    // Reset all if sequence ended
    bool resetEnd() override {
        if (m_curr == m_children.size()) {
            m_curr = 0;
            for (auto c: m_children) c->reset();
            return false;
        }
        return true;
    }
};

#endif // SEQUENCE_H
