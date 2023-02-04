#include "EngineCore/Rendering/OpenGL/Renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Vec4.hpp>

#include "EngineCore/Rendering/OpenGL/VertexArray.hpp"

namespace Delta
{

bool Renderer::init(GLFWwindow* aWindow)
{
    glfwMakeContextCurrent(aWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("OpenGL context initialization failed");
        return false;
    }

    LOG_INFO("OpenGL context initialized succesfully");
    LOG_INFO("| Vendor: {0}", getVendorInfo());
    LOG_INFO("| Renderer: {0}", getRendererInfo());
    LOG_INFO("| Version: {0}", getVersionInfo());

    return true;
}

void Renderer::draw(const VertexArray& aVertexArray)
{
    aVertexArray.bind();
    aVertexArray.getIndicesCount() > 0
        ? glDrawElements(GL_TRIANGLES, aVertexArray.getIndicesCount(), GL_UNSIGNED_INT, nullptr)
        : glDrawArrays(GL_TRIANGLES, 0, aVertexArray.getVerticesCount());
    aVertexArray.unbind();
}

void Renderer::clearColor(const Vec4& aClearColor)
{
    glClearColor(aClearColor.x, aClearColor.y, aClearColor.z, aClearColor.w);
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::viewport(int aWidth, int aHeight, int aLeftOffset, int aBottomOffset)
{
    glViewport(aLeftOffset, aBottomOffset, aWidth, aHeight);
}

void Renderer::depthTesting(bool aEnable)
{
    aEnable ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

const char* Renderer::getVendorInfo()
{
    return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
}

const char* Renderer::getRendererInfo()
{
    return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
}

const char* Renderer::getVersionInfo()
{
    return reinterpret_cast<const char*>(glGetString(GL_VERSION));
}

} // namespace Delta
