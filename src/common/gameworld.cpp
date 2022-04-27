#include "gameworld.h"

using namespace std;
using namespace glm;

GameWorld::GameWorld() :
    m_gameObjects(),
    m_systems()
{
};

void GameWorld::setGraphics(Graphics * graphics) {
    for (auto gO : m_gameObjects) {
        gO.second->setGraphics(graphics);
    }
}
