#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "engine/util/CommonIncludes.h"
#include "btreenode.h"
#include "leaf.h"

class Composite : public BTreeNode {
public:
    Composite(nodemap_p nodeMap, composite_t i, status_t (*func) (node_p, float), bool negate)  : BTreeNode(nodeMap,false,i,negate) {
        m_curr = 0;
        m_func = func;

        m_prev = 0;
    }

    status_t determine(float seconds) override {
        setStart();
        bool cont = true;
        status_t status;

        while (true) {
            // Update status and determine if must break
            status = m_func(m_children[m_curr],seconds);
            cont = getContinue(status);

            // Reset prev
            resetPrev(m_prev,m_curr,status);

            // If must break, break
            if (!cont) break;

            // Move to next child
            m_curr++;

            // Reset all if completed
            cont = resetEnd();
            if (!cont) break;
        }

        // Set prev child and status
        m_prev = m_curr;

        return status;
    }

    void reset() override {
        for (auto c: m_children) {
            c->reset();
        }
        m_curr = 0;
        m_prev = 0;
    }

    virtual void setStart() = 0;
    virtual bool getContinue(status_t status) = 0;
    virtual void resetPrev(int prev, int curr, status_t status) = 0;
    virtual bool resetEnd() = 0;
    void addChild(node_p node) {m_children.push_back(node);}
protected:
    std::vector<node_p> m_children;
    int m_curr;

    int m_prev;
private:
    status_t (*m_func) (node_p, float);
};

#endif // COMPOSITE_H
