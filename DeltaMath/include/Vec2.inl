#include "Vec2.hpp"
#include <cassert>
#include <cmath>

namespace Delta
{

inline Vec2::Vec2() : x(0), y(0)
{}

inline Vec2::Vec2(const float value) : x(value), y(value)
{}

inline Vec2::Vec2(const float x, const float y) : x(x), y(y)
{}

inline Vec2::Vec2(const Vec2& rhs) : x(rhs.x), y(rhs.y)
{}

inline Vec2::Vec2(const float *xy) : x(xy[0]), y(xy[1])
{}

inline Vec2& Vec2::operator=(const Vec2& rhs)
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}

inline bool Vec2::operator==(const Vec2& rhs) const
{
    return (x == rhs.x && y == rhs.y) ? true : false;
}

inline bool Vec2::operator!=(const Vec2& rhs) const
{
    return (*this == rhs) ? false : true;
}

inline Vec2 Vec2::operator+(const Vec2 & rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

inline Vec2 Vec2::operator-(const Vec2& rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

inline Vec2 Vec2::operator*(const float rhs) const
{
    return Vec2(x * rhs, y * rhs);
}

inline Vec2 Vec2::operator/(const float rhs) const
{
    return Vec2(x / rhs, y / rhs);
}

inline Vec2 Vec2::operator-() const
{
    return Vec2(-x, -y);
}

inline const Vec2& Vec2::operator+=(const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

inline const Vec2& Vec2::operator-=(const Vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

inline const Vec2& Vec2::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
    return *this;
}

inline const Vec2& Vec2::operator/=(const float rhs)
{
    x /= rhs;
    y /= rhs;
    return *this;
}

inline float Vec2::operator[](const size_t idx) const
{
    assert(idx >= 0 && idx <= 1);
    return (&x)[idx];
}

inline float& Vec2::operator[](const size_t idx)
{
    assert(idx >= 0 && idx <= 1);
    return (&x)[idx];
}

inline const Vec2& Vec2::normalize()
{
    float mag = getMagnitude();
    assert(mag != 0.0f);
    x /= mag;
    y /= mag;
    return *this;
}

inline float Vec2::getMagnitude() const
{
    return std::sqrt(x*x + y*y);
}

inline float Vec2::dot(const Vec2& rhs) const
{
    return x * rhs.x + y * rhs.y;
}

inline const float* Vec2::toPtr() const
{
    return &x;
}

inline float* Vec2::toPtr()
{
	return &x;
}

} // namespace Delta
