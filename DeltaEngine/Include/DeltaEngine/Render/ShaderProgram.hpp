#pragma once

#include "GfxEnums.hpp"
#include <DeltaEngine/Math/Mat4.hpp>
#include <DeltaEngine/Math/Mat3.hpp>
#include <DeltaEngine/Math/Mat2.hpp>

#include <unordered_map>
#include <string>
#include <array>

namespace Delta
{

class Mat4;

struct ShaderTypePaths
{
    ShaderTypePaths() : vertexPath(), fragmentPath(), geometryPath(), tessEvaluaitionPath(), tessControlPath(), computePath() {}
    ~ShaderTypePaths() {}
    union
    {
        struct
        {
            std::string vertexPath;
            std::string fragmentPath;
            std::string geometryPath;
            std::string tessEvaluaitionPath;
            std::string tessControlPath;
            std::string computePath;
        };
        std::array<std::string, static_cast<size_t>(ShaderType::MAX_NUM)> shaderPaths;
    };
};

class ShaderProgram
{
public:
    ShaderProgram() = default;
    ~ShaderProgram() = default;

    void Bind() const;
    static void Unbind();

    void SetInt(const char* uniformName, const int val);
    void SetVec2i(const char* uniformName, const Vec2i& vec2);
    void SetVec3i(const char* uniformName, const Vec3i& vec3);
    void SetVec4i(const char* uniformName, const Vec4i& vec4);

    void SetFloat(const char* uniformName, const float val);
    void SetVec2f(const char* uniformName, const Vec2f& vec2);
    void SetVec3f(const char* uniformName, const Vec3f& vec3);
    void SetVec4f(const char* uniformName, const Vec4f& vec4);

    void SetMat2(const char* uniformName, const Mat2& mat2);
    void SetMat3(const char* uniformName, const Mat3& mat3);
    void SetMat4(const char* uniformName, const Mat4& mat4);

    int GetUniformLocation(const char* uniformName);

private:
    bool Init(const ShaderTypePaths& shaderTypePaths);
    bool Init(const std::string& binaryPath);

    void Clear();

    static unsigned int CompileShader(const std::string& sourceCode, ShaderType shaderType);
    static unsigned int CompileShader(const char* sourceCode, ShaderType shaderType);

    unsigned int m_Id{ 0 };
    std::unordered_map<std::string, int> m_UniformLocation;

    friend class ShaderManager;
};

} // namespace Delta
