#pragma once

#include <unordered_map>
#include <string>

namespace Delta
{

class Mat4;

class ShaderProgram
{
public:
    enum class ShaderType
    {
        VERTEX,
        FRAGMENT,
        GEOMETRY,
        TESS_EVALUATION,
        TESS_CONTROL,
        COMPUTE
    };

    ShaderProgram() = default;
    ~ShaderProgram() = default;
    ShaderProgram(ShaderProgram&) = delete;
    ShaderProgram& operator=(ShaderProgram&) = delete;

    bool Init(const char* vertexShaderPath, const char* fragmentShaderPath);
    bool InitFromSrc(const char* vertexShaderSrc, const char* fragmentShaderSrc);
    void Clear();

    void Bind() const;
    static void Unbind();

    void SetMat4(const char* uniformName, const Mat4& mat4);
    void SetInt(const char* uniformName, const int val);

    int GetUniformLocation(const char* uniformName);

private:
    static unsigned int CompileShader(const char* sourceCode, ShaderType shaderType);

    unsigned int m_Id{ 0 };
    std::unordered_map<std::string, int> m_UniformLocation;

};

} // namespace Delta
