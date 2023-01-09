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

private:
    static std::array<bool, static_cast<size_t>(KeyCode::KEY_LAST)> mPressedKeys;

};

}