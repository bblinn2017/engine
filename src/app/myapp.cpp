#include "app/myapp.h"
#include <iostream>

using namespace std;
using namespace glm;

MyApp::MyApp() {
    // Make Screens
    addScreen(make_shared<MainScreen>(m_input));
    addScreen(make_shared<PlayScreen>(m_input));
    setCurrScreen<PlayScreen>(MyScreenType::PLAY);
}

void MyApp::tick(float seconds) {
    m_currScreen->tick(seconds);

    if (m_currScreenType == MyScreenType::MAIN) {
        shared_ptr<MainScreen> curr = dynamic_pointer_cast<MainScreen>(m_currScreen);
        bool toGame = curr->toGame();

        if (toGame) {
            setCurrScreen<PlayScreen>(MyScreenType::PLAY);
            m_currScreen->initializeCamera();
        }
    }
}

void MyApp::reset() {
    addScreen(make_shared<MainScreen>(m_input));
    addScreen(make_shared<PlayScreen>(m_input));
    setCurrScreen<MainScreen>(MyScreenType::MAIN);

    setGraphics(m_graphics);
    m_currScreen->initializeCamera();
}

