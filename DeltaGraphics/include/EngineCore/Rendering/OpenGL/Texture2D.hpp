#pragma once

#include <Vec3.hpp>

namespace Delta
{

class Texture2D
{
public:
    Texture2D() = default;
    ~Texture2D() = default;
    Texture2D(Texture2D&) = delete;
    Texture2D& operator=(Texture2D&) = delete;

    bool init(int aWidth, int aHeight, const unsigned char* aData = nullptr);
    void clear();
    void bind(unsigned int aUnit) const;

    void setData(const unsigned char* aData);

    static std::vector<unsigned char> generateCheckboard(int aWidth, int aHeight, int aChannelsNum, int aSeparationsNum);
    static std::vector<unsigned char> generateFillColor(int aWidth, int aHeight, int aChannelsNum, const Vec3& aColor);

private:
    unsigned int mId;
    int mWidth;
    int mHeight;

};

} // namespace Delta
