#include "Vec4.hpp"
#include <cassert>
#include <cmath>

namespace Delta
{

inline Vec4::Vec4() : x(0), y(0), z(0), w(0)
{}

inline Vec4::Vec4(const float value) : x(value), y(value), z(value), w(value)
{}

inline Vec4::Vec4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w)
{}

inline Vec4::Vec4(const Vec4& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
{}

inline Vec4::Vec4(const float *xyzw) : x(xyzw[0]), y(xyzw[1]), z(xyzw[2]), w(xyzw[3])
{}

inline Vec4& Vec4::operator=(const Vec4& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
}

inline bool Vec4::operator==(const Vec4& rhs) const
{
    return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w) ? true : false;
}

inline bool Vec4::operator!=(const Vec4& rhs) const
{
    return (*this == rhs) ? false : true;
}

inline Vec4 Vec4::operator+(const Vec4 & rhs) const
{
    return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

inline Vec4 Vec4::operator-(const Vec4& rhs) const
{
    return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

inline Vec4 Vec4::operator*(const float rhs) const
{
    return Vec4(x * rhs, y * rhs, z * rhs, w * rhs);
}

inline Vec4 Vec4::operator/(const float rhs) const
{
    return Vec4(x / rhs, y / rhs, z / rhs, w / rhs);
}

inline Vec4 Vec4::operator-() const
{
    return Vec4(-x, -y, -z, -w);
}

inline const Vec4& Vec4::operator+=(const Vec4& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

inline const Vec4& Vec4::operator-=(const Vec4& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

inline const Vec4& Vec4::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

inline const Vec4& Vec4::operator/=(const float rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
}

inline float Vec4::operator[](const size_t idx) const
{
    assert(idx >= 0 && idx <= 3);
    return (&x)[idx];
}

inline float& Vec4::operator[](const size_t idx)
{
    assert(idx >= 0 && idx <= 3);
    return (&x)[idx];
}

inline const Vec4& Vec4::normalize()
{
    float mag = getMagnitude();
    assert(mag != 0.0f);
    x /= mag;
    y /= mag;
    z /= mag;
    w /= mag;
    return *this;
}

inline float Vec4::getMagnitude() const
{
    return std::sqrt(x*x + y*y + z*z + w*w);
}

inline float Vec4::dot(const Vec4& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

inline const float* Vec4::toPtr() const
{
    return &x;
}

inline float* Vec4::toPtr()
{
	return &x;
}

} // namespace Delta
