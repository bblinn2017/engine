#ifndef APPLICATION_H
#define APPLICATION_H

#include "engine/util/CommonIncludes.h"
#include "screen.h"

class Application {
public:
    Application();
    void setScreenSize(int w, int h);

    template <typename Type>
    void addScreen(std::shared_ptr<Type> &&s) {
        m_screens.put<Type>(std::forward<std::shared_ptr<Type>>(s));
    }
    template <typename Type>
    void removeScreen() {
        m_screens.remove<Type>();
    }
    template <typename Type>
    std::shared_ptr<Type> getScreen() {
        return std::static_pointer_cast<Type>(m_screens.find<Type>()->second);
    }
    template <typename Type>
    void setCurrScreen(int type) {
        m_currScreen = getScreen<Type>();
        m_currScreenType = type;
    }

    virtual void reset() = 0;

    std::shared_ptr<Input> getInput() {return m_input;}

    virtual void tick(float seconds);
    virtual void draw(Graphics *graphics);

    void setGraphics(Graphics *graphics);
    virtual void initializeCamera();
protected:
    TypeMap<std::shared_ptr<Screen>> m_screens;
    std::shared_ptr<Screen> m_currScreen;
    int m_currScreenType;

    std::shared_ptr<Input> m_input;

    Graphics * m_graphics;
};

#endif // APPLICATION_H
