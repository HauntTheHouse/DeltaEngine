#include "EngineCore/Rendering/Renderer.hpp"

#include "EngineCore/Log.hpp"
#include "EngineCore/Rendering/VertexArray.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Vec4.hpp>

namespace Delta
{

bool Renderer::Init(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("OpenGL context initialization failed");
        return false;
    }

    LOG_INFO("OpenGL context initialized succesfully");
    LOG_INFO("| Vendor: {0}", GetVendorInfo());
    LOG_INFO("| Renderer: {0}", GetRendererInfo());
    LOG_INFO("| Version: {0}", GetVersionInfo());

    return true;
}

void Renderer::Draw(const VertexArray& vertexArray)
{
    vertexArray.Bind();
    vertexArray.GetIndicesCount() > 0
        ? glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertexArray.GetIndicesCount()), GL_UNSIGNED_INT, nullptr)
        : glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexArray.GetVerticesCount()));
    vertexArray.Unbind();
}

void Renderer::ClearColor(const Vec4& clearColor)
{
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::Viewport(int width, int height, int leftOffset, int bottomOffset)
{
    glViewport(leftOffset, bottomOffset, width, height);
}

void Renderer::DepthTesting(bool enable)
{
    enable ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

const char* Renderer::GetVendorInfo()
{
    return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
}

const char* Renderer::GetRendererInfo()
{
    return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
}

const char* Renderer::GetVersionInfo()
{
    return reinterpret_cast<const char*>(glGetString(GL_VERSION));
}

} // namespace Delta
