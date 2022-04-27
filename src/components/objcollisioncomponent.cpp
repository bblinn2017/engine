#include "objcollisioncomponent.h"

using namespace std;
using namespace glm;

ObjCollisionComponent::ObjCollisionComponent(GameObject *gameObject) :
    Component(gameObject)
{
    m_transform = m_gameObject->getComponent<TransformComponent>();
    m_obj = m_gameObject->getComponent<ObjectComponent>();
}

void ObjCollisionComponent::tick(float seconds) {

}

bool ObjCollisionComponent::insideLine(glm::vec3 c, glm::vec3 d, glm::vec3 n, glm::vec3 p) {
    return glm::dot(glm::cross(n,d - c),p - (d + c)/2.f) >= 0.;
}

coll_t ObjCollisionComponent::checkFace(vec3 b, vector<vec3> ps, vec3 n) {
    // Moving parallel/away from surface
    if (glm::dot(b,n) > -1e-6  * glm::length(b)) return coll_t();

    // Not in range
    // The only point on unit sphere that can touch at normal n is point -n
    vec3 touchPoint = -n;
    float t = glm::dot(ps[0]-touchPoint,n) / glm::dot(b,n);
    if (!inRange(t)) return coll_t();

    // Not inside triangle
    vec3 p = b*t;
    for (int i = 0; i < 3; i++) {
        if (!insideLine(ps[i]-touchPoint,ps[(i+1)%3]-touchPoint,n,p)) return coll_t();
    }

    return coll_t(p,t,n);
}

bool ObjCollisionComponent::solveQuadratic(float a, float b, float c, float &t) {
    float det = b * b - 4 * a * c;

    if (det < 0.) return false;
    float det_sqrt = glm::sqrt(det);

    float d0 = -b / (2 * a);
    float d1 = det_sqrt / (2 * a);

    float min_t = d0 - d1;
    if (inRange(min_t)) {t = min_t; return true;}

    float max_t = d0 + d1;
    if (inRange(max_t)) {t = max_t; return true;}

    t = INFINITY;
    return false;
}

coll_t ObjCollisionComponent::checkEdge(vec3 b, vec3 c, vec3 d, vec3 n) {
    vec3 vec0 = d - c;
    vec3 vec1 = glm::cross(b,vec0);
    vec3 vec2 = glm::cross(d,c);

    float coeffA = glm::dot(vec1,vec1);
    float coeffB = 2*glm::dot(vec1,vec2);
    float coeffC = glm::dot(vec2,vec2) - glm::dot(vec0, vec0);

    float t;
    if (!solveQuadratic(coeffA,coeffB,coeffC,t)) {
        return coll_t();
    }
    vec3 p = b*t;

    // Check that p is on line and not over triangle
    vec3 vecCP = p - c;

    float s = glm::dot(vecCP,vec0);
    float sd = glm::dot(vecCP,glm::cross(n,vec0));
    if ((s > 0) && (s < glm::dot(vec0,vec0)) && (sd < 0)) {
        return  coll_t(p,t,n);
    }
    return coll_t();
}

coll_t ObjCollisionComponent::checkVertex(vec3 b, vec3 v) {
    float coeffA = glm::dot(b,b);
    float coeffB = -2 * glm::dot(v,b);
    float coeffC = glm::dot(v,v) - 1;

    float t;
    if (solveQuadratic(coeffA,coeffB,coeffC,t)) {
        return coll_t(b*t,t,v-b*t);
    }
    return coll_t();
}

