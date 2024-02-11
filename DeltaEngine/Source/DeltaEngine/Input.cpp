#include "DeltaEngine/Input.hpp"

namespace Delta
{

void InputManager::Init()
{
    for (size_t i = 0; i < s_MaxKeys; ++i)
    {
        m_PressedKeys[i] = false;
    }
    for (size_t i = 0; i < s_MaxButtons; ++i)
    {
        m_PressedMouseButtons[i] = false;
    }
    m_CursorPosition = Vec2f(0.0f);
}

bool Delta::InputManager::IsKeyPressed(KeyCode keyCode)
{
    return m_PressedKeys[static_cast<size_t>(keyCode)];
}

bool InputManager::IsMouseButtonPressed(MouseButtonCode mouseButtonCode)
{
    return m_PressedMouseButtons[static_cast<size_t>(mouseButtonCode)];
}

Vec2f InputManager::GetCursorPosition()
{
    return m_CursorPosition;
}


void InputManager::PressKey(KeyCode keyCode)
{
    m_PressedKeys[static_cast<size_t>(keyCode)] = true;
}

void InputManager::ReleaseKey(KeyCode keyCode)
{
    m_PressedKeys[static_cast<size_t>(keyCode)] = false;
}

void InputManager::PressMouseButton(MouseButtonCode mouseButtonCode)
{
    m_PressedMouseButtons[static_cast<size_t>(mouseButtonCode)] = true;
}

void InputManager::ReleaseMouseButton(MouseButtonCode mouseButtonCode)
{
    m_PressedMouseButtons[static_cast<size_t>(mouseButtonCode)] = false;
}

void InputManager::SetCursorPosition(Vec2f newPosition)
{
    m_CursorPosition = newPosition;
}

} // namespace Delta
