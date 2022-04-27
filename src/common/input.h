#ifndef INPUT_H
#define INPUT_H

class QMouseEvent;
class QWheelEvent;
class QKeyEvent;

#include <glm/glm.hpp>
#include <set>

class Input {
public:
    Input();

    void setScreenSize(int width, int height);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyRepeatEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    bool isKeyActive(int key);
    bool keyDeactivate(int key);

    glm::vec2 getMouseDelta();
    void setMouseDelta(glm::vec2 newDelta);

    int getWidth();
    int getHeight();

    void reset();
private:
    std::set<int> m_activeKeys;
    std::set<int> m_activeMouseButtons;
    glm::vec2 m_mousePosition;
    glm::vec2 m_mouseDelta;

    int m_width, m_height;
};

#endif // INPUT_H
