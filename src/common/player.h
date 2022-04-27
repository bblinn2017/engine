#ifndef PLAYER_H
#define PLAYER_H

#include "common/gameobject.h"
#include "components/basiccomponents.h"

#define PLAYER_HEIGHT 2.f
#define PLAYER_RADIUS 1.f

class Player : public GameObject {
public:
    Player(std::shared_ptr<Input> input, std::shared_ptr<Camera> camera);

    void setDrawables() override;
};

#endif // PLAYER_H
