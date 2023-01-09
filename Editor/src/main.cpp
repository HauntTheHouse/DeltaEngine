#include "EngineCore/Application.hpp"

#include <imgui.h>
#include <Vec3.hpp>

class Editor : public Delta::Application
{
public:
    void onUpdate() override
    {
        mCamera.setTransform(cameraPosition, cameraRotation);
        mCamera.setProjectionMode(isPerspectiveCamera ? Delta::Camera::ProjectionMode::PERSPECTIVE : Delta::Camera::ProjectionMode::ORTHO);
    }
    void onGuiDraw() override
    {
        ImGui::Begin("Camera");
        ImGui::SliderFloat3("Position", cameraPosition.toPtr(), -5.0f, 5.0f);
        ImGui::SliderFloat3("Rotation", cameraRotation.toPtr(), -180.0f, 180.0f);
        ImGui::Checkbox("Perspective projection", &isPerspectiveCamera);
        ImGui::End();
    }

private:
    Delta::Vec3 cameraPosition{ 0.0f, 0.0f, 2.0f };
    Delta::Vec3 cameraRotation{ 0.0f, 0.0f, 0.0f };
    bool isPerspectiveCamera = false;

};

int main()
{
    const auto app = std::make_unique<Editor>();
    return app->start(1024, 768, "Editor");
}
