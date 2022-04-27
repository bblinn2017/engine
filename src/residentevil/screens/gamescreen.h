#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "common/screen.h"
#include "systems/basicsystems.h"

#include "residentevil/gameobjects/regameobjects.h"

class GameScreen : public Screen {
public:
    GameScreen(std::shared_ptr<Input> input);

    void tick(float seconds) override;
    void draw(Graphics *graphics) override;
};


#endif // GAMESCREEN_H
