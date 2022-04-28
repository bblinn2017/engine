#include "gamescreen.h"
#include <iostream>

using namespace std;
using namespace glm;

GameScreen::GameScreen(shared_ptr<Input> input) :
    Screen(input)
{
    // Make Systems
    m_gameWorld->addSystem(make_shared<TickSystem>());
    shared_ptr<TickSystem> tickSystem = m_gameWorld->getSystem<TickSystem>();
    m_gameWorld->addSystem(make_shared<DrawSystem>());
    shared_ptr<DrawSystem> drawSystem = m_gameWorld->getSystem<DrawSystem>();
    m_gameWorld->addSystem(make_shared<BVHCollisionSystem>());
    shared_ptr<BVHCollisionSystem> collisionSystem = m_gameWorld->getSystem<BVHCollisionSystem>();
    m_gameWorld->addSystem(make_shared<NavigationSystem>());
    shared_ptr<NavigationSystem> navSystem = m_gameWorld->getSystem<NavigationSystem>();

    // Make Game Objects
    // Player
    shared_ptr<Player> player = make_shared<Player>(m_input,m_camera);
    m_gameWorld->addGameObject("player",player);
    tickSystem->addGameObject("player",player);
    drawSystem->addGameObject("player",player);
    collisionSystem->addGameObject("player",player);
    // Mansion
    for (int i = 0; i < 10; i++) {
        cout << i << endl;
        shared_ptr<Part> part = make_shared<Part>(i);
        std::string key = "part" + std::to_string(i);
        m_gameWorld->addGameObject(key,part);
        tickSystem->addGameObject(key,part);
        drawSystem->addGameObject(key,part);
        collisionSystem->addGameObject(key,part);
        navSystem->addGameObject(key,part);
    }

    collisionSystem->build();
}

void GameScreen::draw(Graphics *graphics) {
    m_gameWorld->getSystem<DrawSystem>()->draw();
}

void GameScreen::tick(float seconds) {
    m_gameWorld->getSystem<TickSystem>()->tick(seconds);
//    m_gameWorld->getSystem<BVHCollisionSystem>()->checkCollisions();
}
