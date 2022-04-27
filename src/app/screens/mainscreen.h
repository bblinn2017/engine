#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "common/screen.h"
#include "systems/basicsystems.h"
#include "app/gameobjects/menu.h"

class MainScreen : public Screen {
public:
    MainScreen(std::shared_ptr<Input> input);

    void draw(Graphics *graphics) override;
    void tick(float seconds) override;

    bool toGame() {return m_toGame;}
protected:
    bool m_toGame;
};

#endif // MAINSCREEN_H
