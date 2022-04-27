#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include "common/screen.h"
#include "systems/basicsystems.h"
#include "app/gameobjects/appgameobjects.h"
#include "app/components/appcomponents.h"

#define NUM_OTHER 1

class PlayScreen : public Screen {
public:
    PlayScreen(std::shared_ptr<Input> input);

    void tick(float seconds) override;
    void draw(Graphics *graphics) override;
    void setup();

    std::shared_ptr<Player> getPlayer() {return m_gameWorld->getGameObject<Player>("player");}
    std::shared_ptr<World> getWorld() {return m_gameWorld->getGameObject<World>("world");}
    std::shared_ptr<Other> getOther(int i) {return m_gameWorld->getGameObject<Other>("other"+std::to_string(i));}
};

#endif // PLAYSCREEN_H
