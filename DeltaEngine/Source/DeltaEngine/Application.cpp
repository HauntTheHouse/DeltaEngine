#include "DeltaEngine/Application.hpp"

#include <imgui.h>

#include "DeltaEngine/Input.hpp"
#include "DeltaEngine/Render/Renderer.hpp"
#include "DeltaEngine/Gui.hpp"

namespace Delta
{

Application::Application(unsigned int windowWidth, unsigned int windowHeight, const char* title)
{
    m_Window.Init(windowWidth, windowHeight, title);

    m_EventDispatcher.AddEventListener<WindowResizeEvent>([this](WindowResizeEvent& event)
    {
        OnWindowResizeEvent(event.width, event.height);
    });
    m_EventDispatcher.AddEventListener<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& event)
    {
        m_InputManager.PressMouseButton(event.mMouseButton);
        OnMouseButtonEvent(event.mMouseButton, event.x, event.y, true);
    });
    m_EventDispatcher.AddEventListener<MouseButtonReleasedEvent>([this](MouseButtonReleasedEvent& event)
    {
        m_InputManager.ReleaseMouseButton(event.mMouseButton);
        OnMouseButtonEvent(event.mMouseButton, event.x, event.y, false);
    });
    m_EventDispatcher.AddEventListener<KeyPressedEvent>([this](KeyPressedEvent& event)
    {
        m_InputManager.PressKey(event.keyCode);
        OnKeyEvent(event.keyCode, true);
    });
    m_EventDispatcher.AddEventListener<KeyReleasedEvent>([this](KeyReleasedEvent& event)
    {
        m_InputManager.ReleaseKey(event.keyCode);
        OnKeyEvent(event.keyCode, true);
    });
    m_EventDispatcher.AddEventListener<MouseMoveEvent>([this](MouseMoveEvent& event)
    {
        m_InputManager.SetCursorPosition(Vec2f(event.x, event.y));
        OnMouseMoveEvent(event.x, event.y);
    });
    m_EventDispatcher.AddEventListener<MouseScrolledEvent>([this](MouseScrolledEvent& event)
    {
        OnMouseScrollEvent(event.xOffset, event.yOffset);
    });
    m_EventDispatcher.AddEventListener<WindowCloseEvent>([this](WindowCloseEvent& event)
    {
        ShouldClose();
    });

    m_Window.SetEventCallback([this](EventBase& event)
    {
        m_EventDispatcher.Dispatch(event);
    });

    m_InputManager.Init();

    m_GraphicsSystem.Init();
}

Application::~Application()
{
    m_GraphicsSystem.Clear();
    m_Window.Shutdown();
}

void Application::Run()
{
    while (!m_IsShouldClose)
    {
        static float lastFrameTime = 0.0f;
        float time = Time::GetSeconds();
        Timestep timestep = time - lastFrameTime;
        lastFrameTime = time;

        OnUpdate(timestep);

        Gui::OnDrawBegin();
        OnGuiDraw();
        Gui::OnDrawEnd();

        m_Window.OnUpdate();
    }

}

void Application::ShouldClose()
{
    m_IsShouldClose = true;
}

} // namespace Delta
