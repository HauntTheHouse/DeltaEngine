#pragma once

#include <Vec2.hpp>
#include "Keys.hpp"

namespace Delta
{

class Input
{
public:
    static bool isKeyPressed(KeyCode aKeyCode);
    static bool isMouseButtonPressed(MouseButtonCode aMouseButtonCode);
    static Vec2 getCursorPosition();

private:
    static void pressKey(KeyCode aKeyCode);
    static void releaseKey(KeyCode aKeyCode);

    static void pressMouseButton(MouseButtonCode aMouseButtonCode);
    static void releaseMouseButton(MouseButtonCode aMouseButtonCode);

    static void setCursorPosition(Vec2 aNewPosition);

    static std::array<bool, static_cast<size_t>(KeyCode::KEY_LAST) + 1> mPressedKeys;
    static std::array<bool, static_cast<size_t>(MouseButtonCode::MOUSE_BUTTON_LAST) + 1> mPressedMouseButtons;
    static Vec2 mCursorPosition;

    friend class Application;

};

}