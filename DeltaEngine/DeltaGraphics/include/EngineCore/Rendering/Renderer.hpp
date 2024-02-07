#pragma once

#include "GfxEnums.hpp"
#include "Color.hpp"

struct GLFWwindow;

namespace Delta
{

class VertexArray;

class Renderer
{
public:
    static bool Init(GLFWwindow* window);

    static void Draw(DrawPrimitive drawPrimitive, const VertexArray& vao);
    static void ClearColor(const Color& rgba);
    static void Clear();
    static void Viewport(int width, int height, int leftOffset = 0, int bottomOffset = 0);

    // Blend state
    static void SetBlendTarget(unsigned int id);
    static void SetBlendFunc(BlendFunc srcFunc, BlendFunc dstFunc, BlendFunc srcFuncAlpha, BlendFunc dstFuncAlpha);
    static void SetBlendEquation(BlendEquation modeRgb, BlendEquation modeAlpha);

    // Color state
    static void SetBlendEnable(int id, bool enable);
    static void SetLogicOp(LogicOp logicOp);

    // Depth Stencil state
    static void SetDepthTestEnable(bool enable);
    static void SetDepthWriteEnable(bool enable);
    static void SetDepthFunc(Func func);
    static void SetStencilTestEnable(bool enable);
    static void SetStencilFunc(Face face, Func func, int ref, unsigned int mask);
    static void SetStencilOp(Face faces, StencilOp fail, StencilOp depthFail, StencilOp depthPass);

    // Polygon state
    static void SetCullFace(Face face);
    static void SetFrontFace(FrontFace frontFace);
    static void SetPolygonMode(PolygonMode mode);

    static const char* GetVendorInfo();
    static const char* GetRendererInfo();
    static const char* GetVersionInfo();

};

} // namespace Delta
