#pragma once

#include "Color.hpp"

struct GLFWwindow;

namespace Delta
{

class VertexArray;
class Vec4;

enum class DrawPrimitive
{
    POINTS,
    LINES,
    LINE_LOOP,
    LINE_STRIP,
    TRIANGLES,
    TRIANGLE_STRIP,
    TRIANGLE_FAN,
    QUADS,
    QUAD_STRIP,
    POLYGON,
    LINES_ADJACENCY,
    LINE_STRIP_ADJACENCY,
    TRIANGLES_ADJACENCY,
    TRIANGLE_STRIP_ADJACENCY,
    PATCHES,
};

class Renderer
{
public:
    static bool Init(GLFWwindow* window);

    static void Draw(DrawPrimitive drawPrimitive, const VertexArray& vao);
    static void ClearColor(const Color& rgba);
    static void Clear();
    static void Viewport(int width, int height, int leftOffset = 0, int bottomOffset = 0);

    static void DepthTesting(bool enable);

    static const char* GetVendorInfo();
    static const char* GetRendererInfo();
    static const char* GetVersionInfo();

};

} // namespace Delta
