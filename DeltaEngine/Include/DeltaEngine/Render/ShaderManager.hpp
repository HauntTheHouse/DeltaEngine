#pragma once

#include "DeltaEngine/Singleton.hpp"
#include "DeltaEngine/HandleManager.hpp"
#include "ShaderProgram.hpp"

namespace Delta
{

using HandleShader = Handle<ShaderProgram>;

class ShaderManager : public Singleton<ShaderManager>
{
public:
    HandleShader Aquire(const ShaderTypePaths& shaderTypePaths);
    HandleShader Aquire(const std::string& binaryPath);

    void Release(HandleShader handle);

    inline ShaderProgram& Dereference(HandleShader handle)
    { return m_ShaderManager.Dereference(handle); }
    inline const ShaderProgram& Dereference(HandleShader handle) const
    { return m_ShaderManager.Dereference(handle); }

private:
    bool Init();
    void Clear();

    HandleManager<ShaderProgram, HandleShader> m_ShaderManager;

    friend class GraphicsSystem;
};

} // namespace Delta
