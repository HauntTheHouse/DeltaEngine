#include "DeltaEngine/EntryPoint.hpp"

#include "DeltaEngine/Render/ShaderManager.hpp"
#include "DeltaEngine/Render/TextureManager.hpp"
#include "DeltaEngine/Render/VertexArray.hpp"
#include "DeltaEngine/Render/VertexBuffer.hpp"
#include "DeltaEngine/Render/IndexBuffer.hpp"
#include "DeltaEngine/Render/Renderer.hpp"

#include "DeltaEngine/Camera.hpp"
#include "DeltaEngine/Time.hpp"
#include "DeltaEngine/Input.hpp"

#include <DeltaEngine/Math/Vec2.hpp>
#include <DeltaEngine/Math/Vec3.hpp>
#include <DeltaEngine/Math/Mat4.hpp>
#include <imgui.h>

#include "CubeData.hpp"

class Editor : public Delta::Application
{
public:
    Editor(unsigned int windowWidth, unsigned int windowHeight, const char* title) : Application(windowWidth, windowHeight, title)
    {
        m_Camera.Init({ 0.0f, 0.0f, 8.0f }, { 0.0f, 0.0f, 0.0f });
        m_Camera.SetProjectionMode(m_IsPerspectiveCamera ? Delta::Camera::ProjectionMode::PERSPECTIVE : Delta::Camera::ProjectionMode::ORTHO);
        m_Camera.SetAspect(windowWidth / static_cast<float>(windowHeight));
        m_Camera.SetFov(90.0f);
        m_Camera.SetNearFarPlanes(0.1f, 100.0f);
        m_Camera.SetOrthoPlanes(-8.0f, 8.0f, -8.0f, 8.0f);

        Delta::ShaderTypePaths paths;
        paths.vertexPath = "assets/shaders/object.vert";
        paths.fragmentPath = "assets/shaders/object.frag";
        m_HandleShader = Delta::ShaderManager::GetInstance().Aquire(paths);

        m_VBO.Init(CubeData::GetVertices(), CubeData::GetLayout());
        m_EBO.Init(CubeData::GetIndices());

        m_VAO.Init();
        m_VAO.AddVertexBuffer(m_VBO);
        m_VAO.SetIndexBuffer(m_EBO);


        Delta::TextureParams params;
        params.samplingParams.minFilter = Delta::MinFilter::LINEAR_MIPMAP_LINEAR;
        params.samplingParams.magFilter = Delta::MagFilter::LINEAR;
        params.imageParams = Delta::Texture2D::Load("assets/textures/brick_wall.png");
        m_HandleBrickWallTex = Delta::TextureManager::GetInstance().Aquire(params);

        params.imageParams = Delta::Texture2D::GenerateFillColor({ 1.0f, 0.0f, 1.0f });
        m_HandlePinkTex = Delta::TextureManager::GetInstance().Aquire(params);

        Delta::Renderer::SetDepthTestEnable(true);
    }

    ~Editor() override
    {
        m_EBO.Clear();
        m_VBO.Clear();
        m_VAO.Clear();

        Delta::TextureManager::GetInstance().Release(m_HandleBrickWallTex);
        Delta::TextureManager::GetInstance().Release(m_HandlePinkTex);
        Delta::ShaderManager::GetInstance().Release(m_HandleShader);
    }

