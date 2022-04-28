#ifndef PART_H
#define PART_H

#include "common/gameobject.h"
#include "components/basiccomponents.h"

#define MANSION_FOLDER "/Users/blinnbryce/Documents/engine/res/residentevil/mansion/"

class Part : public GameObject {
public:
    Part(int index);

    void setDrawables() override;
private:
    OBJData m_objData;
    int m_index;
};


#endif // PART_H
