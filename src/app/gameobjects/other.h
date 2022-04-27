#ifndef OTHER_H
#define OTHER_H

#include "common/gameobject.h"
#include "components/basiccomponents.h"

#define SCALE 1.5

class Other : public GameObject {
public:
    Other();

    void setDrawables() override;
};

#endif // OTHER_H
