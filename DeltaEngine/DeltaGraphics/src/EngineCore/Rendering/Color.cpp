#include "EngineCore/Rendering/Color.hpp"

namespace Delta
{

Color::Color(const Vec3f& rgb)
    : r(rgb.x), g(rgb.y), b(rgb.z), a(1.0f) {}

Color::Color(float r, float g, float b)
    : r(r), g(g), b(b), a(1.0f) {}

Color::Color(int r, int g, int b)
    : Color(r/255.0f, g/255.0f, b/255.0f) {}


Color::Color(const Vec4f& rgba)
    : r(rgba.x), g(rgba.y), b(rgba.z), a(rgba.w) {}

Color::Color(float r, float g, float b, float a)
    : r(r), g(g), b(b), a(a) {}

Color::Color(int r, int g, int b, int a)
    : Color(r/255.0f, g/255.0f, b/255.0f, a/255.0f) {}


Color::Color(uint32_t rgbaHex)
{
    int alpha = (rgbaHex >> 24) & 0xFF;

    if (!alpha) alpha = 255;

    int red   = (rgbaHex >> 16) & 0xFF;
    int green = (rgbaHex >> 8)  & 0xFF;
    int blue  = (rgbaHex >> 0)  & 0xFF;

    r = red / 255.0f;
    g = green / 255.0f;
    b = blue / 255.0f;
    a = alpha / 255.0f;
}

} // namespace Delta
