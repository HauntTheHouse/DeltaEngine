#include "DeltaEngine/Render/ShaderManager.hpp"

#include "DeltaEngine/Render/GfxEnums.hpp"
#include "DeltaEngine/Utils.hpp"

namespace Delta
{

bool ShaderManager::Init()
{
    // Do not needed any additional initialization for OpenGL
    return true;
}

void ShaderManager::Clear()
{
    m_ShaderManager.ForEach([](ShaderProgram& shaderProgram)
    {
        shaderProgram.Clear();
    });
    m_ShaderManager.ReleaseAll();
}

HandleShader ShaderManager::Aquire(const ShaderTypePaths& shaderTypePaths)
{
    HandleShader handle;
    auto& shaderProgram = m_ShaderManager.Acquire(handle);
    shaderProgram.Init(shaderTypePaths);
    return handle;
}

HandleShader ShaderManager::Aquire(const std::string& binaryPath)
{
    HandleShader handle;
    auto& shaderProgram = m_ShaderManager.Acquire(handle);
    shaderProgram.Init(binaryPath);
    return handle;
}

void ShaderManager::Release(HandleShader handle)
{
    auto& shaderProgram = m_ShaderManager.Dereference(handle);
    shaderProgram.Clear();

    m_ShaderManager.Release(handle);
}

} // namespace Delta
