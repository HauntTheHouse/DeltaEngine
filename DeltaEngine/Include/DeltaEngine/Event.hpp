#pragma once

#include "Keys.hpp"
#include <functional>

namespace Delta
{

enum class EventType
{
    WINDOW_RESIZED_EVENT = 0,
    WINDOW_CLOSED_EVENT,

    KEY_PRESSED_EVENT,
    KEY_RESEASED_EVENT,

    MOUSE_BUTTON_PRESSED_EVENT,
    MOUSE_BUTTON_RELEASED_EVENT,
    MOUSE_MOVED_EVENT,
    MOUSE_SCROLLED_EVENT,

    EVENTS_COUNT
};


class EventBase
{
public:
    virtual ~EventBase() = default;
    virtual EventType GetType() const = 0;

    bool isHandled{ false };
};

class EventDispatcher
{
public:
    template<typename EventT>
    void AddEventListener(std::function<void(EventT&)> callback)
    {
        auto baseCallback = [func = std::move(callback)](EventBase& e)
        {
            if (e.GetType() == EventT::type)
            {
                func(static_cast<EventT&>(e));
            }
        };
        mEventCallbacks[static_cast<size_t>(EventT::type)] = std::move(baseCallback);
    }

    void Dispatch(EventBase& event)
    {
        auto& callback = mEventCallbacks[static_cast<size_t>(event.GetType())];
        if (callback)
        {
            callback(event);
            event.isHandled = true;
        }
    }

private:
    std::array<std::function<void(EventBase&)>, static_cast<size_t>(EventType::EVENTS_COUNT)> mEventCallbacks;
};


class WindowResizeEvent : public EventBase
{
public:
    WindowResizeEvent(const unsigned int width, const int unsigned height) : width(width), height(height) {}
    EventType GetType() const override { return type; }
    static const EventType type{ EventType::WINDOW_RESIZED_EVENT };

    unsigned int width;
    unsigned int height;
};

class MouseButtonPressedEvent : public EventBase
{
public:
    MouseButtonPressedEvent(MouseButtonCode aMouseButton, const float x, const float y) : mMouseButton(aMouseButton), x(x), y(y) {}
    EventType GetType() const override { return type; }
    static const EventType type{ EventType::MOUSE_BUTTON_PRESSED_EVENT };

    MouseButtonCode mMouseButton;
    float x;
    float y;
};

class MouseButtonReleasedEvent : public EventBase
{
public:
    MouseButtonReleasedEvent(MouseButtonCode aMouseButton, const float x, const float y) : mMouseButton(aMouseButton), x(x), y(y) {}
    EventType GetType() const override { return type; }
    static const EventType type{ EventType::MOUSE_BUTTON_RELEASED_EVENT };

    MouseButtonCode mMouseButton;
    float x;
    float y;
};

class MouseMoveEvent : public EventBase
{
public:
    MouseMoveEvent(const float x, const float y) : x(x), y(y) {}
    EventType GetType() const override { return type; }
    static const EventType type{ EventType::MOUSE_MOVED_EVENT };

    float x;
    float y;
};

class WindowCloseEvent : public EventBase
{
public:
    WindowCloseEvent() = default;
    EventType GetType() const override { return type; }
    static const EventType type{ EventType::WINDOW_CLOSED_EVENT };
};

class KeyPressedEvent : public EventBase
{
public:
    KeyPressedEvent(KeyCode keyCode, bool repeated) : keyCode(keyCode), repeated(repeated) {}
    EventType GetType() const override { return type; }
    static const EventType type{ EventType::KEY_PRESSED_EVENT };

    KeyCode keyCode;
    bool repeated;
};

class KeyReleasedEvent : public EventBase
{
public:
    KeyReleasedEvent(KeyCode keyCode) : keyCode(keyCode) {}
    EventType GetType() const override { return type; }
    static const EventType type{ EventType::KEY_RESEASED_EVENT };

    KeyCode keyCode;
};

class MouseScrolledEvent : public EventBase
{
public:
    MouseScrolledEvent(float xOffset, float yOffset) : xOffset(xOffset), yOffset(yOffset) {}
    EventType GetType() const override { return type; }
    static const EventType type{ EventType::MOUSE_SCROLLED_EVENT };

    float xOffset;
    float yOffset;
};

} // namespace Delta
