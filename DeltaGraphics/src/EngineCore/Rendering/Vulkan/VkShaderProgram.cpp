#include "EngineCore/Rendering/ShaderProgram.hpp"

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
    return false;
}

void ShaderProgram::clear()
{
}

void ShaderProgram::bind() const
{
}

void ShaderProgram::unbind()
{
}

void ShaderProgram::setMat4(const char* aUniformName, const Mat4& aMat4)
{
}

void ShaderProgram::setInt(const char* aUniformName, const int aInt)
{
}

int ShaderProgram::getUniformLocation(const char* aUniformName)
{
    return 0;
}

unsigned int ShaderProgram::compileShader(const char* aSourceCode, ShaderType aShaderType)
{
    return 0;
}

const char* ShaderProgram::getShaderTypeStr(ShaderType aShaderType)
{
    return "";
}

constexpr unsigned int ShaderProgram::getRendererCode(ShaderType aShaderType)
{
    return 0;
}

} // namespace Delta
