#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "engine/util/CommonIncludes.h"
#include "common/system.h"
#include "components/objcollisioncomponent.h"

template <typename TypeStatic, typename TypeDynamic>
class CollisionSystem : public System {
public:
    CollisionSystem() {
        m_statics = std::make_shared<TypeStatic>(false);
        m_dynamics = std::make_shared<TypeDynamic>(true);
    }

    void addGameObject(std::string key, std::shared_ptr<GameObject> o) override {
        m_gameObjects[key] = o;
        if (o->getComponent<ObjCollisionComponent>()->isMovable()) {
            m_dynamics->addSpatial(o);
        } else{
            m_statics->addSpatial(o);
        }
    }

    void removeGameObject(std::string key) override {
        if (m_gameObjects[key]->template getComponent<ObjCollisionComponent>()->isMovable()) {
            m_dynamics->removeSpatial(m_gameObjects[key]);
        } else{
            m_statics->removeSpatial(m_gameObjects[key]);
        }
        m_gameObjects.erase(key);
    }

    void buildStatics() {m_statics->build();}
    void buildDynamics() {m_dynamics->build();}
    void build() {buildStatics(); buildDynamics();}

    void checkCollisions() {
        // Set no friction
        for (auto o : m_dynamics->getSpatials()) {
            o->template getComponent<MovementComponent>()->noFriction();
        }

        // Check collisions on all dynamic objects
        std::set<std::shared_ptr<GameObject>> prechecked;
        for (auto o_i : m_dynamics->getSpatials()) {
            auto c_i = o_i->template getComponent<ObjCollisionComponent>();

            // Check collision all dynamic objects
            for (auto o_j : m_dynamics->intersectedGameObjects(o_i)) {
                if (o_i == o_j) continue;
                if (prechecked.find(o_j) != prechecked.end()) continue;

                auto c_j = o_j->template getComponent<ObjCollisionComponent>();

                // Check collision
                c_i->handleCollision(c_i->collide(c_j),c_j);
            }

            // Check collision all static objects
            for (auto o_j : m_statics->intersectedGameObjects(o_i)) {
                auto c_j = o_j->template getComponent<ObjCollisionComponent>();

                // Check collision
                c_i->handleCollision(c_i->collide(c_j),c_j);
            }

            // Don't check the same collision twice
            prechecked.emplace(o_i);
        }
    }

protected:
    std::shared_ptr<TypeStatic> m_statics;
    std::shared_ptr<TypeDynamic> m_dynamics;
};

#endif // COLLISIONSYSTEM_H
