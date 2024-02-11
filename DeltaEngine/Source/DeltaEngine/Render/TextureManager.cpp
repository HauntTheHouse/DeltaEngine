#include "DeltaEngine/Render/TextureManager.hpp"

namespace Delta
{

bool TextureManager::Init()
{
    // Do not needed any additional initialization for OpenGL
    return true;
}

void TextureManager::Clear()
{
    m_TextureManager.ForEach([](Texture2D& texture)
    {
        texture.Clear();
    });
    m_TextureManager.ReleaseAll();
}

HandleTexture TextureManager::Aquire(const TextureParams& texParams)
{
    HandleTexture handle;
    auto& texture = m_TextureManager.Acquire(handle);
    texture.Init(texParams);
    return handle;
}

void TextureManager::Release(HandleTexture handle)
{
    auto& texture = m_TextureManager.Dereference(handle);
    texture.Clear();

    m_TextureManager.Release(handle);
}

} // namespace Delta
