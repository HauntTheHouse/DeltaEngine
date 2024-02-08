#include "DeltaEngine/Render/Renderer.hpp"

#include "DeltaEngine/Log.hpp"
#include "DeltaEngine/Render/VertexArray.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <DeltaEngine/Math/Vec4.hpp>

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

void Renderer::Draw(DrawPrimitive drawPrimitive, const VertexArray& vao)
{
    vao.Bind();
    vao.GetIndicesCount() > 0
        ? glDrawElements(
            static_cast<GLenum>(toNativeType(drawPrimitive)),
            static_cast<GLsizei>(vao.GetIndicesCount()),
            static_cast<GLenum>(toNativeType(vao.GetIndexDataType())),
            nullptr)
        : glDrawArrays(
            static_cast<GLenum>(toNativeType(drawPrimitive)),
            0,
            static_cast<GLsizei>(vao.GetVerticesCount()));
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

namespace
{
    static unsigned int s_BlendTargetId{ 0 };
}

void Renderer::SetBlendTarget(unsigned int id)
{
    s_BlendTargetId = id;
}

void Renderer::SetBlendFunc(BlendFunc srcFunc, BlendFunc dstFunc, BlendFunc srcFuncAlpha, BlendFunc dstFuncAlpha)
{
    glBlendFuncSeparatei(s_BlendTargetId,
        static_cast<GLenum>(toNativeType(srcFunc)),      static_cast<GLenum>(toNativeType(dstFunc)),
        static_cast<GLenum>(toNativeType(srcFuncAlpha)), static_cast<GLenum>(toNativeType(dstFuncAlpha)));
}

void Renderer::SetBlendEquation(BlendEquation modeRgb, BlendEquation modeAlpha)
{
    glBlendEquationSeparatei(s_BlendTargetId, static_cast<GLenum>(toNativeType(modeRgb)), static_cast<GLenum>(toNativeType(modeAlpha)));
}

void Renderer::SetBlendEnable(int id, bool enable)
{
    enable ? glEnablei(GL_BLEND, id) : glDisablei(GL_BLEND, id);
}

void Renderer::SetLogicOp(LogicOp logicOp)
{
    glLogicOp(static_cast<GLenum>(toNativeType(logicOp)));
}

void Renderer::SetDepthTestEnable(bool enable)
{
    enable ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void Renderer::SetDepthWriteEnable(bool enable)
{
    enable ? glDepthMask(GL_TRUE) : glDepthMask(GL_FALSE);
}

void Renderer::SetDepthFunc(Func func)
{
    glDepthFunc(static_cast<GLenum>(toNativeType(func)));
}

void Renderer::SetStencilTestEnable(bool enable)
{
    enable ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
}

void Renderer::SetStencilFunc(Face face, Func func, int ref, unsigned int mask)
{
    glStencilFuncSeparate(static_cast<GLenum>(toNativeType(face)), static_cast<GLenum>(toNativeType(func)), ref, mask);
}

void Renderer::SetStencilOp(Face faces, StencilOp fail, StencilOp depthFail, StencilOp depthPass)
{
    glStencilOpSeparate(
        static_cast<GLenum>(toNativeType(faces)), static_cast<GLenum>(toNativeType(fail)),
        static_cast<GLenum>(toNativeType(depthFail)), static_cast<GLenum>(toNativeType(depthPass)));
}

void Renderer::SetCullFace(Face face)
{
    glCullFace(static_cast<GLenum>(toNativeType(face)));
}

void Renderer::SetFrontFace(FrontFace frontFace)
{
    glFrontFace(static_cast<GLenum>(toNativeType(frontFace)));
}

void Renderer::SetPolygonMode(PolygonMode mode)
{
    glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(toNativeType(mode)));
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
