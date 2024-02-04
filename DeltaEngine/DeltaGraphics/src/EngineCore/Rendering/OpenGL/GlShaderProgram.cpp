#include "EngineCore/Rendering/ShaderProgram.hpp"

#include "EngineCore/Log.hpp"
#include <glad/glad.h>
#include <Mat4.hpp>

#include <fstream>
#include <sstream>

namespace Delta
{

namespace
{
    GLenum toGlType(ShaderProgram::ShaderType shaderType)
    {
        switch (shaderType)
        {
        case ShaderProgram::ShaderType::VERTEX: return GL_VERTEX_SHADER;
        case ShaderProgram::ShaderType::FRAGMENT: return GL_FRAGMENT_SHADER;
        case ShaderProgram::ShaderType::GEOMETRY: return GL_GEOMETRY_SHADER;
        case ShaderProgram::ShaderType::TESS_EVALUATION: return GL_TESS_EVALUATION_SHADER;
        case ShaderProgram::ShaderType::TESS_CONTROL: return GL_TESS_CONTROL_SHADER;
        case ShaderProgram::ShaderType::COMPUTE: return GL_COMPUTE_SHADER;
        default: return GL_NONE;
        }
    }

    const char* toStrType(ShaderProgram::ShaderType shaderType)
    {
        switch (shaderType)
        {
        case ShaderProgram::ShaderType::VERTEX: return "Vertex shader";
        case ShaderProgram::ShaderType::FRAGMENT: return "Fragment shader";
        case ShaderProgram::ShaderType::GEOMETRY: return "Geometry shader";
        case ShaderProgram::ShaderType::TESS_EVALUATION: return "Tessellation evaluation shader";
        case ShaderProgram::ShaderType::TESS_CONTROL: return "Tessellation control shader";
        case ShaderProgram::ShaderType::COMPUTE: return "Compute shader";
        default: return "Unknown shader";
        }
    }
}

bool ShaderProgram::Init(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    auto const readFile = [](const char* path)
    {
        std::fstream file(path);
        std::stringstream stream;
        stream << file.rdbuf();
        return stream.str();
    };

    std::string vsStr = readFile(vertexShaderPath);
    std::string fsStr = readFile(fragmentShaderPath);

    return InitFromSrc(vsStr.c_str(), fsStr.c_str());
}

bool ShaderProgram::InitFromSrc(const char* vertexShaderSrc, const char* fragmentShaderSrc)
{
    if (m_Id != 0) return false;

    const GLuint vs = CompileShader(vertexShaderSrc, ShaderType::VERTEX);
    if (vs == 0) return false;
    const GLuint fs = CompileShader(fragmentShaderSrc, ShaderType::FRAGMENT);
    if (fs == 0) return false;

    m_Id = static_cast<unsigned int>(glCreateProgram());
    glAttachShader(static_cast<GLuint>(m_Id), vs);
    glAttachShader(static_cast<GLuint>(m_Id), fs);
    glLinkProgram(static_cast<GLuint>(m_Id));

    GLint success;
    const GLsizei logSize = 256;
    GLchar infoLog[logSize];
    glGetProgramiv(static_cast<GLuint>(m_Id), GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(static_cast<GLuint>(m_Id), logSize, nullptr, infoLog);
        LOG_ERROR("Program linking failed\n{0}", infoLog);
        return false;
    }

    glDetachShader(static_cast<GLuint>(m_Id), vs);
    glDetachShader(static_cast<GLuint>(m_Id), fs);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return true;
}

void ShaderProgram::Clear()
{
    glDeleteProgram(static_cast<GLuint>(m_Id));
    m_Id = 0;
}

void ShaderProgram::Bind() const
{
    assert(m_Id != 0);
    glUseProgram(static_cast<GLuint>(m_Id));
}

void ShaderProgram::Unbind()
{
    glUseProgram(0);
}

void ShaderProgram::SetMat4(const char* uniformName, const Mat4& mat4)
{
    glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, mat4.toPtr());
}

void ShaderProgram::SetInt(const char* uniformName, const int val)
{
    glUniform1i(GetUniformLocation(uniformName), val);
}

int ShaderProgram::GetUniformLocation(const char* uniformName)
{
    const auto it = m_UniformLocation.find(uniformName);
    if (it != m_UniformLocation.end()) return it->second;

    GLint uniformLocation = glGetUniformLocation(static_cast<GLuint>(m_Id), uniformName);
    m_UniformLocation.insert({ uniformName, uniformLocation });
    return uniformLocation;
}

unsigned int ShaderProgram::CompileShader(const char* sourceCode, ShaderType shaderType)
{
    GLuint shader = glCreateShader(static_cast<GLenum>(toGlType(shaderType)));
    glShaderSource(shader, 1, &sourceCode, nullptr);
    glCompileShader(shader);

    GLint success;
    const GLsizei logSize = 256;
    GLchar infoLog[logSize];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, logSize, nullptr, infoLog);
        LOG_ERROR("{0} compilation failed\n{1}", toStrType(shaderType), infoLog);
        return 0;
    }

    return static_cast<unsigned int>(shader);
}

} // namespace Delta
