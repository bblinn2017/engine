#ifndef SPATIALSTRUCTURES_H
#define SPATIALSTRUCTURES_H

#include "engine/util/CommonIncludes.h"

template <typename Spatial>
class SpatialStructure {
public:
    SpatialStructure(bool dynamic)
    {
        m_spatials = std::vector<Spatial>();
    }

    void addSpatial(Spatial o) {
        m_spatials.push_back(o);
    }
    std::vector<Spatial> getSpatials() {return m_spatials;}
    void removeSpatial(Spatial o) {
        auto it = std::find(m_spatials.begin(),m_spatials.end(),o);
        if (it != m_spatials.end()) m_spatials.erase(it);
    }

    virtual glm::vec3 getPos(Spatial o) = 0;
    virtual glm::vec3 getMin(Spatial o) = 0;
    virtual glm::vec3 getMax(Spatial o) = 0;

    virtual void build() = 0;

protected:
    bool isDynamic;
    std::vector<Spatial> m_spatials;
};

template <typename Collidable>
class CollisionStructure : public SpatialStructure<Collidable> {
public:
    CollisionStructure(bool dynamic) :
        SpatialStructure<Collidable>(dynamic)
    {

    }
    virtual std::vector<Collidable> intersectedCollidables(glm::vec3 bmin, glm::vec3 bmax) = 0;
};

#endif // SPATIALSTRUCTURES_H
