#pragma once

#include "ShaderManager.hpp"
#include "TextureManager.hpp"

namespace Delta
{

class GraphicsSystem
{
public:
    bool Init();
    void Clear();

private:
    ShaderManager m_ShaderManager;
    TextureManager m_TextureManager;

};

} // namespace Delta
