#ifndef COMPLEX_H
#define COMPLEX_H

#include "engine/util/CommonIncludes.h"
#include "objects.h"

class Complex : public Object {
public:
    Complex(glm::vec3 scale);
    Complex(float scale);
    Complex(objData obj);

    glm::vec3 getMax() override;
    glm::vec3 getMin() override;

    std::vector<tri_p> getTriangles(glm::vec3 bmin, glm::vec3 bmax);
private:
    std::shared_ptr<TriBVH> triBVH;
    glm::vec3 min;
    glm::vec3 max;
};

#endif // COMPLEX_H
