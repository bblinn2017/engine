#include "playscreen.h"
#include <iostream>

using namespace std;
using namespace glm;

PlayScreen::PlayScreen(shared_ptr<Input> input) :
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
    // Ground
    shared_ptr<World> world = make_shared<World>();
    m_gameWorld->addGameObject("world",world);
    tickSystem->addGameObject("world",world);
    drawSystem->addGameObject("world",world);
    collisionSystem->addGameObject("world",world);
    navSystem->addGameObject("world",world);
    // Other
    for (int i = 0; i < NUM_OTHER; i++) {
        shared_ptr<Other> other = make_shared<Other>();
        m_gameWorld->addGameObject("other"+std::to_string(i),other);
        tickSystem->addGameObject("other"+std::to_string(i),other);
        drawSystem->addGameObject("other"+std::to_string(i),other);
        collisionSystem->addGameObject("other"+std::to_string(i),other);
    }

    setup();
    collisionSystem->build();
}

void PlayScreen::setup() {
    vector<shared_ptr<GameObject>> others;
    for (int i = 0; i < NUM_OTHER; i++) {
        others.push_back(getOther(i));
    }

    shared_ptr<GameObject> curr;
    for (int i = 0; i < NUM_OTHER; i++) {
        curr = others[i];
        vector<shared_ptr<GameObject>> temp(others);
        temp.erase(temp.begin()+i);
        temp.push_back(getPlayer());
        curr->addComponent<TagComponent>(make_shared<TagComponent>(curr,temp,getWorld()));
    }

    int tagger = std::rand() % others.size();
    others[tagger]->getComponent<TagComponent>()->setTagging(true);
    for (int i = 0; i < others.size(); i++) {
        if (i == tagger) continue;

        others[i]->getComponent<TagComponent>()->setTagger(others[tagger]);
    }
}

void PlayScreen::draw(Graphics *graphics) {
    m_gameWorld->getSystem<DrawSystem>()->draw();
}

void PlayScreen::tick(float seconds) {
    m_gameWorld->getSystem<TickSystem>()->tick(seconds);
    m_gameWorld->getSystem<BVHCollisionSystem>()->checkCollisions();
}
