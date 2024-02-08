#include "DeltaEngine/Render/ShaderProgram.hpp"

#include "DeltaEngine/Log.hpp"
#include <glad/glad.h>

#include <fstream>
#include <sstream>

namespace Delta
{

namespace
{
    const char* toStrType(ShaderType shaderType)
    {
        switch (shaderType)
        {
        case ShaderType::VERTEX: return "Vertex shader";
        case ShaderType::FRAGMENT: return "Fragment shader";
        case ShaderType::GEOMETRY: return "Geometry shader";
        case ShaderType::TESS_EVALUATION: return "Tessellation evaluation shader";
        case ShaderType::TESS_CONTROL: return "Tessellation control shader";
        case ShaderType::COMPUTE: return "Compute shader";
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


void ShaderProgram::SetInt(const char* uniformName, const int val)
{
    glUniform1i(GetUniformLocation(uniformName), val);
}

void ShaderProgram::SetVec2i(const char* uniformName, const Vec2i& vec2)
{
    glUniform2iv(GetUniformLocation(uniformName), 1, vec2.toPtr());
}

void ShaderProgram::SetVec3i(const char* uniformName, const Vec3i& vec3)
{
    glUniform3iv(GetUniformLocation(uniformName), 1, vec3.toPtr());
}

void ShaderProgram::SetVec4i(const char* uniformName, const Vec4i& vec4)
{
    glUniform4iv(GetUniformLocation(uniformName), 1, vec4.toPtr());
}

void ShaderProgram::SetFloat(const char* uniformName, const float val)
{
    glUniform1f(GetUniformLocation(uniformName), val);
}

void ShaderProgram::SetVec2f(const char* uniformName, const Vec2f& vec2)
{
    glUniform2fv(GetUniformLocation(uniformName), 1, vec2.toPtr());
}

void ShaderProgram::SetVec3f(const char* uniformName, const Vec3f& vec3)
{
    glUniform3fv(GetUniformLocation(uniformName), 1, vec3.toPtr());
}

void ShaderProgram::SetVec4f(const char* uniformName, const Vec4f& vec4)
{
    glUniform4fv(GetUniformLocation(uniformName), 1, vec4.toPtr());
}

void ShaderProgram::SetMat2(const char* uniformName, const Mat2& mat2)
{
    glUniformMatrix2fv(GetUniformLocation(uniformName), 1, GL_FALSE, mat2.toPtr());
}

void ShaderProgram::SetMat3(const char* uniformName, const Mat3& mat3)
{
    glUniformMatrix3fv(GetUniformLocation(uniformName), 1, GL_FALSE, mat3.toPtr());
}

void ShaderProgram::SetMat4(const char* uniformName, const Mat4& mat4)
{
    glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, mat4.toPtr());
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
    GLuint shader = glCreateShader(static_cast<GLenum>(toNativeType(shaderType)));
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
