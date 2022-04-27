#ifndef CONDITION_H
#define CONDITION_H

#include "engine/util/CommonIncludes.h"
#include "leaf.h"

class Condition : public Leaf {
public:
    Condition(nodemap_p nodeMap) : Leaf(nodeMap,CONDITION) {}
};

#endif // CONDITION_H
