#pragma once

#include "Input.hpp"
#include <DeltaEngine/Math/Vec2.hpp>
#include <functional>
#include <string>

struct GLFWwindow;

namespace Delta
{

class EventBase;

class Window
{
public:
    using EventCallback = std::function<void(EventBase&)>;

    Window() = default;
    ~Window() = default;

    Window(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(const Window&&) = delete;

    int Init(unsigned int windowWidth, unsigned int windowHeight, const char* title);
    void Shutdown();
    void OnUpdate();

    unsigned int GetWidth() const { return m_Data.width; }
    unsigned int GetHeight() const { return m_Data.height; }

    void SetEventCallback(EventCallback eventCallbeck) { m_Data.eventCallback = std::move(eventCallbeck); }

private:
    struct WindowParameters
    {
        unsigned int width{ 0 };
        unsigned int height{ 0 };
        std::string title;
        EventCallback eventCallback;
    };

    GLFWwindow* m_Window{ nullptr };
    WindowParameters m_Data;

    friend class Input;
};

} // namespace Delta
