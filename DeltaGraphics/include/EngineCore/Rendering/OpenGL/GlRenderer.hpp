#pragma once

#include <Vec4.hpp>
#include "GlTypes.hpp"

struct GLFWwindow;

namespace Delta
{

class GlVertexArray;

class GlRenderer
{
public:
	static bool init(GLFWwindow* aWindow);

	static void draw(const GlVertexArray& aVertexArray);
	static void clearColor(const Vec4& aClearColor);
	static void clear();
	static void viewport(GLsizei aWidth, GLsizei aHeight, GLint aLeftOffset = 0, GLint aBottomOffset = 0);

	static const char* getVendorInfo();
	static const char* getRendererInfo();
	static const char* getVersionInfo();
};

} // namespace Delta
