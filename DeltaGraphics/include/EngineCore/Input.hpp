#pragma once

#include "Keys.hpp"

namespace Delta
{

class Input
{
public:
    static bool isKeyPressed(KeyCode aKeyCode);
    static void pressKey(KeyCode aKeyCode);
    static void releaseKey(KeyCode aKeyCode);

    static bool isMouseButtonPressed(MouseButtonCode aMouseButtonCode);
    static void pressMouseButton(MouseButtonCode aMouseButtonCode);
    static void releaseMouseButton(MouseButtonCode aMouseButtonCode);

private:
    static std::array<bool, static_cast<size_t>(KeyCode::KEY_LAST) + 1> mPressedKeys;
    static std::array<bool, static_cast<size_t>(MouseButtonCode::MOUSE_BUTTON_LAST) + 1> mPressedMouseButtons;

};

}