#ifndef TAGGEDCONDITION_H
#define TAGGEDCONDITION_H

#include "engine/util/CommonIncludes.h"
#include "behaviortree/basicsbehaviortree.h"

class TaggedCondition : public Condition {
    TaggedCondition() : Condition() {
        isTagged = false;
    }

    status_t update() {
        if (isTagged) return SUCCESS;
        return FAIL;
    }
private:
    bool isTagged;
};

#endif // TAGGEDCONDITION_H
