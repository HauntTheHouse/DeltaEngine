#include "Vec3.hpp"
#include <cassert>
#include <cmath>

namespace Delta
{

inline Vec3::Vec3() : x(0), y(0), z(0)
{}

inline Vec3::Vec3(const float value) : x(value), y(value), z(value)
{}

inline Vec3::Vec3(const float x, const float y, const float z) : x(x), y(y), z(z)
{}

inline Vec3::Vec3(const Vec3& rhs) : x(rhs.x), y(rhs.y), z(rhs.z)
{}

inline Vec3::Vec3(const float *xyz) : x(xyz[0]), y(xyz[1]), z(xyz[2])
{}

inline Vec3& Vec3::operator=(const Vec3& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

inline bool Vec3::operator==(const Vec3& rhs) const
{
    return (x == rhs.x && y == rhs.y && z == rhs.z) ? true : false;
}

inline bool Vec3::operator!=(const Vec3& rhs) const
{
    return (*this == rhs) ? false : true;
}

inline Vec3 Vec3::operator+(const Vec3 & rhs) const
{
    return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

inline Vec3 Vec3::operator-(const Vec3& rhs) const
{
    return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

inline Vec3 Vec3::operator*(const float rhs) const
{
    return Vec3(x * rhs, y * rhs, z * rhs);
}

inline Vec3 Vec3::operator/(const float rhs) const
{
    return Vec3(x / rhs, y / rhs, z / rhs);
}

inline const Vec3& Vec3::operator+=(const Vec3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

inline const Vec3& Vec3::operator-=(const Vec3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

inline const Vec3& Vec3::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

inline const Vec3& Vec3::operator/=(const float rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

inline float Vec3::operator[](const int idx) const
{
    assert(idx >= 0 && idx <= 2);
    return (&x)[idx];
}

inline float& Vec3::operator[](const int idx)
{
    assert(idx >= 0 && idx <= 2);
    return (&x)[idx];
}

inline const Vec3& Vec3::normalize()
{
    float mag = getMagnitude();
    assert(mag != 0.0f);
    x /= mag;
    y /= mag;
    z /= mag;
    return *this;
}

inline float Vec3::getMagnitude() const
{
    return std::sqrt(x*x + y*y + z*z);
}

inline float Vec3::getLengthSqr() const
{
    return dot(*this);
}

inline void Vec3::getOrtho(Vec3& u, Vec3& v) const
{
    Vec3 n = *this;
    n.normalize();

    const Vec3 w = (n.z * n.z > 0.9f * 0.9f) ? Vec3(1.0f, 0.0f, 0.0f) : Vec3(0.0f, 0.0f, 1.0f);
    u = w.cross(n);
    u.normalize();

    v = n.cross(u);
    v.normalize();
    u = v.cross(n);
    u.normalize();
}

inline float Vec3::dot(const Vec3& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

inline Vec3 Vec3::cross(const Vec3& rhs) const
{
    Vec3 tmp (
        (y * rhs.z) - (rhs.y * z),
        (rhs.x * z) - (x * rhs.z),
        (x * rhs.y) - (rhs.x * y)
    );
    return tmp;
}

inline const float* Vec3::toPtr() const
{
    return &x;
}

} // namespace Delta
