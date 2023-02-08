#pragma once

#include "Window.hpp"
#include "Event.hpp"
#include "Camera.hpp"
#include "Time.hpp"

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

    virtual void onUpdate(Timestep aTimestep) {};
    virtual void onGuiDraw() {};

    virtual void onWindowResizeEvent(unsigned int aNewWidth, unsigned int aNewHeight) {};
    virtual void onMouseButtonEvent(MouseButtonCode aMouseButtonCode, float aPosX, float aPosY, bool aPressed) {};
    virtual void onKeyEvent(KeyCode aKeyCode, bool aPressed) {};
    virtual void onMouseMoveEvent(float aNewPosX, float aNewPosY) {};
    virtual void onMouseScrollEvent(float aOffsetX, float aOffsetY) {};

private:
    Window mWindow;
    EventDispatcher mEventDispatcher;

    bool mIsShouldClose{ false };

};

Application* createApplication();

} // namespace Delta
