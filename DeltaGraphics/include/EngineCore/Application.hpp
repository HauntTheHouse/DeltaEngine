#pragma once

#include "Window.hpp"
#include "Event.hpp"
#include "Camera.hpp"

namespace Delta
{

class Application
{
public:
    Application(unsigned int aWindowWidth, unsigned int aWindowHeight, const char* aTitle);
    virtual ~Application() {};

    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(const Application&&) = delete;

    void run();
    void shouldClose();

    virtual void onUpdate() {};
    virtual void onGuiDraw() {};

    virtual void onWindowResizeEvent(unsigned int aNewWidth, unsigned int aNewHeight) {};
    virtual void onMouseButtonEvent(MouseButtonCode aMouseButtonCode, double aPosX, double aPosY, bool aPressed) {};
    virtual void onKeyEvent(KeyCode aKeyCode, bool aPressed) {};
    virtual void onMouseMoveEvent(double aNewPosX, double aNewPosY) {};
    virtual void onMouseScrollEvent(double aOffsetX, double aOffsetY) {};

private:
    Window mWindow;
    EventDispatcher mEventDispatcher;

    bool mIsShouldClose{ false };

};

Application* createApplication();

} // namespace Delta
