#pragma once

#include "ShaderManager.hpp"

namespace Delta
{

class GraphicsSystem
{
public:
    bool Init();
    void Clear();

private:
    ShaderManager m_ShaderManager;

};

} // namespace Delta
