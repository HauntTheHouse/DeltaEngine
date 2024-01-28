#pragma once

struct GLFWwindow;

namespace Delta
{

class VertexArray;
class Vec4;

class Renderer
{
public:
    static bool Init(GLFWwindow* window);

    static void Draw(const VertexArray& vertexArray);
    static void ClearColor(const Vec4& clearColor);
    static void Clear();
    static void Viewport(int width, int height, int leftOffset = 0, int bottomOffset = 0);

    static void DepthTesting(bool enable);

    static const char* GetVendorInfo();
    static const char* GetRendererInfo();
    static const char* GetVersionInfo();

};

} // namespace Delta
