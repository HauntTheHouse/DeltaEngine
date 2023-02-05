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

    virtual void run();
    virtual void onUpdate() {};
    virtual void onGuiDraw() {};
    virtual void onMouseButtonEvent(MouseButtonCode aMouseButtonCode, double aPosX, double aPosY, bool aPressed) {};

    Vec2 getCursorPosition() const;

    void shouldClose();

protected:
    Camera mCamera;

private:
    Window mWindow;
    EventDispatcher mEventDispatcher;
    bool mIsShouldClose{ false };

};

Application* createApplication();

} // namespace Delta
