#include "EngineCore/Rendering/OpenGL/GlRenderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "EngineCore/Rendering/OpenGL/GlVertexArray.hpp"

namespace Delta
{

bool GlRenderer::init(GLFWwindow* aWindow)
{
	glfwMakeContextCurrent(aWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERROR("OpenGL context initialization failed");
		return false;
	}

	LOG_INFO("OpenGL context initialized succesfully");
	LOG_INFO("  Vendor: {0}", getVendorInfo());
	LOG_INFO("  Renderer: {0}", getRendererInfo());
	LOG_INFO("  Version: {0}", getVersionInfo());

	return true;
}

void GlRenderer::draw(const GlVertexArray& aVertexArray)
{
	aVertexArray.bind();
	aVertexArray.getIndicesCount() > 0
		? glDrawElements(GL_TRIANGLES, aVertexArray.getIndicesCount(), GL_UNSIGNED_INT, nullptr)
		: glDrawArrays(GL_TRIANGLES, 0, aVertexArray.getVerticesCount());
	aVertexArray.unbind();
}

void GlRenderer::clearColor(const Vec4& aClearColor)
{
	glClearColor(aClearColor.x, aClearColor.y, aClearColor.z, aClearColor.w);
}

void GlRenderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GlRenderer::viewport(GLsizei aWidth, GLsizei aHeight, GLint aLeftOffset, GLint aBottomOffset)
{
	glViewport(aLeftOffset, aBottomOffset, aWidth, aHeight);
}

const char* GlRenderer::getVendorInfo()
{
	return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
}

const char* GlRenderer::getRendererInfo()
{
	return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
}

const char* GlRenderer::getVersionInfo()
{
	return reinterpret_cast<const char*>(glGetString(GL_VERSION));
}

} // namespace Delta
