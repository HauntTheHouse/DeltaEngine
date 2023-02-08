#pragma once

#include "Keys.hpp"

namespace Delta
{

enum class EventType
{
    WINDOW_RESIZED = 0,
    WINDOW_CLOSED,

    KEY_PRESSED,
    KEY_RESEASED,

    MOUSE_BUTTON_PRESSED,
    MOUSE_BUTTON_RELEASED,
    MOUSE_MOVED,
    MOUSE_SCROLLED,

    EVENTS_COUNT
};


class EventBase
{
public:
    virtual ~EventBase() = default;
    virtual EventType getType() const = 0;

    bool isHandled{ false };
};

class EventDispatcher
{
public:
    template<typename EventT>
    void addEventListener(std::function<void(EventT&)> callback)
    {
        auto baseCallback = [func = std::move(callback)](EventBase& e)
        {
            if (e.getType() == EventT::type)
            {
                func(static_cast<EventT&>(e));
            }
        };
        mEventCallbacks[static_cast<size_t>(EventT::type)] = std::move(baseCallback);
    }

    void dispatch(EventBase& event)
    {
        auto& callback = mEventCallbacks[static_cast<size_t>(event.getType())];
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
    EventType getType() const override { return type; }
    static const EventType type{ EventType::WINDOW_RESIZED };

    unsigned int width;
    unsigned int height;
};

class MouseButtonPressedEvent : public EventBase
{
public:
    MouseButtonPressedEvent(MouseButtonCode aMouseButton, const float x, const float y) : mMouseButton(aMouseButton), x(x), y(y) {}
    EventType getType() const override { return type; }
    static const EventType type{ EventType::MOUSE_BUTTON_PRESSED };

    MouseButtonCode mMouseButton;
    float x;
    float y;
};

class MouseButtonReleasedEvent : public EventBase
{
public:
    MouseButtonReleasedEvent(MouseButtonCode aMouseButton, const float x, const float y) : mMouseButton(aMouseButton), x(x), y(y) {}
    EventType getType() const override { return type; }
    static const EventType type{ EventType::MOUSE_BUTTON_RELEASED };

    MouseButtonCode mMouseButton;
    float x;
    float y;
};

class MouseMoveEvent : public EventBase
{
public:
    MouseMoveEvent(const float x, const float y) : x(x), y(y) {}
    EventType getType() const override { return type; }
    static const EventType type{ EventType::MOUSE_MOVED };

    float x;
    float y;
};

class WindowCloseEvent : public EventBase
{
public:
    WindowCloseEvent() = default;
    EventType getType() const override { return type; }
    static const EventType type{ EventType::WINDOW_CLOSED };
};

class KeyPressedEvent : public EventBase
{
public:
    KeyPressedEvent(KeyCode keyCode, bool repeated) : keyCode(keyCode), repeated(repeated) {}
    EventType getType() const override { return type; }
    static const EventType type{ EventType::KEY_PRESSED };

    KeyCode keyCode;
    bool repeated;
};

class KeyReleasedEvent : public EventBase
{
public:
    KeyReleasedEvent(KeyCode keyCode) : keyCode(keyCode) {}
    EventType getType() const override { return type; }
    static const EventType type{ EventType::KEY_RESEASED };

    KeyCode keyCode;
};

class MouseScrolledEvent : public EventBase
{
public:
    MouseScrolledEvent(float xOffset, float yOffset) : xOffset(xOffset), yOffset(yOffset) {}
    EventType getType() const override { return type; }
    static const EventType type{ EventType::MOUSE_SCROLLED };

    float xOffset;
    float yOffset;
};

} // namespace Delta
