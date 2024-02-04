#include "EngineCore/Rendering/Renderer.hpp"

#include "EngineCore/Log.hpp"
#include "EngineCore/Rendering/VertexArray.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Vec4.hpp>

namespace Delta
{

namespace
{
    GLenum toGlType(IndexBuffer::DataType type)
    {
        switch (type)
        {
        case Delta::IndexBuffer::DataType::BYTE: return GL_BYTE;
        case Delta::IndexBuffer::DataType::UNSIGNED_BYTE: return GL_UNSIGNED_BYTE;
        case Delta::IndexBuffer::DataType::SHORT: return GL_SHORT;
        case Delta::IndexBuffer::DataType::UNSIGNED_SHORT: return GL_UNSIGNED_SHORT;
        case Delta::IndexBuffer::DataType::INT: return GL_INT;
        case Delta::IndexBuffer::DataType::UNSIGNED_INT: return GL_UNSIGNED_INT;
        default: return GL_NONE;
        }
    }

    GLenum toGltype(DrawPrimitive drawPrimitive)
    {
        switch (drawPrimitive)
        {
        case Delta::DrawPrimitive::POINTS: return GL_POINTS;
        case Delta::DrawPrimitive::LINES: return GL_LINES;
        case Delta::DrawPrimitive::LINE_LOOP: return GL_LINE_LOOP;
        case Delta::DrawPrimitive::LINE_STRIP: return GL_LINE_STRIP;
        case Delta::DrawPrimitive::TRIANGLES: return GL_TRIANGLES;
        case Delta::DrawPrimitive::TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
        case Delta::DrawPrimitive::TRIANGLE_FAN: return GL_TRIANGLE_FAN;
        case Delta::DrawPrimitive::QUADS: return GL_QUADS;
        case Delta::DrawPrimitive::LINES_ADJACENCY: return GL_LINES_ADJACENCY;
        case Delta::DrawPrimitive::LINE_STRIP_ADJACENCY: return GL_LINE_STRIP_ADJACENCY;
        case Delta::DrawPrimitive::TRIANGLES_ADJACENCY: return GL_TRIANGLES_ADJACENCY;
        case Delta::DrawPrimitive::TRIANGLE_STRIP_ADJACENCY: return GL_TRIANGLE_STRIP_ADJACENCY;
        case Delta::DrawPrimitive::PATCHES: return GL_PATCHES;
        default: return GL_NONE;
        }
    }
}

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

void Renderer::Draw(DrawPrimitive drawPrimitive, const VertexArray& vao)
{
    vao.Bind();
    vao.GetIndicesCount() > 0
        ? glDrawElements(toGltype(drawPrimitive), static_cast<GLsizei>(vao.GetIndicesCount()), toGlType(vao.GetIndexDataType()), nullptr)
        : glDrawArrays(toGltype(drawPrimitive), 0, static_cast<GLsizei>(vao.GetVerticesCount()));
    vao.Unbind();
}

void Renderer::ClearColor(const Color& rgba)
{
    glClearColor(rgba.r, rgba.g, rgba.b, rgba.a);
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
