#ifndef COMMONINCLUDES_H
#define COMMONINCLUDES_H

/*A file for any includes or structs that need to be used in many different places. */

#include "GL/glew.h"
#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <unordered_set>
#include <queue>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "engine/util/TypeMap.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"
#include "engine/graphics/Shape.h"
#include "engine/graphics/Material.h"
#include "engine/graphics/OBJLoader.h"

#include <QMouseEvent>
#include <QKeyEvent>

#include "common/input.h"

inline glm::vec3 cmin(glm::vec3 a, glm::vec3 b) {return glm::vec3(glm::min(a.x,b.x),glm::min(a.y,b.y),glm::min(a.z,b.z));}
inline glm::vec3 cmax(glm::vec3 a, glm::vec3 b) {return glm::vec3(glm::max(a.x,b.x),glm::max(a.y,b.y),glm::max(a.z,b.z));}

#define GRAVITY -10.f
#define MOVE 10.f
#define CAMERA_M 10.f
#define STRAFING true
#define MAX_TRANSLATIONS 100
#define MAX_NUDGES 3
#define NUDGE 1e-2f
#define EPSILON 1e-2f

#define UNTOUCHED 0xffffffff
#define TOUCHED_TWICE 0xfffffffd
#define ROOT 0xfffffffc
#define LEAF_SIZE 10

struct vecFuncs {
    size_t operator()(const glm::vec3& k) const {
        return std::hash<float>()(k.x) ^ std::hash<float>()(k.y) ^ std::hash<float>()(k.z);
    }

    bool operator()(const glm::vec3& a, const glm::vec3& b)const
    {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }
};

#endif // COMMONINCLUDES_H
