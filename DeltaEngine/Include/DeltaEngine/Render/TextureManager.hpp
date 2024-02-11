#pragma once

#include "DeltaEngine/Singleton.hpp"
#include "DeltaEngine/HandleManager.hpp"
#include "Texture2D.hpp"

namespace Delta
{

using HandleTexture = Handle<Texture2D>;

class TextureManager : public Singleton<TextureManager>
{
public:
    HandleTexture Aquire(const TextureParams& texParams = TextureParams());
    void Release(HandleTexture handle);

    inline Texture2D& Dereference(HandleTexture handle)
    { return m_TextureManager.Dereference(handle); }
    inline const Texture2D& Dereference(HandleTexture handle) const
    { return m_TextureManager.Dereference(handle); }

private:
    bool Init();
    void Clear();

    HandleManager<Texture2D, HandleTexture> m_TextureManager;

    friend class GraphicsSystem;
};

} // namespace Delta
