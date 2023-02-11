#include "EngineCore/Rendering/OpenGL/Renderer.hpp"

#include "EngineCore/Rendering/OpenGL/VertexArray.hpp"

namespace Delta
{

bool Renderer::init(GLFWwindow* aWindow)
{
    return true;
}

void Renderer::draw(const VertexArray& aVertexArray)
{
}

void Renderer::clearColor(const Vec4& aClearColor)
{
}

void Renderer::clear()
{
}

void Renderer::viewport(int aWidth, int aHeight, int aLeftOffset, int aBottomOffset)
{
}

void Renderer::depthTesting(bool aEnable)
{
}

const char* Renderer::getVendorInfo()
{
    return "";
}

const char* Renderer::getRendererInfo()
{
    return "";
}

const char* Renderer::getVersionInfo()
{
    return "";
}

} // namespace Delta
