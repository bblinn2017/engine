#ifndef LEAF_H
#define LEAF_H

#include "engine/util/CommonIncludes.h"
#include "btreenode.h"

class Leaf : public BTreeNode {
public:
    Leaf(nodemap_p nodeMap, leaf_t i) : BTreeNode(nodeMap,true,i,false) {}
protected:
    status_t m_status;
};

typedef std::shared_ptr<Leaf> leaf_p;

#endif // LEAF_H
