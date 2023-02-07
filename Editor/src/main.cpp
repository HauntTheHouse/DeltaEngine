#include "EngineCore/Application.hpp"
#include "EngineCore/EntryPoint.hpp"
#include "EngineCore/Input.hpp"
#include "EngineCore/Time.hpp"
#include "EngineCore/Camera.hpp"
#include "EngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "EngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "EngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "EngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "EngineCore/Rendering/OpenGL/Texture2D.hpp"
#include "EngineCore/Rendering/OpenGL/Renderer.hpp"

#include <imgui.h>
#include <Vec2.hpp>
#include <Vec3.hpp>
#include <Mat4.hpp>

class Editor : public Delta::Application
{
public:
    Editor(unsigned int aWindowWidth, unsigned int aWindowHeight, const char* aTitle) : Application(aWindowWidth, aWindowHeight, aTitle)
    {
        std::vector<float> vertices = {
            // front side
           -1.0f,  -1.0f,  1.0f,  0.0f, 0.0f,
           -1.0f,   1.0f,  1.0f,  0.0f, 1.0f,
            1.0f,   1.0f,  1.0f,  1.0f, 1.0f,
            1.0f,  -1.0f,  1.0f,  1.0f, 0.0f,

            // left side
           -1.0f, -1.0f, -1.0f,   0.0f, 0.0f,
           -1.0f,  1.0f, -1.0f,   0.0f, 1.0f,
           -1.0f,  1.0f,  1.0f,   1.0f, 1.0f,
           -1.0f, -1.0f,  1.0f,   1.0f, 0.0f,

            // back side
            1.0f, -1.0f, -1.0f,   0.0f, 0.0f,
            1.0f,  1.0f, -1.0f,   0.0f, 1.0f,
           -1.0f,  1.0f, -1.0f,   1.0f, 1.0f,
           -1.0f, -1.0f, -1.0f,   1.0f, 0.0f,

           // right side
            1.0f, -1.0f,  1.0f,   0.0f, 0.0f,
            1.0f,  1.0f,  1.0f,   0.0f, 1.0f,
            1.0f,  1.0f, -1.0f,   1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,   1.0f, 0.0f,

             // up side
           -1.0f,  1.0f,  1.0f,   0.0f, 0.0f,
           -1.0f,  1.0f, -1.0f,   0.0f, 1.0f,
            1.0f,  1.0f, -1.0f,   1.0f, 1.0f,
            1.0f,  1.0f,  1.0f,   1.0f, 0.0f,

            // down side
           -1.0f, -1.0f, -1.0f,   0.0f, 0.0f,
           -1.0f, -1.0f,  1.0f,   0.0f, 1.0f,
            1.0f, -1.0f,  1.0f,   1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,   1.0f, 0.0f,
        };

        std::vector<unsigned int> indices = {
            0,  2,  1,
            0,  3,  2,

            4,  6,  5,
            4,  7,  6,

            8,  10, 9,
            8,  11, 10,

            12, 14, 13,
            12, 15, 14,

            16, 18, 17,
            16, 19, 18,

            20, 22, 21,
            20, 23, 22
        };

        mCamera.init({ 0.0f, 0.0f, 8.0f }, { 0.0f, 0.0f, 0.0f });
        mCamera.setProjectionMode(mIsPerspectiveCamera ? Delta::Camera::ProjectionMode::PERSPECTIVE : Delta::Camera::ProjectionMode::ORTHO);
        mCamera.setAspect(aWindowWidth / static_cast<float>(aWindowHeight));
        mCamera.setFov(90.0f);
        mCamera.setNearFarPlanes(0.1f, 100.0f);
        mCamera.setOrthoPlanes(-8.0f, 8.0f, -8.0f, 8.0f);

        mShaderProgram.init("assets/shaders/object.vert", "assets/shaders/object.frag");
        mShaderProgram.bind();

        Delta::BufferLayout layout({ Delta::ShaderData::Type::FLOAT3, Delta::ShaderData::Type::FLOAT2 });

        mVBO.init(vertices, layout);
        mEBO.init(indices);

        mVAO.init();
        mVAO.addVertexBuffer(mVBO);
        mVAO.setIndexBuffer(mEBO);

        const unsigned int width = 512;
        const unsigned int height = 512;

        mTextureCheckboard.init(width, height, Delta::Texture2D::generateCheckboard(width, height, 3, 8).data());
        mTexturePink.init(width, height, Delta::Texture2D::generateFillColor(width, height, 3, { 0.0f, 0.0f, 1.0f }).data());

        Delta::Renderer::depthTesting(true);
    }

