#ifndef CHASE_HIDE_H
#define CHASE_HIDE_H

#include "engine/util/CommonIncludes.h"
#include "behaviortree/basicsbehaviortree.h"
#include "common/gameobject.h"
#include "components/basiccomponents.h"
#include "isChasing.h"

class ChaseHide : public Action {
public:
    ChaseHide(nodemap_p nodeMap, std::shared_ptr<GameObject> o, std::shared_ptr<GameObject> navigable, std::string isChasingKey) : Action(nodeMap) {
        m_o = o;
        m_navmesh = navigable->getComponent<NavmeshComponent>();
        m_target = NULL;
        m_isChasingKey = isChasingKey;
        delta = 1.f;
        total_delta = 0.f;
    }

    void setTarget(std::shared_ptr<GameObject> target) {
        m_target = target;
    }

    bool hasTarget() {return m_target != NULL;}

    status_t determine(float seconds) override {
        // One second buffer
        total_delta += seconds;
        if (total_delta > 1.f) {
            // Check if tagged
            coll_move_t coll = m_o->getComponent<ObjCollisionComponent>()->collide(m_target->getComponent<ObjCollisionComponent>());
            if (coll.mtvA != glm::vec3()) {
                delta = 0.f;
                swapRole();
                return collisionStatus();
            }
        }

        delta += seconds;
        if (delta >= 1.) {
            glm::vec3 start = getStart();
            glm::vec3 end = getEnd();
            std::vector<glm::vec3> path = m_navmesh->genPath(start,end);
            m_o->getComponent<NavigationComponent>()->setPath(path);
            delta = 0.f;
        }
        return RUNNING;
    }

    virtual glm::vec3 getStart() = 0;
    virtual glm::vec3 getEnd() = 0;
    virtual void swapRole() = 0;
    virtual status_t collisionStatus() = 0;

    void reset() override {
        m_target = NULL;
        delta = 1.f;
        total_delta = 0.f;
    }

protected:
    std::shared_ptr<GameObject> m_o;
    std::shared_ptr<GameObject> m_target;
    std::shared_ptr<NavmeshComponent> m_navmesh;
    float delta;
    float total_delta;
    std::string m_isChasingKey;
    std::string m_hideKey;
};

#endif // CHASE_HIDE_H