coll_t ObjCollisionComponent::collisionPoint(shared_ptr<tri_t> t, vec3 currPos, vec3 finalPos) {
    shared_ptr<Cylinder> cyl = getObj<Cylinder>();
    vector<vec3> ps = vector<vec3>(t->positions);
    vec3 n = t->normal;

    // Convert to ellipsoid coordinates
    mat4 toCyl = mat4(1.);
    toCyl = toCyl * glm::scale(1.f / vec3(cyl->getRadius(),cyl->getHeight()/2.f,cyl->getRadius()));
    toCyl = toCyl * glm::translate(-currPos);
    for (int i = 0; i < 3; i++) {
        ps[i] = vec3(toCyl * vec4(ps[i],1.));
    }
    n = vec3(toCyl * vec4(n,0.));
    n /= glm::length(n);

    vec3 b = finalPos - currPos;
    b = vec3(toCyl * vec4(b,0.));

    coll_t coll;
    // Check face
    if ((coll = checkFace(b,ps,n))) {
        coll.setFriction(t->friction);
        coll.apply(glm::inverse(toCyl));
        return coll;
    }

    // Check Edges
    for (int i = 0; i < 3; i++) {
        coll.minimum(checkEdge(b,ps[i],ps[(i+1)%3],n));
    }
    if (coll) {
        coll.setFriction(t->friction);
        coll.apply(glm::inverse(toCyl));
        return coll;
    }

    // Check Vertices
    coll = coll_t();
    for (int i = 0; i < 3; i++) {
        coll.minimum(checkVertex(b,ps[i]));
    }
    if (coll) {
        coll.setFriction(t->friction);
        coll.apply(glm::inverse(toCyl));
        return coll;
    }

    return coll_t();
}

coll_t ObjCollisionComponent::getClosestCollision(shared_ptr<Complex> complex, vec3 currPos, vec3 nextPos) {
    vec3 mtv;
    coll_t coll;

    shared_ptr<TransformComponent> transform = m_gameObject->getComponent<TransformComponent>();

    vec3 cylMin = transform->getMin();
    vec3 cylMax = transform->getMax();

    for (auto tri : complex->getTriangles(cylMin,cylMax)) {
        coll.minimum(collisionPoint(tri,currPos,nextPos));
    }
    return coll;
}

vec3 ObjCollisionComponent::doNudge(shared_ptr<Complex> complex, coll_t c) {
    vec3 currPos = c.p;
    vec3 nudge = c.n;

    vec3 pos_nudged = currPos + nudge * NUDGE;
    for (int i = 0; i < MAX_NUDGES; i++) {
        coll_t nudge_c = getClosestCollision(complex,currPos,pos_nudged);

        // Floating point precision error where shape starts out inside
        vec3 nudgeD = pos_nudged - currPos;
        if (glm::dot(nudgeD,nudge_c.n) > 0.f) {
            currPos = pos_nudged;
            pos_nudged = currPos + nudge * NUDGE;
            continue;
        }

        if (!nudge_c) {currPos = pos_nudged; break;}

        // ||nudge_c.n +- nudge|| < EPSILON
        // <nudge_c.n +- nudge, nudge_c.n += nudge> < EPSILON
        // ||nudge_c.n||^2 +- 2<nudge_c.n,nudge> + ||nudge||^2 < EPSILON
        // abs(||nudge_c.n||^2 + ||nudge||^2 - EPSILON) < abs(+- 2<nudge_c.n,nudge>)
        if (glm::abs(glm::dot(nudge_c.n,nudge_c.n) + glm::dot(nudge,nudge) - EPSILON) < glm::abs(2*glm::dot(nudge_c.n,nudge))) {
            nudge = -nudge_c.n;
        } else{
            nudge = nudge_c.n;
        }
        pos_nudged = nudge_c.p + nudge * NUDGE;
    }
    return currPos;
}

coll_move_t ObjCollisionComponent::collideCylinder2Complex(shared_ptr<ObjCollisionComponent> other_cc) {
    bool isCyl = getType() == CYLINDER;
    shared_ptr<Complex> complex = (isCyl) ? other_cc->getObj<Complex>() : getObj<Complex>();
    ObjCollisionComponent *cylComp = (isCyl) ? this : other_cc.get();

    vec3 currPos = cylComp->getOldPos();
    vec3 nextPos = cylComp->getPos();
    vector<coll_t> collisions = vector<coll_t>();

    for (int i = 0; i < MAX_TRANSLATIONS; i++) {
        coll_t c = cylComp->getClosestCollision(complex, currPos, nextPos);
        if (!c) break;

        currPos = cylComp->doNudge(complex, c);

        vec3 d = nextPos - currPos;
        vec3 d_corrected = d - glm::dot(d,c.n) * c.n;
        nextPos = currPos + d_corrected;
        collisions.push_back(c);
    }
    if (collisions.size() == 0) return coll_move_t();

    // Can the complex object move itself at the point of collision on the cylinder?
    coll_t lastColl = collisions[collisions.size()-1];
    bool cylFriction = ((isCyl) ? getObj<Cylinder>() : other_cc->getObj<Cylinder>())->hasFriction(lastColl.n);

    bool a_friction = isCyl ? cylFriction : lastColl.f;
    bool b_friction = isCyl ? lastColl.f : cylFriction;

    return coll_move_t(nextPos-cylComp->getPos(), a_friction, b_friction);
}

