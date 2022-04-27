#ifndef PART_H
#define PART_H

#include "common/gameobject.h"
#include "components/basiccomponents.h"

#define MANSION_FOLDER "/Users/blinnbryce/Documents/engine/res/residentevil/mansion/"
#define WORLD_FILE "/Users/blinnbryce/Documents/engine/res/platformer/level_easy.obj"
#define TEX_FILE "/Users/blinnbryce/Documents/engine/res/platformer/level_easy.png"

class Part : public GameObject {
public:
    Part(int index);

    void setDrawables() override;
private:
    OBJData m_objData;
    int m_index;
};


#endif // PART_H
