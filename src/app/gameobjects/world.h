#ifndef WORLD_H
#define WORLD_H

#include "common/gameobject.h"
#include "components/basiccomponents.h"

#define WORLD_FILE "/Users/blinnbryce/Documents/engine/res/platformer/level_easy.obj"
#define TEX_FILE "/Users/blinnbryce/Documents/engine/res/platformer/level_easy.png"

class World : public GameObject {
public:
    World();

    void setDrawables() override;
private:
    OBJData m_objData;
};

#endif // WORLD_H
