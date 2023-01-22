#include "EngineCore/Application.hpp"
#include <EngineCore/Input.hpp>

#include <imgui.h>
#include <Vec2.hpp>
#include <Vec3.hpp>

class Editor : public Delta::Application
{
public:
    void init()
    {
        mCamera.init(mCameraPosition, mCameraRotation);
        mCamera.setProjectionMode(mIsPerspectiveCamera ? Delta::Camera::ProjectionMode::PERSPECTIVE : Delta::Camera::ProjectionMode::ORTHO);
    }

    void onUpdate() override
    {
        Delta::Vec3 movementDelta{ 0.0f, 0.0f, 0.0f };
        Delta::Vec3 rotationDelta{ 0.0f, 0.0f, 0.0f };

        if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_W))
            movementDelta.z += 0.01f;
        else if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_S))
            movementDelta.z -= 0.01f;
        if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_D))
            movementDelta.x += 0.01f;
        else if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_A))
            movementDelta.x -= 0.01f;

        if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_UP))
            rotationDelta.x -= 0.5f;
        else if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_DOWN))
            rotationDelta.x += 0.5f;
        if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_RIGHT))
            rotationDelta.y += 0.5f;
        else if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_LEFT))
            rotationDelta.y -= 0.5f;


        if (Delta::Input::isMouseButtonPressed(Delta::MouseButtonCode::MOUSE_BUTTON_LEFT))
        {
            Delta::Vec2 currentCursorPostion = getCursorPosition();
            if (Delta::Input::isMouseButtonPressed(Delta::MouseButtonCode::MOUSE_BUTTON_RIGHT))
            {
                movementDelta.x += (mInitCursorPosition.x - currentCursorPostion.x) / 100.0f;
                movementDelta.y -= (mInitCursorPosition.y - currentCursorPostion.y) / 100.0f;
            }
            else
            {
                rotationDelta.y -= (mInitCursorPosition.x - currentCursorPostion.x) / 5.0f;
                rotationDelta.x -= (mInitCursorPosition.y - currentCursorPostion.y) / 5.0f;
            }
            mInitCursorPosition = currentCursorPostion;
        }

        mCamera.move(movementDelta, rotationDelta);
    }

    void onGuiDraw() override
    {
        ImGui::Begin("Camera");
        if (ImGui::Checkbox("Perspective projection", &mIsPerspectiveCamera))
        {
            mCamera.setProjectionMode(mIsPerspectiveCamera ? Delta::Camera::ProjectionMode::PERSPECTIVE : Delta::Camera::ProjectionMode::ORTHO);
        }
        ImGui::End();
    }

    void onMouseButtonEvent(Delta::MouseButtonCode aMouseButtonCode, double aPosX, double aPosY, bool aPressed) override
    {
        mInitCursorPosition.x = static_cast<float>(aPosX);
        mInitCursorPosition.y = static_cast<float>(aPosY);
    }

private:
    Delta::Vec3 mCameraPosition{ 0.0f, 0.0f, 5.0f };
    Delta::Vec3 mCameraRotation{ 0.0f, 0.0f, 0.0f };
    bool mIsPerspectiveCamera{ true };

    Delta::Vec2 mInitCursorPosition;

};

int main()
{
    const auto app = std::make_unique<Editor>();
    app->init();
    return app->start(1024, 768, "Editor");
}
