#ifndef OBJCOLLISIONCOMPONENT_H
#define OBJCOLLISIONCOMPONENT_H

#include "common/component.h"
#include "common/gameobject.h"
#include "objectcomponent.h"
#include "transformcomponent.h"
#include "movementcomponent.h"

struct coll_t {
    glm::vec3 p;
    float t;
    glm::vec3 n;
    bool f;

    coll_t() {
        p = glm::vec3();
        t = INFINITY;
    }
    coll_t(glm::vec3 point, float interval, glm::vec3 normal) {
        p = point;
        t = interval;
        n = normal;
    }

    void setFriction(bool friction) {
        f = friction;
    }

    void apply(glm::mat4 invTransform) {
        p = glm::vec3(invTransform * glm::vec4(p,1.));
        n = glm::vec3(invTransform * glm::vec4(n,0.));
        n /= glm::length(n);
    }

    void minimum(coll_t other) {
        if (t < other.t) return;
        else if (t == other.t && (f || !other.f)) return;

        p = other.p;
        n = other.n;
        f = other.f;
        t = other.t;
    }

    operator bool() const {
        return (t > 0.f) && (t <= 1.f);
    }
};

struct coll_move_t {
    glm::vec3 mtvA;
    bool a_friction;
    bool b_friction;

    coll_move_t() {
        mtvA = glm::vec3();
        a_friction = false;
        b_friction = false;
    }

    coll_move_t(glm::vec3 vec, bool af, bool bf) {
        mtvA = vec;
        a_friction = af;
        b_friction = bf;
    }
};

class ObjCollisionComponent : public Component {
public:
    ObjCollisionComponent(GameObject *gameObject);
    void tick(float seconds) override;

    coll_move_t collide(std::shared_ptr<ObjCollisionComponent> other_cc);
    coll_move_t collideCylinder2Cylinder(std::shared_ptr<ObjCollisionComponent> other_cc);
    coll_move_t collideCylinder2Complex(std::shared_ptr<ObjCollisionComponent> other_cc);

    glm::vec3 doNudge(std::shared_ptr<Complex> complex, coll_t c);
    coll_t getClosestCollision(std::shared_ptr<Complex> complex, glm::vec3 currPos, glm::vec3 finalPos);
    coll_t collisionPoint(std::shared_ptr<tri_t> tri, glm::vec3 currPos, glm::vec3 nextPos);
    coll_t checkVertex(glm::vec3 b, glm::vec3 v);
    coll_t checkEdge(glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 n);
    coll_t checkFace(glm::vec3 b, std::vector<glm::vec3> ps, glm::vec3 n);
    bool insideLine(glm::vec3 c, glm::vec3 d, glm::vec3 n, glm::vec3 p);
    bool solveQuadratic(float a, float b, float c, float &t);

    bool isMovable() {return m_transform->isMovable();}
    void handleCollision(coll_move_t coll_move, std::shared_ptr<ObjCollisionComponent> other_cc);
    void updateTransform(glm::vec3 mtv, bool onFrictionSurface);

    glm::vec3 getPos() {return *(m_transform->getPos());}
    glm::vec3 getOldPos() {return *(m_transform->getOldPos());}
    float getMin() {return m_transform->getMin().y;}
    float getMax() {return m_transform->getMax().y;}
    obj_type_t getType() {return m_obj->getType();}
    glm::vec3 getDelta() {return *(m_transform->getPos()) - *(m_transform->getOldPos());}
    void reset() {(*m_transform->getOldPos()) = (*m_transform->getPos());}
    bool inRange(float t) {return t >= 0.f && t < 1.f;}

    template <typename ObjType>
    std::shared_ptr<ObjType> getObj() {
        return m_obj->getObj<ObjType>();
    }
private:
    std::shared_ptr<TransformComponent> m_transform;
    std::shared_ptr<ObjectComponent> m_obj;
};

#endif // OBJCOLLISIONCOMPONENT_H
