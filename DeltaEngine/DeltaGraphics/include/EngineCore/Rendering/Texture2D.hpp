#pragma once

#include "GfxEnums.hpp"
#include <DeltaMath/Vec3.hpp>
#include <string>

namespace Delta
{

struct ImageParams
{
    ImageParams() = default;
    ~ImageParams();
    ImageParams(const ImageParams& params);
    ImageParams& operator=(const ImageParams& params);
    ImageParams(ImageParams&& params) noexcept;
    ImageParams& operator=(ImageParams&& params) noexcept;

    int width{ 256 };
    int height{ 256 };
    Format format{ Format::RGBA };
    unsigned char* data{ nullptr };
};

struct SamplingParams
{
    MinFilter minFilter{ MinFilter::NEAREST_MIPMAP_NEAREST };
    MagFilter magFilter{ MagFilter::NEAREST };
    WrapMode wrap{ WrapMode::REPEAT };
};

struct TextureParams
{
    ImageParams imageParams{};
    SamplingParams samplingParams{};
    bool createMipmap{ true };
};

class Texture2D
{
public:
    Texture2D() = default;
    ~Texture2D() = default;
    Texture2D(Texture2D&) = delete;
    Texture2D& operator=(Texture2D&) = delete;

    bool Init(const TextureParams& texParams = TextureParams());
    void Clear();
    void Bind(unsigned int unit) const;

    void SetData(const unsigned char* data);

    static ImageParams Load(const std::string& path);
    static ImageParams Load(const char* path);

    static ImageParams GenerateCheckboard(int separationsNum);
    static ImageParams GenerateFillColor(const Vec3f& color);

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }

private:
    unsigned int m_Id{ 0 };
    int m_Width{};
    int m_Height{};

};

} // namespace Delta
