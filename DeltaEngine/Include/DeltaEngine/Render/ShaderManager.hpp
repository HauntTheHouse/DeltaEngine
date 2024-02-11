#pragma once

#include "DeltaEngine/Singleton.hpp"
#include "DeltaEngine/HandleManager.hpp"
#include "ShaderProgram.hpp"

namespace Delta
{

using HandleShader = Handle<ShaderProgram>;
using ShaderManagerH = HandleManager<ShaderProgram, HandleShader>;

class ShaderManager : public Singleton<ShaderManager>
{
public:
    HandleShader Aquire(const ShaderTypePaths& shaderTypePaths);
    HandleShader Aquire(const std::string& binaryPath);

    void Release(HandleShader handle);

    ShaderProgram& Dereference(HandleShader handle);
    const ShaderProgram& Dereference(HandleShader handle) const;

private:
    bool Init();
    void Clear();

    ShaderManagerH m_ShaderManager;

    friend class GraphicsSystem;
};

} // namespace Delta