    ~Editor() override
    {
        mEBO.clear();
        mVBO.clear();
        mVAO.clear();
        mShaderProgram.clear();
        mTextureCheckboard.clear();
        mTexturePink.clear();
    }

    void onUpdate(Delta::Timestep aTimestep) override
    {
        Delta::Vec3 movementDelta{ 0.0f, 0.0f, 0.0f };
        Delta::Vec3 rotationDelta{ 0.0f, 0.0f, 0.0f };

        if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_W))
            movementDelta.z += 2.0f * static_cast<float>(aTimestep);
        else if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_S))
            movementDelta.z -= 2.0f * static_cast<float>(aTimestep);
        if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_D))
            movementDelta.x += 2.0f * static_cast<float>(aTimestep);
        else if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_A))
            movementDelta.x -= 2.0f * static_cast<float>(aTimestep);

        if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_UP))
            rotationDelta.x -= 40.0f * static_cast<float>(aTimestep);
        else if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_DOWN))
            rotationDelta.x += 40.0f * static_cast<float>(aTimestep);
        if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_RIGHT))
            rotationDelta.y += 40.0f * static_cast<float>(aTimestep);
        else if (Delta::Input::isKeyPressed(Delta::KeyCode::KEY_LEFT))
            rotationDelta.y -= 40.0f * static_cast<float>(aTimestep);

        if (!ImGui::IsAnyItemActive())
        {
            if (Delta::Input::isMouseButtonPressed(Delta::MouseButtonCode::MOUSE_BUTTON_LEFT))
            {
                Delta::Vec2 currentCursorPostion = Delta::Input::getCursorPosition();
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

        Delta::Renderer::clearColor(Delta::Vec4(mBackgroundColor.x, mBackgroundColor.y, mBackgroundColor.z, 1.0f));
        Delta::Renderer::clear();

        static Delta::Vec3 translate(0.0f);
        static Delta::Vec3 angles(0.0f);
        static Delta::Vec3 scale(1.0f);

        Delta::Mat4 transformMat;
        transformMat.transform(translate, angles, scale);

        mShaderProgram.bind();
        {
            mShaderProgram.setMat4("uModel", transformMat);
            mShaderProgram.setMat4("uViewProject", mCamera.getViewProjection());

            mTextureCheckboard.bind(0);
            mShaderProgram.setInt("uDefaultTexture", 0);
            mTexturePink.bind(1);
            mShaderProgram.setInt("uPink", 1);

            Delta::Renderer::draw(mVAO);
        }
        mShaderProgram.unbind();
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

    void onWindowResizeEvent(unsigned int aNewWidth, unsigned int aNewHeight) override
    {
        mCamera.setAspect(aNewWidth / static_cast<float>(aNewHeight));
    }

    void onMouseButtonEvent(Delta::MouseButtonCode aMouseButtonCode, double aPosX, double aPosY, bool aPressed) override
    {
        mInitCursorPosition.x = static_cast<float>(aPosX);
        mInitCursorPosition.y = static_cast<float>(aPosY);
    }

private:
    Delta::Camera mCamera;

    Delta::ShaderProgram mShaderProgram;
    Delta::VertexBuffer mVBO;
    Delta::IndexBuffer mEBO;
    Delta::VertexArray mVAO;
    Delta::Texture2D mTextureCheckboard;
    Delta::Texture2D mTexturePink;

    Delta::Vec3 mBackgroundColor{ 0.66f, 0.86f, 1.0f };

    bool mIsPerspectiveCamera{ true };
    Delta::Vec2 mInitCursorPosition;

};

Delta::Application* Delta::createApplication()
{
    return new Editor(1024, 768, "Editor");
}
