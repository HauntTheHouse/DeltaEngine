#pragma once

#include "Singleton.hpp"
#include "Keys.hpp"
#include <DeltaEngine/Math/Vec2.hpp>
#include <array>

namespace Delta
{

class InputManager : public Singleton<InputManager>
{
private:
    void Init();

    bool IsKeyPressed(KeyCode keyCode);
    bool IsMouseButtonPressed(MouseButtonCode mouseButtonCode);
    Vec2f GetCursorPosition();

    void PressKey(KeyCode keyCode);
    void ReleaseKey(KeyCode keyCode);

    void PressMouseButton(MouseButtonCode mouseButtonCode);
    void ReleaseMouseButton(MouseButtonCode mouseButtonCode);

    void SetCursorPosition(Vec2f newPosition);

    static const size_t s_MaxKeys{ static_cast<size_t>(KeyCode::KEY_LAST) + 1 };
    std::array<bool, s_MaxKeys> m_PressedKeys;

    static const size_t s_MaxButtons{ static_cast<size_t>(MouseButtonCode::MOUSE_BUTTON_LAST) + 1 };
    std::array<bool, s_MaxButtons> m_PressedMouseButtons;

    Vec2f m_CursorPosition;

    friend class Application;
    friend class Input;

};

class Input
{
public:
    inline static bool IsKeyPressed(KeyCode keyCode)
    {
        return InputManager::GetInstance().IsKeyPressed(keyCode);
    }
    inline static bool IsMouseButtonPressed(MouseButtonCode mouseButtonCode)
    {
        return InputManager::GetInstance().IsMouseButtonPressed(mouseButtonCode);
    }
    inline static Vec2f GetCursorPosition()
    {
        return InputManager::GetInstance().GetCursorPosition();
    }
};

} // namespace Delta
