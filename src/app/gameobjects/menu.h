#ifndef MENU_H
#define MENU_H

#include "common/gameobject.h"
#include "components/basiccomponents.h"

class Menu : public GameObject {
public:
    Menu();

    void setDrawables() override;
};

#endif // MENU_H
