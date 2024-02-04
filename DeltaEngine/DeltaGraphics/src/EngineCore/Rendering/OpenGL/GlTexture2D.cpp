#include "EngineCore/Rendering/Texture2D.hpp"

#include <stb_image.h>
#include <glad/glad.h>

namespace Delta
{

namespace
{
    GLint toGlFilter(Filter filter)
    {
        switch (filter)
        {
        case Delta::Filter::NEAREST:                return GL_NEAREST;
        case Delta::Filter::LINEAR:                 return GL_LINEAR;
        case Delta::Filter::NEAREST_MIPMAP_NEAREST: return GL_NEAREST_MIPMAP_NEAREST;
        case Delta::Filter::LINEAR_MIPMAP_NEAREST:  return GL_LINEAR_MIPMAP_NEAREST;
        case Delta::Filter::NEAREST_MIPMAP_LINEAR:  return GL_NEAREST_MIPMAP_LINEAR;
        case Delta::Filter::LINEAR_MIPMAP_LINEAR:   return GL_LINEAR_MIPMAP_LINEAR;
        default: return GL_NONE;
        }
    }

    GLint toGlWrap(WrapMode wrap)
    {
        switch (wrap)
        {
        case Delta::WrapMode::REPEAT:               return GL_REPEAT;
        case Delta::WrapMode::CLAMP_TO_EDGE:        return GL_CLAMP_TO_EDGE;
        case Delta::WrapMode::CLAMP_TO_BORDER:      return GL_CLAMP_TO_BORDER;
        case Delta::WrapMode::MIRRORED_REPEAT:      return GL_MIRRORED_REPEAT;
        case Delta::WrapMode::MIRROR_CLAMP_TO_EDGE: return GL_MIRROR_CLAMP_TO_EDGE;
        default: return GL_NONE;
        }
    }

    GLint toGlFormat(Format format)
    {
        switch (format)
        {
        case Delta::Format::RED: return GL_RED;
        case Delta::Format::RG: return GL_RG;
        case Delta::Format::RGB: return GL_RGB;
        case Delta::Format::RGBA: return GL_RGBA;
        default: return GL_NONE;
        }
    }
}


bool Texture2D::Init(const ImageParams& imageParams, const SamplingParams& samplingParams)
{
    if (m_Id != 0) return false;

    ImageParams tmpParams = imageParams;
    if (!tmpParams.data)
    {
        tmpParams = GenerateCheckboard(8);
    }

    m_Width = tmpParams.width;
    m_Height = tmpParams.height;

    GLint format = toGlFormat(tmpParams.format);

    glGenTextures(1, static_cast<GLuint*>(&m_Id));
    glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(m_Id));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toGlWrap(samplingParams.wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toGlWrap(samplingParams.wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toGlFilter(samplingParams.minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toGlFilter(samplingParams.magFilter));

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, tmpParams.data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(tmpParams.data);

    return true;
}

void Texture2D::Clear()
{
    glDeleteTextures(1, static_cast<GLuint*>(&m_Id));
    m_Id = 0;
}

void Texture2D::Bind(unsigned int unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(m_Id));
}

void Texture2D::SetData(const unsigned char* data)
{
    glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(m_Id));
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

ImageParams Texture2D::Load(const std::string& path)
{
    ImageParams params{};

    stbi_set_flip_vertically_on_load(true);

    int channelsNum;
    params.data = stbi_load(path.c_str(), &params.width, &params.height, &channelsNum, 0);

    switch (channelsNum)
    {
    case 1: params.format = Format::RED;  break;
    case 2: params.format = Format::RG;   break;
    case 3: params.format = Format::RGB;  break;
    case 4: params.format = Format::RGBA; break;
    default: break;
    }

    return params;
}

ImageParams Texture2D::GenerateCheckboard(int separationsNum)
{
    ImageParams params;
    params.width = params.height = 512;
    params.format = Format::RGB;

    int channelsNum = 3;
    params.data = static_cast<unsigned char*>(stbi__malloc(params.width * params.height * channelsNum));

    size_t xUnitSize = params.width / separationsNum;
    if (params.width % separationsNum > 0) xUnitSize++;

    size_t yUnitSize = params.height / separationsNum;
    if (params.height % separationsNum > 0) yUnitSize++;

    for (size_t y = 0; y < params.height; ++y)
    {
        for (size_t x = 0; x < params.width; ++x)
        {
            unsigned char cellColor = (((x / xUnitSize) + (y / yUnitSize)) % 2 == 0) ? 94 : 118;
            for (size_t i = 0; i < channelsNum; ++i)
            {
                params.data[y * params.width * channelsNum + x * channelsNum + i] = cellColor;
            }
        }
    }

    return params;
}

ImageParams Texture2D::GenerateFillColor(const Vec3& color)
{
    ImageParams params;
    params.width = params.height = 512;
    params.format = Format::RGB;

    int channelsNum = 3;
    params.data = static_cast<unsigned char*>(stbi__malloc(params.width * params.height * channelsNum));

    for (size_t y = 0; y < params.height; ++y)
    {
        for (size_t x = 0; x < params.width; ++x)
        {
            size_t id = y * params.width * channelsNum + x * channelsNum;
            params.data[id + 0] = static_cast<unsigned char>(color.x * 255.0f);
            params.data[id + 1] = static_cast<unsigned char>(color.y * 255.0f);
            params.data[id + 2] = static_cast<unsigned char>(color.z * 255.0f);
        }
    }

    return params;
}

} // namespace Delta
