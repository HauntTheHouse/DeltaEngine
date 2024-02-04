#include "EngineCore/Application.hpp"
#include "EngineCore/EntryPoint.hpp"

#include "EngineCore/Camera.hpp"
#include "EngineCore/Time.hpp"
#include "EngineCore/Rendering/VertexArray.hpp"
#include "EngineCore/Rendering/Renderer.hpp"

#include "EngineCore/Input.hpp"
#include "EngineCore/Rendering/ShaderProgram.hpp"
#include "EngineCore/Rendering/VertexBuffer.hpp"
#include "EngineCore/Rendering/IndexBuffer.hpp"
#include "EngineCore/Rendering/Texture2D.hpp"

#include <imgui.h>
#include <Vec2.hpp>
#include <Vec3.hpp>
#include <Mat4.hpp>

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

        m_ShaderProgram.Init("assets/shaders/object.vert", "assets/shaders/object.frag");
        m_ShaderProgram.Bind();

        m_VBO.Init(CubeData::GetVertices(), CubeData::GetLayout());
        m_EBO.Init(CubeData::GetIndices());

        m_VAO.Init();
        m_VAO.AddVertexBuffer(m_VBO);
        m_VAO.SetIndexBuffer(m_EBO);


        //Delta::Texture2D::GenerateCheckboard(8);

        Delta::SamplingParams samplingParams{};
        samplingParams.minFilter = Delta::Filter::LINEAR_MIPMAP_LINEAR;
        samplingParams.magFilter = Delta::Filter::LINEAR;

        Delta::ImageParams imageParams = Delta::Texture2D::Load("assets/textures/brick_wall.png");
        m_BrickWallTex.Init(imageParams, samplingParams);

        imageParams = Delta::Texture2D::GenerateFillColor({ 0.0f, 0.0f, 1.0f });
        m_PinkTex.Init(imageParams);

        Delta::Renderer::DepthTesting(true);
    }

    ~Editor() override
    {
        m_EBO.Clear();
        m_VBO.Clear();
        m_VAO.Clear();
        m_ShaderProgram.Clear();
        m_BrickWallTex.Clear();
        m_PinkTex.Clear();
    }

    void OnUpdate(Delta::Timestep aTimestep) override
    {
        Delta::Vec3 movementDelta{ 0.0f, 0.0f, 0.0f };
        Delta::Vec3 rotationDelta{ 0.0f, 0.0f, 0.0f };

        if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_W))
            movementDelta.z += 2.0f * aTimestep;
        else if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_S))
            movementDelta.z -= 2.0f * aTimestep;
        if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_D))
            movementDelta.x += 2.0f * aTimestep;
        else if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_A))
            movementDelta.x -= 2.0f * aTimestep;

        if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_UP))
            rotationDelta.x -= 40.0f * aTimestep;
        else if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_DOWN))
            rotationDelta.x += 40.0f * aTimestep;
        if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_RIGHT))
            rotationDelta.y += 40.0f * aTimestep;
        else if (Delta::Input::IsKeyPressed(Delta::KeyCode::KEY_LEFT))
            rotationDelta.y -= 40.0f * aTimestep;

        if (!ImGui::IsAnyItemActive())
        {
            if (Delta::Input::IsMouseButtonPressed(Delta::MouseButtonCode::MOUSE_BUTTON_LEFT))
            {
                Delta::Vec2 currentCursorPostion = Delta::Input::GetCursorPosition();
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

        Delta::Renderer::ClearColor(Delta::Vec4(m_BackgroundColor.x, m_BackgroundColor.y, m_BackgroundColor.z, 1.0f));
        Delta::Renderer::Clear();

        static Delta::Vec3 translate(0.0f);
        static Delta::Vec3 angles(0.0f);
        static Delta::Vec3 scale(1.0f);

        Delta::Mat4 transformMat;
        transformMat.transform(translate, angles, scale);

        m_ShaderProgram.Bind();
        {
            m_ShaderProgram.SetMat4("uModel", transformMat);
            m_ShaderProgram.SetMat4("uViewProject", m_Camera.GetViewProjection());

            m_BrickWallTex.Bind(0);
            m_ShaderProgram.SetInt("uDefaultTexture", 0);
            m_PinkTex.Bind(1);
            m_ShaderProgram.SetInt("uPink", 1);

            Delta::Renderer::Draw(Delta::DrawPrimitive::TRIANGLES, m_VAO);
        }
        m_ShaderProgram.Unbind();
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

    Delta::ShaderProgram m_ShaderProgram;
    Delta::VertexBuffer m_VBO;
    Delta::IndexBuffer m_EBO;
    Delta::VertexArray m_VAO;
    Delta::Texture2D m_BrickWallTex;
    Delta::Texture2D m_PinkTex;

    Delta::Vec3 m_BackgroundColor{ 0.66f, 0.86f, 1.0f };

    bool m_IsPerspectiveCamera{ true };
    Delta::Vec2 m_InitCursorPosition;

};

Delta::Application* Delta::CreateApplication()
{
    return new Editor(1024, 768, "Editor");
}
