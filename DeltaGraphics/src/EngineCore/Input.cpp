#include "EngineCore/Input.hpp"

namespace Delta
{

std::array<bool, static_cast<size_t>(KeyCode::KEY_LAST)> Input::mPressedKeys = {};

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

} // namespace Delta
