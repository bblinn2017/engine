#ifndef TAGTREE_H
#define TAGTREE_H

#include "engine/util/CommonIncludes.h"
#include "behaviortree/behaviortree.h"
#include "common/gameobject.h"

#include "pickTarget.h"
#include "chase.h"
#include "hide.h"
#include "wait.h"
#include "isChasing.h"

class TagTree : public BehaviorTree  {
public:
    TagTree(std::shared_ptr<GameObject> o, std::vector<std::shared_ptr<GameObject>> targets, std::shared_ptr<GameObject> navigable);
    void setTagger(std::shared_ptr<GameObject> o);
};

#endif // TAGTREE_H
