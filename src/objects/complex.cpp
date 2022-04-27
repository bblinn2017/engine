#include "complex.h"

using namespace std;
using namespace glm;

Complex::Complex(glm::vec3 scale) : Object(scale), min(vec3(0,0,0)), max(vec3(0,0,0)) {
}
Complex::Complex(float scale) : Object(vec3(scale,scale,scale)), min(vec3(0,0,0)), max(vec3(0,0,0)) {
}
Complex::Complex(objData obj) : Object(vec3(1.,1.,1.)) {
    min = obj.min;
    max = obj.max;

    triBVH = std::make_shared<TriBVH>(obj.tris);
}

vec3 Complex::getMax() {return max;}
vec3 Complex::getMin() {return min;}

vector<tri_p> Complex::getTriangles(vec3 bmin, vec3 bmax) {
    return triBVH->intersectedCollidables(bmin,bmax);
}
