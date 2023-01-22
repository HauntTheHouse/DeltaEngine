#include "EngineCore/Input.hpp"

namespace Delta
{

std::array<bool, static_cast<size_t>(KeyCode::KEY_LAST) + 1> Input::mPressedKeys = {};
std::array<bool, static_cast<size_t>(MouseButtonCode::MOUSE_BUTTON_LAST) + 1> Input::mPressedMouseButtons = {};

bool Delta::Input::isKeyPressed(KeyCode aKeyCode)
{
    return mPressedKeys[static_cast<size_t>(aKeyCode)];
}

void Input::pressKey(KeyCode aKeyCode)
{
    mPressedKeys[static_cast<size_t>(aKeyCode)] = true;
}

void Input::releaseKey(KeyCode aKeyCode)
{
    mPressedKeys[static_cast<size_t>(aKeyCode)] = false;
}

bool Input::isMouseButtonPressed(MouseButtonCode aMouseButtonCode)
{
    return mPressedMouseButtons[static_cast<size_t>(aMouseButtonCode)];
}

void Input::pressMouseButton(MouseButtonCode aMouseButtonCode)
{
    mPressedMouseButtons[static_cast<size_t>(aMouseButtonCode)] = true;
}

void Input::releaseMouseButton(MouseButtonCode aMouseButtonCode)
{
    mPressedMouseButtons[static_cast<size_t>(aMouseButtonCode)] = false;
}

} // namespace Delta