    void OnUpdate(Delta::Timestep timestep) override
    {
        Delta::Vec3f movementDelta{ 0.0f, 0.0f, 0.0f };
        Delta::Vec3f rotationDelta{ 0.0f, 0.0f, 0.0f };

        float ts = timestep.GetSeconds<float>();
        if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_W))
            movementDelta.z += 2.0f * ts;
        else if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_S))
            movementDelta.z -= 2.0f * ts;
        if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_D))
            movementDelta.x += 2.0f * ts;
        else if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_A))
            movementDelta.x -= 2.0f * ts;

        if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_UP))
            rotationDelta.x -= 40.0f * ts;
        else if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_DOWN))
            rotationDelta.x += 40.0f * ts;
        if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_RIGHT))
            rotationDelta.y += 40.0f * ts;
        else if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_LEFT))
            rotationDelta.y -= 40.0f * ts;

        if (!ImGui::IsAnyItemActive())
        {
            if (Delta::Input::IsMouseButtonPressed(Delta::MouseButtonCode::MOUSE_BUTTON_LEFT))
            {
                Delta::Vec2f currentCursorPostion = Delta::Input::GetCursorPosition();
                if (Delta::Input::IsMouseButtonPressed(Delta::MouseButtonCode::MOUSE_BUTTON_RIGHT))
                {
                    movementDelta.x += (m_InitCursorPosition.x - currentCursorPostion.x) / 100.0f;
                    movementDelta.y -= (m_InitCursorPosition.y - currentCursorPostion.y) / 100.0f;
                }
                else
                {
                    rotationDelta.y -= (m_InitCursorPosition.x - currentCursorPostion.x) / 5.0f;
                    rotationDelta.x -= (m_InitCursorPosition.y - currentCursorPostion.y) / 5.0f;
                }
                m_InitCursorPosition = currentCursorPostion;
            }
        }

        m_Camera.Move(movementDelta, rotationDelta);

        Delta::Renderer::ClearColor(Delta::Vec4f(m_BackgroundColor.x, m_BackgroundColor.y, m_BackgroundColor.z, 1.0f));
        Delta::Renderer::Clear();

        static Delta::Vec3f translate(0.0f);
        static Delta::Vec3f angles(0.0f);
        static Delta::Vec3f scale(1.0f);

        Delta::Mat4 transformMat;
        transformMat.transform(translate, angles, scale);

        auto& shaderProgram = Delta::ShaderManager::GetInstance().Dereference(m_HandleShader);

        shaderProgram.Bind();
        {
            shaderProgram.SetMat4("uModel", transformMat);
            shaderProgram.SetMat4("uViewProject", m_Camera.GetViewProjection());

            auto& brickWallTex = Delta::TextureManager::GetInstance().Dereference(m_HandleBrickWallTex);
            shaderProgram.SetTexture("uDefaultTexture", brickWallTex, 0);

            auto& pinkTex = Delta::TextureManager::GetInstance().Dereference(m_HandlePinkTex);
            shaderProgram.SetTexture("uPink", pinkTex, 1);

            Delta::Renderer::Draw(Delta::DrawPrimitive::TRIANGLES, m_VAO);
        }
        shaderProgram.Unbind();
    }

    void OnGuiDraw() override
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                if (ImGui::MenuItem("New scene...")) {}
                if (ImGui::MenuItem("Open scene...")) {}
                if (ImGui::MenuItem("Save scene...")) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) { ShouldClose(); }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        ImGui::Begin("Camera");
        if (ImGui::Checkbox("Perspective projection", &m_IsPerspectiveCamera))
        {
            m_Camera.SetProjectionMode(m_IsPerspectiveCamera ? Delta::Camera::ProjectionMode::PERSPECTIVE : Delta::Camera::ProjectionMode::ORTHO);
        }
        ImGui::End();
    }

    void OnWindowResizeEvent(unsigned int newWidth, unsigned int newHeight) override
    {
        m_Camera.SetAspect(newWidth / static_cast<float>(newHeight));
    }

    void OnMouseButtonEvent(Delta::MouseButtonCode mouseButtonCode, float posX, float posY, bool pressed) override
    {
        m_InitCursorPosition.x = posX;
        m_InitCursorPosition.y = posY;
    }

private:
    Delta::Camera m_Camera;

    Delta::HandleShader m_HandleShader;
    Delta::HandleTexture m_HandleBrickWallTex;
    Delta::HandleTexture m_HandlePinkTex;
    Delta::VertexBuffer m_VBO;
    Delta::IndexBuffer m_EBO;
    Delta::VertexArray m_VAO;

    Delta::Vec3f m_BackgroundColor{ 0.66f, 0.86f, 1.0f };

    bool m_IsPerspectiveCamera{ true };
    Delta::Vec2f m_InitCursorPosition;

};

Delta::Application* Delta::CreateApplication()
{
    return new Editor(1024, 768, "Editor");
}
