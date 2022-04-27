#include "navigationcomponent.h"

using namespace std;
using namespace glm;

NavigationComponent::NavigationComponent(GameObject * o) : Component(o) {
    pathSet = false;
    m_transform = o->getComponent<TransformComponent>();
}

void NavigationComponent::setPath(std::vector<glm::vec3> path) {
    m_path = path;
    pathSet = true;
}

void NavigationComponent::checkpoint() {
    // Check if past current checkpoint
    vec2 start = vec2(m_path[0].x,m_path[0].z);
    vec2 end = vec2(m_path[1].x,m_path[1].z);

    vec3 pos = *(m_transform->getPos());
    vec2 v = vec2(pos.x,pos.z);

    float t = glm::dot(v - start,end - start) / glm::dot(end - start, end - start);

    if (t > 1.f) {
        m_path.erase(m_path.begin());
        m_path[0] = pos;
    }
}

void NavigationComponent::tick(float seconds) {
    // No path set
    if (!pathSet) return;
    // Empty Path
    if (m_path.size() == 0) {pathSet = false; return;}
    // Update checkpoints
    checkpoint();
    // If navigation is ended
    if (m_path.size() == 1) {m_path.empty(); pathSet = false; return;}

    // Update movement
    vec3 start = m_path[0];
    vec3 end = m_path[1];

    vec3 *vel = m_transform->getVel();
    vec3 pos = *(m_transform->getPos());
    vec3 dir = end - start;
    dir.y = 0;
    dir = dir * MOVE / glm::length(dir);

    vel->x = 0.; vel->z = 0.;
    (*vel) += dir;
}
