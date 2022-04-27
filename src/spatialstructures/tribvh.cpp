#include "tribvh.h"

using namespace std;
using namespace glm;

TriBVH::TriBVH(vector<shared_ptr<tri_t>> tris) :
    BVH<shared_ptr<tri_t>,TriComparator>(false)
{
    for (auto t: tris) {
        addSpatial(t);
    }
    build();
}

glm::vec3 TriBVH::getMin(shared_ptr<tri_t> o) {
    return o->min();
}

glm::vec3 TriBVH::getMax(shared_ptr<tri_t> o) {
    return o->max();
}

glm::vec3 TriBVH::getPos(shared_ptr<tri_t> o) {
    return o->pos();
}
