#pragma once

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
    };

    ShaderProgram() = default;
    ~ShaderProgram() = default;
    ShaderProgram(ShaderProgram&) = delete;
    ShaderProgram& operator=(ShaderProgram&) = delete;

    bool init(const char* aVertexShaderSrc, const char* aFragmentShaderSrc);
    void clear();

    void bind() const;
    static void unbind();

    void setMat4(const char* aUniformName, const Mat4& aMat4);

private:
    static unsigned int compileShader(const char* aSourceCode, ShaderType aShaderType);
    static const char* getShaderTypeStr(ShaderType aShaderType);
    constexpr static unsigned int getRendererCode(ShaderType aShaderType);

    unsigned int mId{ 0 };

};

} // namespace Delta
