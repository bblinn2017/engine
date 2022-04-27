#ifndef SCREEN_H
#define SCREEN_H

#include "engine/util/CommonIncludes.h"
#include "gameworld.h"

class Screen {
public:
    Screen(std::shared_ptr<Input> input);
    void setScreenSize(int w, int h);

    virtual void tick(float seconds);
    virtual void draw(Graphics *graphics) = 0;
    void initializeCamera();
    std::shared_ptr<Camera> getCamera() {return m_camera;}
    void setGraphics(Graphics *graphics);
protected:
    Graphics * m_graphics;
    std::shared_ptr<Input> m_input;
    std::shared_ptr<GameWorld> m_gameWorld;
    std::shared_ptr<Camera> m_camera;
};

#endif // SCREEN_H
