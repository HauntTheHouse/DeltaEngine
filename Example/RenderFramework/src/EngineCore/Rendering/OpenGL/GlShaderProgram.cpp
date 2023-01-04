#include "EngineCore/Rendering/OpenGL/GlShaderProgram.hpp"

#include <glad/glad.h>

bool GlShaderProgram::init(const char* aVertexShaderSrc, const char* aFragmentShaderSrc)
{
	if (mId != 0) return false;

	const GLuint vs = compileShader(aVertexShaderSrc, ShaderType::VERTEX);
	if (vs == 0) return false;
	const GLuint fs = compileShader(aFragmentShaderSrc, ShaderType::FRAGMENT);
	if (fs == 0) return false;

	mId = glCreateProgram();
	glAttachShader(mId, vs);
	glAttachShader(mId, fs);
	glLinkProgram(mId);

	GLint success;
	const GLsizei logSize = 256;
	GLchar infoLog[logSize];
	glGetProgramiv(mId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(mId, logSize, nullptr, infoLog);
		LOG_ERROR("Program linking failed\n{0}", infoLog);
		return false;
	}

	glDetachShader(mId, vs);
	glDetachShader(mId, fs);
	glDeleteShader(vs);
	glDeleteShader(fs);
}

void GlShaderProgram::clear()
{
	glDeleteProgram(mId);
	mId = 0;
}

void GlShaderProgram::bind() const
{
	assert(mId != 0);
	glUseProgram(mId);
}

void GlShaderProgram::unbind()
{
	glUseProgram(0);

}

GLuint GlShaderProgram::compileShader(const char* aSourceCode, ShaderType aShaderType)
{
	GLuint shader = glCreateShader(castToGLenum(aShaderType));
	glShaderSource(shader, 1, &aSourceCode, nullptr);
	glCompileShader(shader);

	GLint success;
	const GLsizei logSize = 256;
	GLchar infoLog[logSize];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, logSize, nullptr, infoLog);
		LOG_ERROR("{0} compilation failed\n{1}", getShaderTypeStr(aShaderType), infoLog);
		return 0;
	}

	return shader;
}

const char* GlShaderProgram::getShaderTypeStr(ShaderType aShaderType)
{
	switch (aShaderType)
	{
	case ShaderType::VERTEX: return "Vertex shader";
	case ShaderType::FRAGMENT: return "Fragment shader";
	default: return "Unknown shader";
	}
}

constexpr GLenum GlShaderProgram::castToGLenum(ShaderType aShaderType)
{
	switch (aShaderType)
	{
		case ShaderType::VERTEX: return GL_VERTEX_SHADER;
		case ShaderType::FRAGMENT: return GL_FRAGMENT_SHADER;
		default: return GL_NONE;
	}
}
