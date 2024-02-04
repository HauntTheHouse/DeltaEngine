#pragma once

#include <Vec3.hpp>
#include <string>

namespace Delta
{

enum class Filter
{
    NEAREST,
    LINEAR,
    NEAREST_MIPMAP_NEAREST,
    LINEAR_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    LINEAR_MIPMAP_LINEAR
};

enum class WrapMode
{
    REPEAT,
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER,
    MIRRORED_REPEAT,
    MIRROR_CLAMP_TO_EDGE
};

enum class Format
{
    RED, RG, RGB, RGBA
};

struct SamplingParams
{
    Filter minFilter{ Filter::NEAREST_MIPMAP_NEAREST };
    Filter magFilter{ Filter::NEAREST };
    WrapMode wrap{ WrapMode::REPEAT };
};

struct ImageParams
{
    int width{ 256 };
    int height{ 256 };
    Format format{ Format::RGBA };
    unsigned char* data{ nullptr };
};

class Texture2D
{
public:
    Texture2D() = default;
    ~Texture2D() = default;
    Texture2D(Texture2D&) = delete;
    Texture2D& operator=(Texture2D&) = delete;

    bool Init(const ImageParams& imageParams, const SamplingParams& samplingParams = SamplingParams());
    void Clear();
    void Bind(unsigned int unit) const;

    void SetData(const unsigned char* data);

    static ImageParams Load(const std::string& path);

    static ImageParams GenerateCheckboard(int separationsNum);
    static ImageParams GenerateFillColor(const Vec3& color);

private:
    unsigned int m_Id{ 0 };
    int m_Width{};
    int m_Height{};

};

} // namespace Delta
