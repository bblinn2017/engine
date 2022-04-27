#ifndef NODECASTER_H
#define NODECASTER_H

#include "engine/util/CommonIncludes.h"
#include "leaf.h"
#include "composite.h"
#include "action.h"
#include "condition.h"
#include "selector.h"
#include "sequence.h"

inline status_t nodeCastUpdate(node_p node, float seconds) {
    if (node->isLeaf()) {
        if (node->type() == ACTION) return std::static_pointer_cast<Action>(node)->update(seconds);
        return std::static_pointer_cast<Condition>(node)->update(seconds);
    }
    if (node->type() == SELECTOR) return std::static_pointer_cast<Selector>(node)->update(seconds);
    return std::static_pointer_cast<Sequence>(node)->update(seconds);
}

class selector_p : public std::shared_ptr<Selector> {
public:
    selector_p(nodemap_p m_nodeMap, bool negate) : std::shared_ptr<Selector>(std::make_shared<Selector>(m_nodeMap,nodeCastUpdate,negate)) {}
    selector_p(nodemap_p m_nodeMap) : std::shared_ptr<Selector>(std::make_shared<Selector>(m_nodeMap,nodeCastUpdate,false)) {}
};

class sequence_p : public std::shared_ptr<Sequence> {
public:
    sequence_p(nodemap_p m_nodeMap, bool negate) : std::shared_ptr<Sequence>(std::make_shared<Sequence>(m_nodeMap,nodeCastUpdate,negate)) {}
    sequence_p(nodemap_p m_nodeMap) : std::shared_ptr<Sequence>(std::make_shared<Sequence>(m_nodeMap,nodeCastUpdate,false)) {}
};

#endif // NODECASTER_H
