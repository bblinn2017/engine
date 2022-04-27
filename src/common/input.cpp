#include "input.h"
#include "engine/util/CommonIncludes.h"

using namespace std;
using namespace glm;

Input::Input() :
    m_activeKeys(),
    m_activeMouseButtons(),
    m_mousePosition(),
    m_mouseDelta()
{
}

void Input::setScreenSize(int width, int height) {
    m_width = width;
    m_height = height;
}

void Input::mousePressEvent(QMouseEvent *event) {
    m_activeMouseButtons.insert(int(event->button()));
}
void Input::mouseMoveEvent(QMouseEvent *event) {
    setMouseDelta(glm::vec2(event->x(),event->y()));
}
void Input::mouseReleaseEvent(QMouseEvent *event) {
    m_activeMouseButtons.erase(int(event->button()));
}
void Input::wheelEvent(QWheelEvent *event) {

}
void Input::keyPressEvent(QKeyEvent *event) {
    m_activeKeys.insert(event->key());
}

void Input::keyRepeatEvent(QKeyEvent *event) {}

void Input::keyReleaseEvent(QKeyEvent *event) {
    m_activeKeys.erase(event->key());
}

bool Input::isKeyActive(int key) {return m_activeKeys.find(key) != m_activeKeys.end();}
bool Input::keyDeactivate(int key) {m_activeKeys.erase(key);}

glm::vec2 Input::getMouseDelta() {return m_mouseDelta;}
void Input::setMouseDelta(glm::vec2 newDelta) {m_mouseDelta = newDelta;}

int Input::getWidth() {return m_width;}
int Input::getHeight() {return m_height;}

void Input::reset() {
    m_activeKeys.empty();
    m_activeMouseButtons.empty();
    m_mousePosition = glm::vec2();
    m_mouseDelta = glm::vec2();
}
