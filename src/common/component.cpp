#include "component.h"
#include "gameobject.h"

using namespace std;
using namespace glm;

Component::Component(GameObject *gameObject) :
    m_gameObject(gameObject)
{

}

void Component::tick(float seconds) {

}

void Component::setGraphics(Graphics * graphics) {

}


