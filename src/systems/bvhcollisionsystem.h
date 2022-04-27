#ifndef BVHCOLLISIONSYSTEM_H
#define BVHCOLLISIONSYSTEM_H

#include "engine/util/CommonIncludes.h"
#include "collisionsystem.h"
#include "spatialstructures/gameobjectbvh.h"

class BVHCollisionSystem : public CollisionSystem<GameObjectBVH,GameObjectBVH> {
public:
    BVHCollisionSystem() {}
};

#endif // BVHCOLLISIONSYSTEM_H
