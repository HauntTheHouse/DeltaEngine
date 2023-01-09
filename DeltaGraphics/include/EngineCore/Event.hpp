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

    EVENTS_COUNT
};

class EventBase
{
public:
    virtual ~EventBase() = default;
    virtual EventType getType() const = 0;
};

class WindowResizeEvent : public EventBase
{
public:
    WindowResizeEvent(const unsigned int width, const int unsigned height) : width(width), height(height) {}
    EventType getType() const override { return type; }

    unsigned int width;
    unsigned int height;

    static const EventType type{ EventType::WINDOW_RESIZED };
};

class MouseMoveEvent : public EventBase
{
public:
    MouseMoveEvent(const double x, const double y) : x(x), y(y) {}
    EventType getType() const override { return type; }

    double x;
    double y;

    static const EventType type{ EventType::MOUSE_MOVED };
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
    KeyPressedEvent(KeyCode aKeyCode, bool aRepeated) : mKeyCode(aKeyCode), mRepeated(aRepeated) {}
    EventType getType() const override { return type; }

    KeyCode mKeyCode;
    bool mRepeated;

    static const EventType type{ EventType::KEY_PRESSED };
};

class KeyReleasedEvent : public EventBase
{
public:
    KeyReleasedEvent(KeyCode aKeyCode) : mKeyCode(aKeyCode) {}
    EventType getType() const override { return type; }

    KeyCode mKeyCode;

    static const EventType type{ EventType::KEY_RESEASED };
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
        }
    }

private:
    std::array<std::function<void(EventBase&)>, static_cast<size_t>(EventType::EVENTS_COUNT)> mEventCallbacks;
};

} // namespace Delta
