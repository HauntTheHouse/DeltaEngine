#include "EngineCore/PCH.hpp"
#include "EngineCore/Application.hpp"

#include <imgui.h>
#include <cmrc/cmrc.hpp>

#include "EngineCore/Camera.hpp"
#include "EngineCore/Input.hpp"
#include "EngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "EngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "EngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "EngineCore/Rendering/OpenGL/VertexArray.hpp"

#include "EngineCore/Rendering/OpenGL/Renderer.hpp"
#include "EngineCore/Modules/GUIModule.hpp"

CMRC_DECLARE(shaders);

namespace Delta
{

std::vector<float> vertices = {
    // position           // color
    -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f
};

std::vector<unsigned int> indices = {
    0, 1, 2,
    2, 1, 3
};

ShaderProgram mShaderProgram;
VertexBuffer mVBO;
IndexBuffer mEBO;
VertexArray mVAO;

Vec3 mBackgroundColor{ 0.2f, 0.2f, 0.2f };

Vec3 translate(0.0f);
Vec3 angles(0.0f);
Vec3 scale(1.0f);

int Application::start(unsigned int aWindowWidth, unsigned int aWindowHeight, const char* aTitle)
{
    mWindow.init(aWindowWidth, aWindowHeight, aTitle);

    mEventDispatcher.addEventListener<WindowResizeEvent>([](WindowResizeEvent& event)
    {
        LOG_INFO("WindowResizeEvent: {0}x{1}", event.width, event.height);
    });
    mEventDispatcher.addEventListener<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& event)
    {
        Input::pressMouseButton(event.mMouseButton);
        onMouseButtonEvent(event.mMouseButton, event.x, event.y, true);
    });
    mEventDispatcher.addEventListener<MouseButtonReleasedEvent>([this](MouseButtonReleasedEvent& event)
    {
        Input::releaseMouseButton(event.mMouseButton);
        onMouseButtonEvent(event.mMouseButton, event.x, event.y, false);
    });
    mEventDispatcher.addEventListener<MouseMoveEvent>([](MouseMoveEvent& event)
    {
        //LOG_INFO("MouseMovedEvent: x = {0}, y = {1}", event.x, event.y);
    });
    mEventDispatcher.addEventListener<KeyPressedEvent>([](KeyPressedEvent& event)
    {
        Input::pressKey(event.mKeyCode);
    });
    mEventDispatcher.addEventListener<KeyReleasedEvent>([](KeyReleasedEvent& event)
    {
        Input::releaseKey(event.mKeyCode);
    });
    mEventDispatcher.addEventListener<WindowCloseEvent>([this](WindowCloseEvent& event)
    {
        LOG_INFO("MouseCloseEvent");
        mIsShouldClose = true;
    });

    mWindow.setEventCallback([this](EventBase& event)
    {
        mEventDispatcher.dispatch(event);
    });

    const auto fs = cmrc::shaders::get_filesystem();
    const auto vertShader = fs.open("shaders/object.vert");
    const auto fragShader = fs.open("shaders/object.frag");

    if (mShaderProgram.init(vertShader.begin(), fragShader.begin()) == false)
        return -4;

    BufferLayout layout({ ShaderData::Type::FLOAT3, ShaderData::Type::FLOAT3 });

    mVBO.init(vertices, layout);
    mEBO.init(indices);

    mVAO.init();
    mVAO.addVertexBuffer(mVBO);
    mVAO.setIndexBuffer(mEBO);

    while (!mIsShouldClose)
    {
        Renderer::clearColor(Vec4(mBackgroundColor.x, mBackgroundColor.y, mBackgroundColor.z, 1.0f));
        Renderer::clear();

        Mat4 transformMat;
        transformMat.transform(translate, angles, scale);

        mShaderProgram.bind();
        {
            mShaderProgram.setMat4("uModel", transformMat);
            mShaderProgram.setMat4("uViewProject", mCamera.getViewProjection());
            Renderer::draw(mVAO);
        }
        mShaderProgram.unbind();

        onUpdate();

        GUIModule::onDrawBegin();
        {
            GUIModule::ShowExampleAppDockSpace();
            //ImGui::ShowDemoWindow();
            ImGui::Begin("General properties");
            ImGui::ColorEdit3("Background color", mBackgroundColor.toPtr());
            ImGui::Separator();
            ImGui::SliderFloat3("Translate object", translate.toPtr(), -5.0f, 5.0f);
            ImGui::SliderFloat3("Rotate object", angles.toPtr(), -180.0f, 180.0f);
            ImGui::SliderFloat3("Scale object", scale.toPtr(), 0.0f, 2.0f);
            ImGui::Separator();
            ImGui::End();
            onGuiDraw();
        }
        GUIModule::onDrawEnd();

        mWindow.onUpdate();
    }

    mEBO.clear();
    mVBO.clear();
    mVAO.clear();
    mShaderProgram.clear();

    mWindow.shutdown();
    return 0;
}

Vec2 Application::getCursorPosition() const
{
    return mWindow.getCursorPosition();
}

}
