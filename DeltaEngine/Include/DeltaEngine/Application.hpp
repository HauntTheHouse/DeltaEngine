#pragma once

#include "Window.hpp"
#include "Event.hpp"
#include "Time.hpp"

namespace Delta
{

class Application
{
public:
    Application(unsigned int windowWidth, unsigned int windowHeight, const char* title);
    virtual ~Application() {};

    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(const Application&&) = delete;

    void Run();
    void ShouldClose();

    virtual void OnUpdate(Timestep timestep) {};
    virtual void OnGuiDraw() {};

    virtual void OnWindowResizeEvent(unsigned int newWidth, unsigned int newHeight) {};
    virtual void OnMouseButtonEvent(MouseButtonCode mouseButtonCode, float posX, float posY, bool pressed) {};
    virtual void OnKeyEvent(KeyCode keyCode, bool pressed) {};
    virtual void OnMouseMoveEvent(float newPosX, float newPosY) {};
    virtual void OnMouseScrollEvent(float offsetX, float offsetY) {};

private:
    Window m_Window;
    EventDispatcher m_EventDispatcher;

    bool m_IsShouldClose{ false };

};

Application* CreateApplication();

} // namespace Delta
