#include "EngineCore/Rendering/OpenGL/ShaderProgram.hpp"

#include <glad/glad.h>
#include <Mat4.hpp>

namespace Delta
{

bool ShaderProgram::init(const char* aVertexShaderPath, const char* aFragmentShaderPath)
{
    auto const readFile = [](const char* path)
    {
        std::fstream file(path);
        std::stringstream stream;
        stream << file.rdbuf();
        return stream.str();
    };

    std::string vsStr = readFile(aVertexShaderPath);
    std::string fsStr = readFile(aFragmentShaderPath);

    return initFromSrc(vsStr.c_str(), fsStr.c_str());
}

bool ShaderProgram::initFromSrc(const char* aVertexShaderSrc, const char* aFragmentShaderSrc)
{
    if (mId != 0) return false;

    const GLuint vs = compileShader(aVertexShaderSrc, ShaderType::VERTEX);
    if (vs == 0) return false;
    const GLuint fs = compileShader(aFragmentShaderSrc, ShaderType::FRAGMENT);
    if (fs == 0) return false;

    mId = static_cast<unsigned int>(glCreateProgram());
    glAttachShader(static_cast<GLuint>(mId), vs);
    glAttachShader(static_cast<GLuint>(mId), fs);
    glLinkProgram(static_cast<GLuint>(mId));

    GLint success;
    const GLsizei logSize = 256;
    GLchar infoLog[logSize];
    glGetProgramiv(static_cast<GLuint>(mId), GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(static_cast<GLuint>(mId), logSize, nullptr, infoLog);
        LOG_ERROR("Program linking failed\n{0}", infoLog);
        return false;
    }

    glDetachShader(static_cast<GLuint>(mId), vs);
    glDetachShader(static_cast<GLuint>(mId), fs);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return true;
}

void ShaderProgram::clear()
{
    glDeleteProgram(static_cast<GLuint>(mId));
    mId = 0;
}

void ShaderProgram::bind() const
{
    assert(mId != 0);
    glUseProgram(static_cast<GLuint>(mId));
}

void ShaderProgram::unbind()
{
    glUseProgram(0);
}

void ShaderProgram::setMat4(const char* aUniformName, const Mat4& aMat4)
{
    glUniformMatrix4fv(getUniformLocation(aUniformName), 1, GL_FALSE, aMat4.toPtr());
}

void ShaderProgram::setInt(const char* aUniformName, const int aInt)
{
    glUniform1i(getUniformLocation(aUniformName), aInt);
}

int ShaderProgram::getUniformLocation(const char* aUniformName)
{
    const auto it = mUniformLocation.find(aUniformName);
    if (it != mUniformLocation.end()) return it->second;

    GLint uniformLocation = glGetUniformLocation(static_cast<GLuint>(mId), aUniformName);
    mUniformLocation.insert({ aUniformName, uniformLocation });
    return uniformLocation;
}

unsigned int ShaderProgram::compileShader(const char* aSourceCode, ShaderType aShaderType)
{
    GLuint shader = glCreateShader(static_cast<GLenum>(getRendererCode(aShaderType)));
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

    return static_cast<unsigned int>(shader);
}

const char* ShaderProgram::getShaderTypeStr(ShaderType aShaderType)
{
    switch (aShaderType)
    {
        case ShaderType::VERTEX: return "Vertex shader";
        case ShaderType::FRAGMENT: return "Fragment shader";
        default: return "Unknown shader";
    }
}

constexpr unsigned int ShaderProgram::getRendererCode(ShaderType aShaderType)
{
    switch (aShaderType)
    {
        case ShaderType::VERTEX: return GL_VERTEX_SHADER;
        case ShaderType::FRAGMENT: return GL_FRAGMENT_SHADER;
        default: return GL_NONE;
    }
}

} // namespace Delta
