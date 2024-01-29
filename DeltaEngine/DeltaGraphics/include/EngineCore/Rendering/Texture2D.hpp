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

    bool Init(int width, int height, const unsigned char* data = nullptr);
    void Clear();
    void Bind(unsigned int unit) const;

    void SetData(const unsigned char* data);

    static std::vector<unsigned char> GenerateCheckboard(int width, int height, int channelsNum, int separationsNum);
    static std::vector<unsigned char> GenerateFillColor(int width, int height, int channelsNum, const Vec3& color);

private:
    unsigned int m_Id{ 0 };
    int m_Width{};
    int m_Height{};

};

} // namespace Delta
