#include "application.h"

using namespace std;
using namespace glm;

Application::Application() :
    m_screens(),
    m_input(make_shared<Input>()),
    m_graphics(nullptr)
{
}

void Application::tick(float seconds) {
    m_currScreen->tick(seconds);
}

void Application::draw(Graphics *graphics) {
    m_currScreen->draw(graphics);
}

void Application::setScreenSize(int w, int h) {
    m_currScreen->setScreenSize(w,h);
    m_input->setScreenSize(w/2,h/2);
}

void Application::setGraphics(Graphics *graphics) {
    m_graphics = graphics;
    for (auto s: m_screens) {
        s.second->setGraphics(m_graphics);
    }
}

void Application::initializeCamera() {
    m_currScreen->initializeCamera();
}

