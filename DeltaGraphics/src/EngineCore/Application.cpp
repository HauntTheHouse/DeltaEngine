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
#include "EngineCore/Rendering/OpenGL/Texture2D.hpp"

#include "EngineCore/Rendering/OpenGL/Renderer.hpp"
#include "EngineCore/Modules/GUIModule.hpp"

CMRC_DECLARE(shaders);

namespace Delta
{

std::vector<float> vertices = {
    // front side
    -1.0f,  -1.0f,  1.0f,   0.0f, 0.0f,
    -1.0f,   1.0f,  1.0f,   0.0f, 1.0f,
     1.0f,   1.0f,  1.0f,   1.0f, 1.0f,
     1.0f,  -1.0f,  1.0f,   1.0f, 0.0f,

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

ShaderProgram mShaderProgram;
VertexBuffer mVBO;
IndexBuffer mEBO;
VertexArray mVAO;
Texture2D mTextureCheckboard;
Texture2D mTexturePink;

Vec3 mBackgroundColor{ 0.66f, 0.86f, 1.0f };

Vec3 translate(0.0f);
Vec3 angles(0.0f);
Vec3 scale(1.0f);

Application::Application(unsigned int aWindowWidth, unsigned int aWindowHeight, const char* aTitle)
{
    mWindow.init(aWindowWidth, aWindowHeight, aTitle);

    mEventDispatcher.addEventListener<WindowResizeEvent>([this](WindowResizeEvent& event)
    {
        onWindowResizeEvent(event.width, event.height);
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
    mEventDispatcher.addEventListener<KeyPressedEvent>([this](KeyPressedEvent& event)
    {
        Input::pressKey(event.keyCode);
        onKeyEvent(event.keyCode, true);
    });
    mEventDispatcher.addEventListener<KeyReleasedEvent>([this](KeyReleasedEvent& event)
    {
        Input::releaseKey(event.keyCode);
        onKeyEvent(event.keyCode, true);
    });
    mEventDispatcher.addEventListener<MouseMoveEvent>([this](MouseMoveEvent& event)
    {
        onMouseMoveEvent(event.x, event.y);
    });
    mEventDispatcher.addEventListener<MouseScrolledEvent>([this](MouseScrolledEvent& event)
    {
        onMouseScrollEvent(event.xOffset, event.yOffset);
    });
    mEventDispatcher.addEventListener<WindowCloseEvent>([this](WindowCloseEvent& event)
    {
        LOG_INFO("MouseCloseEvent");
        shouldClose();
    });

    mWindow.setEventCallback([this](EventBase& event)
    {
        mEventDispatcher.dispatch(event);
    });

    const auto fs = cmrc::shaders::get_filesystem();
    const auto vertShader = fs.open("shaders/object.vert");
    const auto fragShader = fs.open("shaders/object.frag");

    if (mShaderProgram.init(vertShader.begin(), fragShader.begin()) == false)
        exit(-4);

    BufferLayout layout({ ShaderData::Type::FLOAT3, ShaderData::Type::FLOAT2 });

    mShaderProgram.bind();

    const unsigned int width = 512;
    const unsigned int height = 512;

    mTextureCheckboard.init(width, height, Texture2D::generateCheckboard(width, height, 3, 8).data());
    mTexturePink.init(width, height, Texture2D::generateFillColor(width, height, 3, { 0.0f, 0.0f, 1.0f }).data());

    mVBO.init(vertices, layout);
    mEBO.init(indices);

    mVAO.init();
    mVAO.addVertexBuffer(mVBO);
    mVAO.setIndexBuffer(mEBO);
}

void Application::run()
{
    Renderer::depthTesting(true);

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

            mTextureCheckboard.bind(0);
            mShaderProgram.setInt("uDefaultTexture", 0);
            mTexturePink.bind(1);
            mShaderProgram.setInt("uPink", 1);

            Renderer::draw(mVAO);
        }
        mShaderProgram.unbind();

        GUIModule::onDrawBegin();
        {
            onGuiDraw();
        }
        GUIModule::onDrawEnd();

        onUpdate();

        mWindow.onUpdate();
    }

    mEBO.clear();
    mVBO.clear();
    mVAO.clear();
    mShaderProgram.clear();
    mTextureCheckboard.clear();
    mTexturePink.clear();

    mWindow.shutdown();
}

Vec2 Application::getCursorPosition() const
{
    return mWindow.getCursorPosition();
}

void Application::shouldClose()
{
    mIsShouldClose = true;
}

} // namespace Delta
