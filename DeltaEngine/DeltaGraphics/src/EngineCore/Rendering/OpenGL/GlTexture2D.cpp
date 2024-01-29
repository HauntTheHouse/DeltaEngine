#include "PCH.hpp"
#include "EngineCore/Rendering/Texture2D.hpp"

#include <glad/glad.h>

namespace Delta
{

bool Texture2D::Init(int width, int height, const unsigned char* data)
{
    if (m_Id != 0) return false;

    m_Width = width;
    m_Height = height;

    glGenTextures(1, static_cast<GLuint*>(&m_Id));
    glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(m_Id));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data != nullptr ? data : GenerateCheckboard(m_Width, m_Height, 3, 8).data());
    glGenerateMipmap(GL_TEXTURE_2D);

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

std::vector<unsigned char> Texture2D::GenerateCheckboard(int width, int height, int channelsNum, int separationsNum)
{
    std::vector<unsigned char> result;
    result.reserve(width * height * channelsNum);

    size_t xUnitSize = std::ceil(width / static_cast<float>(separationsNum));
    size_t yUnitSize = std::ceil(height / static_cast<float>(separationsNum));

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            unsigned char cellColor = (((x / xUnitSize) + (y / yUnitSize)) % 2 == 0) ? 94 : 118;
            for (size_t i = 0; i < channelsNum; ++i)
            {
                result.push_back(cellColor);
            }
        }
    }

    return result;
}

std::vector<unsigned char> Texture2D::GenerateFillColor(int width, int height, int channelsNum, const Vec3& color)
{
    std::vector<unsigned char> result;
    result.reserve(width * height * channelsNum);

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            result.push_back(static_cast<unsigned char>(color.x * 255.0f));
            result.push_back(static_cast<unsigned char>(color.y * 255.0f));
            result.push_back(static_cast<unsigned char>(color.z * 255.0f));
        }
    }

    return result;
}

} // namespace Delta