coll_move_t ObjCollisionComponent::collideCylinder2Cylinder(shared_ptr<ObjCollisionComponent> other_cc) {
    shared_ptr<Cylinder> cyl = getObj<Cylinder>();
    shared_ptr<Cylinder> other_cyl = other_cc->getObj<Cylinder>();

    vec3 pos = getPos();
    vec3 other_pos = other_cc->getPos();

    // Circle Math
    float rad = cyl->getRadius();
    float other_rad = other_cyl->getRadius();
    vec3 vec = pos - other_pos;
    float radSum = rad + other_rad;
    float len_2 = vec.x * vec.x + vec.z * vec.z;
    bool circleC = len_2 < radSum * radSum;
    if (!circleC) return coll_move_t();
    // Line Math
    float min = getMin();
    float max = getMax();
    float other_min = other_cc->getMin();
    float other_max = other_cc->getMax();
    bool lineC = (min < other_max) && (max > other_min);
    if (!lineC) return coll_move_t();

    // Circle MTV
    float len = glm::sqrt(len_2);
    vec3 mtv_circle = vec3(vec.x,0,vec.z) / len * (radSum - len);
    // Line MTV
    float aRight = other_max - min;
    float aLeft = max - other_min;
    float mtv_line = (aRight < aLeft) ? aRight : -aLeft;
    // MTV
    bool circleCollision = radSum - len < abs(mtv_line);
    vec3 mtv = circleCollision ? mtv_circle : vec3(0,mtv_line,0);

    return coll_move_t(mtv,!circleCollision,!circleCollision);
}

coll_move_t ObjCollisionComponent::collide(std::shared_ptr<ObjCollisionComponent> other_cc) {
    // This object must be movable to collide
    if (!isMovable()) return coll_move_t();
    // Either object must have moved
    if (getDelta() == vec3() && other_cc->getDelta() == vec3()) return coll_move_t();

    map<obj_type_t,int> types = map<obj_type_t,int>();
    for (int i = CYLINDER; i <= COMPLEX; i++) {
        types[obj_type_t(i)] = 0;
    }
    types[getType()]++;
    types[other_cc->getType()]++;

    // Get MTV
    coll_move_t coll_move;
    if (types[CYLINDER] == 2) {
        coll_move = collideCylinder2Cylinder(other_cc);
    } else if (types[CYLINDER] == 1 && types[COMPLEX] == 1) {
        coll_move = collideCylinder2Complex(other_cc);
    }

    return coll_move;
}

void ObjCollisionComponent::handleCollision(coll_move_t coll_move, shared_ptr<ObjCollisionComponent> other_cc) {
    if (coll_move.mtvA == vec3()) return;

    // Handle Collision
    if (other_cc->isMovable()) {
        updateTransform(coll_move.mtvA/2.f,coll_move.b_friction);
        other_cc->updateTransform(-coll_move.mtvA/2.f,coll_move.a_friction);
    } else {
        updateTransform(coll_move.mtvA,coll_move.b_friction);
    }


}

void ObjCollisionComponent::updateTransform(glm::vec3 mtv, bool onFrictionSurface) {
    *(m_transform->getPos()) += mtv;
    vec3 dir = mtv / glm::length(mtv);
    *(m_transform->getVel()) -= glm::dot(*(m_transform->getVel()),dir) * dir;

    // Movement Component
    if (onFrictionSurface) m_gameObject->getComponent<MovementComponent>()->friction();
}
