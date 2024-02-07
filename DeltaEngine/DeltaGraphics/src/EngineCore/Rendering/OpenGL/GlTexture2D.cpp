#include "EngineCore/Rendering/Texture2D.hpp"

#include <stb_image.h>
#include <glad/glad.h>

namespace Delta
{

namespace
{
    size_t getChannelsNum(Format format)
    {
        switch (format)
        {
        case Delta::Format::RED: return 1;
        case Delta::Format::RG: return 2;
        case Delta::Format::RGB: return 3;
        case Delta::Format::RGBA: return 4;
        default: return 0;
        }
    }
}

ImageParams::~ImageParams()
{
    if (data)
    {
        stbi_image_free(data);
        data = nullptr;
    }
}

ImageParams::ImageParams(const ImageParams& params)
    : width(params.width), height(params.height), format(params.format), data(nullptr)
{
    if (params.data)
    {
        size_t size = width * height * getChannelsNum(format);
        data = static_cast<unsigned char*>(stbi__malloc(size));
        std::copy(data, data + size, params.data);
    }
}

ImageParams& ImageParams::operator=(const ImageParams& params)
{
    if (this != &params)
    {
        width = params.width;
        height = params.height;
        format = params.format;

        if (data) stbi_image_free(data);
        data = nullptr;

        if (params.data)
        {
            size_t size = width * height * getChannelsNum(format);
            data = static_cast<unsigned char*>(stbi__malloc(size));
            std::copy(data, data + size, params.data);
        }
    }
    return *this;
}

ImageParams::ImageParams(ImageParams&& params) noexcept
    : width(params.width), height(params.height), format(params.format), data(params.data)
{
    params.width = 0;
    params.height = 0;
    params.data = nullptr;
}

ImageParams& ImageParams::operator=(ImageParams&& params) noexcept
{
    if (this != &params)
    {
        width = params.width;
        height = params.height;
        format = params.format;

        if (data) stbi_image_free(data);
        data = params.data;

        params.width = 0;
        params.height = 0;
        params.data = nullptr;
    }
    return *this;
}

bool Texture2D::Init(const TextureParams& texParams)
{
    if (m_Id != 0) return false;

    if (!texParams.imageParams.data)
    {
        TextureParams newTexParams;
        newTexParams.imageParams = GenerateCheckboard(8);
        return Init(newTexParams);
    }

    m_Width = texParams.imageParams.width;
    m_Height = texParams.imageParams.height;

    GLint format = toNativeType(texParams.imageParams.format);

    glGenTextures(1, static_cast<GLuint*>(&m_Id));
    glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(m_Id));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toNativeType(texParams.samplingParams.wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toNativeType(texParams.samplingParams.wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toNativeType(texParams.samplingParams.minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toNativeType(texParams.samplingParams.magFilter));

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, texParams.imageParams.data);

    if (texParams.createMipmap) glGenerateMipmap(GL_TEXTURE_2D);

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
    return Texture2D::Load(path.c_str());
}

ImageParams Texture2D::Load(const char* path)
{
    ImageParams params{};

    stbi_set_flip_vertically_on_load(true);

    int channelsNum;
    params.data = stbi_load(path, &params.width, &params.height, &channelsNum, 0);

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

ImageParams Texture2D::GenerateFillColor(const Vec3f& color)
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
