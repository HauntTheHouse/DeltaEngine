#pragma once

#include "Keys.hpp"
#include <Vec2.hpp>
#include <array>

namespace Delta
{

class Input
{
public:
    static bool IsKeyPressed(KeyCode keyCode);
    static bool IsMouseButtonPressed(MouseButtonCode mouseButtonCode);
    static Vec2 GetCursorPosition();

private:
    static void PressKey(KeyCode keyCode);
    static void ReleaseKey(KeyCode keyCode);

    static void PressMouseButton(MouseButtonCode mouseButtonCode);
    static void ReleaseMouseButton(MouseButtonCode mouseButtonCode);

    static void SetCursorPosition(Vec2 newPosition);

    static std::array<bool, static_cast<size_t>(KeyCode::KEY_LAST) + 1> m_PressedKeys;
    static std::array<bool, static_cast<size_t>(MouseButtonCode::MOUSE_BUTTON_LAST) + 1> m_PressedMouseButtons;
    static Vec2 m_CursorPosition;

    friend class Application;

};

}