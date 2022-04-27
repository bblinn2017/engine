#ifndef ACTION_H
#define ACTION_H

#include "engine/util/CommonIncludes.h"
#include "leaf.h"

class Action : public Leaf {
public:
    Action(nodemap_p nodeMap) : Leaf(nodeMap,ACTION) {}
};

#endif // ACTION_H
