#include "EngineCore/Application.hpp"
#include "EngineCore/EntryPoint.hpp"
#include "EngineCore/Input.hpp"

#include <imgui.h>
#include <Vec2.hpp>
#include <Vec3.hpp>

class Editor : public Delta::Application
{
public:
    Editor(unsigned int aWindowWidth, unsigned int aWindowHeight, const char* aTitle) : Application(aWindowWidth, aWindowHeight, aTitle)
    {
        mCamera.init(mCameraPosition, mCameraRotation);
        mCamera.setProjectionMode(mIsPerspectiveCamera ? Delta::Camera::ProjectionMode::PERSPECTIVE : Delta::Camera::ProjectionMode::ORTHO);
        mCamera.setAspect(aWindowWidth / static_cast<float>(aWindowHeight));
        mCamera.setFov(90.0f);
        mCamera.setNearFarPlanes(0.1f, 100.0f);
        mCamera.setOrthoPlanes(-8.0f, 8.0f, -8.0f, 8.0f);
    }

    void onUpdate() override
    {
        Delta::Vec3 movementDelta{ 0.0f, 0.0f, 0.0f };
        Delta::Vec3 rotationDelta{ 0.0f, 0.0f, 0.0f };

        if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_W))
            movementDelta.z += 0.05f;
        else if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_S))
            movementDelta.z -= 0.05f;
        if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_D))
            movementDelta.x += 0.05f;
        else if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_A))
            movementDelta.x -= 0.05f;

        if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_UP))
            rotationDelta.x -= 0.5f;
        else if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_DOWN))
            rotationDelta.x += 0.5f;
        if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_RIGHT))
            rotationDelta.y += 0.5f;
        else if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_LEFT))
            rotationDelta.y -= 0.5f;

        if (!ImGui::IsAnyItemActive())
        {
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
        }

        mCamera.move(movementDelta, rotationDelta);
    }

    void onGuiDraw() override
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                if (ImGui::MenuItem("New scene...")) {}
                if (ImGui::MenuItem("Open scene...")) {}
                if (ImGui::MenuItem("Save scene...")) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) { shouldClose(); }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

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
    Delta::Vec3 mCameraPosition{ 0.0f, 0.0f, 8.0f };
    Delta::Vec3 mCameraRotation{ 0.0f, 0.0f, 0.0f };
    bool mIsPerspectiveCamera{ true };

    Delta::Vec2 mInitCursorPosition;

};

Delta::Application* Delta::createApplication()
{
    return new Editor(1024, 768, "Editor");
}
