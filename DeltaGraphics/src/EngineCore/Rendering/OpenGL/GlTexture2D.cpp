#include "EngineCore/Rendering/OpenGL/Texture2D.hpp"

#include <glad/glad.h>

namespace Delta
{

bool Texture2D::init(int aWidth, int aHeight, const unsigned char* aData)
{
    if (mId != 0) return false;

    mWidth = aWidth;
    mHeight = aHeight;

    glGenTextures(1, static_cast<GLuint*>(&mId));
    glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(mId));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, aData != nullptr ? aData : generateCheckboard(mWidth, mHeight, 3, 8).data());
    glGenerateMipmap(GL_TEXTURE_2D);

    return true;
}

void Texture2D::clear()
{
    glDeleteTextures(1, static_cast<GLuint*>(&mId));
    mId = 0;
}

void Texture2D::bind(unsigned int aUnit) const
{
    glActiveTexture(GL_TEXTURE0 + aUnit);
    glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(mId));
}

void Texture2D::setData(const unsigned char* aData)
{
    glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(mId));
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, aData);
    glGenerateMipmap(GL_TEXTURE_2D);
}

std::vector<unsigned char> Texture2D::generateCheckboard(int aWidth, int aHeight, int aChannelsNum, int aSeparationsNum)
{
    std::vector<unsigned char> result;
    result.reserve(aWidth * aHeight * aChannelsNum);

    size_t xUnitSize = std::ceil(aWidth / static_cast<float>(aSeparationsNum));
    size_t yUnitSize = std::ceil(aHeight / static_cast<float>(aSeparationsNum));

    for (size_t y = 0; y < aHeight; ++y)
    {
        for (size_t x = 0; x < aWidth; ++x)
        {
            unsigned char cellColor = (((x / xUnitSize) + (y / yUnitSize)) % 2 == 0) ? 94 : 118;
            for (size_t i = 0; i < aChannelsNum; ++i)
            {
                result.push_back(cellColor);
            }
        }
    }

    return result;
}

std::vector<unsigned char> Texture2D::generateFillColor(int aWidth, int aHeight, int aChannelsNum, const Vec3& aColor)
{
    std::vector<unsigned char> result;
    result.reserve(aWidth * aHeight * aChannelsNum);

    for (size_t y = 0; y < aHeight; ++y)
    {
        for (size_t x = 0; x < aWidth; ++x)
        {
            result.push_back(static_cast<unsigned char>(aColor.x * 255.0f));
            result.push_back(static_cast<unsigned char>(aColor.y * 255.0f));
            result.push_back(static_cast<unsigned char>(aColor.z * 255.0f));
        }
    }

    return result;
}

} // namespace Delta
