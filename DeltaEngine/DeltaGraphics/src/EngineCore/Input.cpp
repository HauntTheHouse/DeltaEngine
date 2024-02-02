#include "EngineCore/Input.hpp"

namespace Delta
{

std::array<bool, static_cast<size_t>(KeyCode::KEY_LAST) + 1> Input::m_PressedKeys = {};
std::array<bool, static_cast<size_t>(MouseButtonCode::MOUSE_BUTTON_LAST) + 1> Input::m_PressedMouseButtons = {};
Vec2 Input::m_CursorPosition{};


bool Delta::Input::IsKeyPressed(KeyCode keyCode)
{
    return m_PressedKeys[static_cast<size_t>(keyCode)];
}

bool Input::IsMouseButtonPressed(MouseButtonCode mouseButtonCode)
{
    return m_PressedMouseButtons[static_cast<size_t>(mouseButtonCode)];
}

Vec2 Input::GetCursorPosition()
{
    return m_CursorPosition;
}


void Input::PressKey(KeyCode keyCode)
{
    m_PressedKeys[static_cast<size_t>(keyCode)] = true;
}

void Input::ReleaseKey(KeyCode keyCode)
{
    m_PressedKeys[static_cast<size_t>(keyCode)] = false;
}

void Input::PressMouseButton(MouseButtonCode mouseButtonCode)
{
    m_PressedMouseButtons[static_cast<size_t>(mouseButtonCode)] = true;
}

void Input::ReleaseMouseButton(MouseButtonCode mouseButtonCode)
{
    m_PressedMouseButtons[static_cast<size_t>(mouseButtonCode)] = false;
}

void Input::SetCursorPosition(Vec2 newPosition)
{
    m_CursorPosition = newPosition;
}

} // namespace Delta
