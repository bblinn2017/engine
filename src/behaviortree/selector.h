#ifndef SELECTOR_H
#define SELECTOR_H

#include "engine/util/CommonIncludes.h"
#include "composite.h"

class Selector : public Composite {
public:
    Selector(nodemap_p nodeMap, status_t (*func) (node_p,float), bool negate) : Composite(nodeMap,SELECTOR,func,negate) {}

    // Starts from first child
    void setStart() override {
        m_curr = 0;
    }

    // Updates until child doesn't fail
    bool getContinue(status_t status) override {
        return status == FAIL;
    }

    // Reset previously running if child before it starts running
    void resetPrev(int prev, int curr, status_t status) override {
        if (status == RUNNING && curr < prev) {
            m_children[prev]->reset();
        }
    }

    // Reset to beginning of selector
    bool resetEnd() override {
        if (m_curr == m_children.size()) {
            m_curr = 0;
            for (auto c: m_children) c->reset();
            return false;
        }
        return true;
    }
};

#endif // SELECTOR_H
