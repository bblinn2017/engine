#include "navmeshcomponent.h"

using namespace std;
using namespace glm;

NavmeshComponent::NavmeshComponent(GameObject *gameObject, objData obj) :
    Component(gameObject)
{
    buildGraph(obj);
}

void NavmeshComponent::buildGraph(objData obj) {
    vector<shared_ptr<tri_t>> allTris = obj.tris;
    vector<shared_ptr<tri_t>> traversableTris;

    // Remove Non-traversable triangles
    vector<set<int>> allFaceMap = obj.faceMap;
    m_faceMap = map<tri_p,set<tri_p>>();
    for (int i = 0 ; i < allTris.size(); i++) {
        if (allTris[i]->friction) {
            traversableTris.push_back(allTris[i]);
            m_faceMap[allTris[i]] = set<tri_p>();
        }
    }

    for (int i = 0; i < allTris.size(); i++) {
        if (!allTris[i]->friction) continue;

        auto adjs = allFaceMap[i];
        for (auto j : adjs) {
            if (!allTris[j]->friction) continue;
            m_faceMap[allTris[i]].emplace(allTris[j]);
        }
    }

    m_triBVH = make_shared<TriBVH>(traversableTris);
}

vector<vec3> NavmeshComponent::genPath(vec3 start, vec3 end) {
    tri_p start_tri = m_triBVH->closestCollidable(start);
    tri_p end_tri = m_triBVH->closestCollidable(end);
    if (start_tri == end_tri) {return vector<vec3> {start,end};}

    tri_p closest;
    map<tri_p,tri_p> parentMap = genNodes(start_tri,end_tri,closest);

    tri_p curr = end_tri;
    if (parentMap.find(end_tri) == parentMap.end()) {
        curr = closest;
    }

    vector<tri_p> tris;
    int i = 0;
    while (curr != NULL) {
        tris.insert(tris.begin(),curr);
        curr = parentMap[curr];
        i++;
        if (i == 100) {
            cout << curr << parentMap[curr] << closest << start_tri << end_tri << endl;
            exit(0);
        }
    }

    vector<vec3> path;
    path.push_back(start);
    for (int i = 0; i < tris.size() - 1; i++) {
        path.push_back(midpointEdge(tris[i],tris[i+1]));
    }
    path.push_back(end);

    return path;
}

map<tri_p,tri_p> NavmeshComponent::genNodes(tri_p start_tri, tri_p end_tri, tri_p &closest) {
    map<tri_p,tri_p> parentMap;
    parentMap[start_tri] = NULL;

    float weight = dist(start_tri,end_tri);

    map<tri_p,float> costMap;
    costMap[start_tri] = weight;

    map<float,tri_p> queue;
    queue[weight] = start_tri;

    float closestDistance = INFINITY;

    tri_p tri;
    while (!queue.empty()) {
        tri = queue.begin()->second;
        if (queue.begin()->first < closestDistance) {
            closestDistance = queue.begin()->first;
            closest = tri;
        }
        queue.erase(queue.begin()->first);
        costMap.erase(tri);

        for (auto neighbor : m_faceMap[tri]) {
            if (neighbor == end_tri) {
                parentMap[neighbor] = tri;
                return parentMap;
            }

            if (parentMap.find(neighbor) != parentMap.end()) continue;

            weight = dist(neighbor,end_tri);
            // If weight exists
            if (costMap.find(neighbor) != costMap.end()) {
                if (weight >= costMap[neighbor]) continue; // Skip if higher
                else { // Remove if lower
                    queue.erase(weight);
                }
            }
            // Set
            queue[weight] = neighbor;
            costMap[neighbor] = weight;
            parentMap[neighbor] = tri;
        }
    }
    return parentMap;
}
