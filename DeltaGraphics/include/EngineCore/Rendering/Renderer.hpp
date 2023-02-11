#pragma once

struct GLFWwindow;

namespace Delta
{

class VertexArray;
class Vec4;

class Renderer
{
public:
    static bool init(GLFWwindow* aWindow);

    static void draw(const VertexArray& aVertexArray);
    static void clearColor(const Vec4& aClearColor);
    static void clear();
    static void viewport(int aWidth, int aHeight, int aLeftOffset = 0, int aBottomOffset = 0);

    static void depthTesting(bool aEnable);

    static const char* getVendorInfo();
    static const char* getRendererInfo();
    static const char* getVersionInfo();

};

} // namespace Delta
