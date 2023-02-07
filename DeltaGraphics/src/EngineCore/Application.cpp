#include "EngineCore/PCH.hpp"
#include "EngineCore/Application.hpp"

#include <imgui.h>
#include <cmrc/cmrc.hpp>

#include "EngineCore/Camera.hpp"
#include "EngineCore/Input.hpp"
#include "EngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "EngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "EngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "EngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "EngineCore/Rendering/OpenGL/Texture2D.hpp"

#include "EngineCore/Rendering/OpenGL/Renderer.hpp"
#include "EngineCore/Modules/GUIModule.hpp"

namespace Delta
{

Application::Application(unsigned int aWindowWidth, unsigned int aWindowHeight, const char* aTitle)
{
    mWindow.init(aWindowWidth, aWindowHeight, aTitle);

    mEventDispatcher.addEventListener<WindowResizeEvent>([this](WindowResizeEvent& event)
    {
        onWindowResizeEvent(event.width, event.height);
    });
    mEventDispatcher.addEventListener<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& event)
    {
        Input::pressMouseButton(event.mMouseButton);
        onMouseButtonEvent(event.mMouseButton, event.x, event.y, true);
    });
    mEventDispatcher.addEventListener<MouseButtonReleasedEvent>([this](MouseButtonReleasedEvent& event)
    {
        Input::releaseMouseButton(event.mMouseButton);
        onMouseButtonEvent(event.mMouseButton, event.x, event.y, false);
    });
    mEventDispatcher.addEventListener<KeyPressedEvent>([this](KeyPressedEvent& event)
    {
        Input::pressKey(event.keyCode);
        onKeyEvent(event.keyCode, true);
    });
    mEventDispatcher.addEventListener<KeyReleasedEvent>([this](KeyReleasedEvent& event)
    {
        Input::releaseKey(event.keyCode);
        onKeyEvent(event.keyCode, true);
    });
    mEventDispatcher.addEventListener<MouseMoveEvent>([this](MouseMoveEvent& event)
    {
        Input::setCursorPosition(Vec2(event.x, event.y));
        onMouseMoveEvent(event.x, event.y);
    });
    mEventDispatcher.addEventListener<MouseScrolledEvent>([this](MouseScrolledEvent& event)
    {
        onMouseScrollEvent(event.xOffset, event.yOffset);
    });
    mEventDispatcher.addEventListener<WindowCloseEvent>([this](WindowCloseEvent& event)
    {
        shouldClose();
    });

    mWindow.setEventCallback([this](EventBase& event)
    {
        mEventDispatcher.dispatch(event);
    });
}

void Application::run()
{
    Renderer::depthTesting(true);

    while (!mIsShouldClose)
    {
        onUpdate();

        GUIModule::onDrawBegin();
        onGuiDraw();
        GUIModule::onDrawEnd();

        mWindow.onUpdate();
    }

    mWindow.shutdown();
}

void Application::shouldClose()
{
    mIsShouldClose = true;
}

} // namespace Delta
