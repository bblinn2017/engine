#include "screen.h"

using namespace std;
using namespace glm;

Screen::Screen(shared_ptr<Input> input) :
    m_input(input),
    m_gameWorld(make_shared<GameWorld>()),
    m_camera(make_shared<Camera>())
{
    m_camera->setEye(vec3());
}

void Screen::initializeCamera() {
    m_graphics->setCamera(m_camera);
}

void Screen::setGraphics(Graphics * graphics) {
    m_graphics = graphics;
    m_gameWorld->setGraphics(graphics);
}

void Screen::setScreenSize(int w, int h) {

}

void Screen::tick(float seconds) {

}
