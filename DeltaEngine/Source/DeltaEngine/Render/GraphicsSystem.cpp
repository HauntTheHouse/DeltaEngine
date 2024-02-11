#include "DeltaEngine/Render/GraphicsSystem.hpp"

namespace Delta
{

bool GraphicsSystem::Init()
{
    m_ShaderManager.Init();
    return true;
}

void GraphicsSystem::Clear()
{
    m_ShaderManager.Clear();
}

} // namespace Delta
