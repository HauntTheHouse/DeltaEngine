#pragma once

#include "GlTypes.hpp"

class GlShaderProgram
{
public:
	enum class ShaderType
	{
		VERTEX,
		FRAGMENT,
	};

	GlShaderProgram() = default;
	~GlShaderProgram() = default;
	GlShaderProgram(GlShaderProgram&) = delete;
	GlShaderProgram& operator=(GlShaderProgram&) = delete;

	bool init(const char* aVertexShaderSrc, const char* aFragmentShaderSrc);
	void clear();

	void bind() const;
	static void unbind();

private:
	static GLuint compileShader(const char* aSourceCode, ShaderType aShaderType);
	static const char* getShaderTypeStr(ShaderType aShaderType);
	constexpr static GLenum castToGLenum(ShaderType aShaderType);

	GLuint mId{ 0 };

};
