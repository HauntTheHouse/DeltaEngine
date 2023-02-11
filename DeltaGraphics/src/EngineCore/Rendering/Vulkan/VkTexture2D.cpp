#include "EngineCore/Rendering/OpenGL/Texture2D.hpp"

namespace Delta
{

bool Texture2D::init(int aWidth, int aHeight, const unsigned char* aData)
{
    return false;
}

void Texture2D::clear()
{
}

void Texture2D::bind(unsigned int aUnit) const
{
}

void Texture2D::setData(const unsigned char* aData)
{
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
