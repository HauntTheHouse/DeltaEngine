#pragma once

#include <DeltaEngine/Math/Vec3.hpp>
#include <DeltaEngine/Math/Vec4.hpp>
#include <cstdint>

namespace Delta
{

class Color
{
public:
    Color(const Vec3f& rgb);
    Color(float r, float g, float b);
    Color(int r, int g, int b);

    Color(const Vec4f& rgba);
    Color(float r, float g, float b, float a);
    Color(int r, int g, int b, int a);

    Color(uint32_t rgbaHex);

public:
    float r;
    float g;
    float b;
    float a;

};

} // namespace Delta
