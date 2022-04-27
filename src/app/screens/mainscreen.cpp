#include "mainscreen.h"

using namespace std;
using namespace glm;

MainScreen::MainScreen(shared_ptr<Input> input) :
    Screen(input),
    m_toGame(false)
{
    // Make Systems
    m_gameWorld->addSystem(make_shared<DrawSystem>());
    std::shared_ptr<DrawSystem> drawSystem = m_gameWorld->getSystem<DrawSystem>();
    // Make Components
    // Menu
    shared_ptr<Menu> menu = make_shared<Menu>();
    m_gameWorld->addGameObject("menu", menu);
    drawSystem->addGameObject("menu", menu);

    m_camera->setUI(true);
}

void MainScreen::draw(Graphics *graphics) {
    m_gameWorld->getSystem<DrawSystem>()->draw();
}

void MainScreen::tick(float seconds) {
    if (m_input->isKeyActive(Qt::Key_Return) && !m_toGame) {
        m_toGame = true;
    }
}
