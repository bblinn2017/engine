#include "re_app.h"
#include <iostream>

using namespace std;
using namespace glm;

ReApp::ReApp() {
    // Make Screens
    addScreen(make_shared<GameScreen>(m_input));
    setCurrScreen<GameScreen>(re_screen_t::GAME);
}

void ReApp::tick(float seconds) {
    m_currScreen->tick(seconds);
}

void ReApp::reset() {
    addScreen(make_shared<GameScreen>(m_input));
    setCurrScreen<GameScreen>(re_screen_t::GAME);

    setGraphics(m_graphics);
    m_currScreen->initializeCamera();
}

