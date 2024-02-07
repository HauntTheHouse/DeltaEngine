#include "Vec3.hpp"
#include <cassert>
#include <cmath>

namespace Delta
{

template<typename T>
inline Vec3<T>::Vec3() : x(0), y(0), z(0)
{}

template<typename T>
inline Vec3<T>::Vec3(const T value) : x(value), y(value), z(value)
{}

template<typename T>
inline Vec3<T>::Vec3(const T x, const T y, const T z) : x(x), y(y), z(z)
{}

template<typename T>
inline Vec3<T>::Vec3(const Vec3& rhs) : x(rhs.x), y(rhs.y), z(rhs.z)
{}

template<typename T>
inline Vec3<T>::Vec3(const T *xyz) : x(xyz[0]), y(xyz[1]), z(xyz[2])
{}

template<typename T>
inline Vec3<T>& Vec3<T>::operator=(const Vec3& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

template<typename T>
inline bool Vec3<T>::operator==(const Vec3& rhs) const
{
    return (x == rhs.x && y == rhs.y && z == rhs.z) ? true : false;
}

template<typename T>
inline bool Vec3<T>::operator!=(const Vec3& rhs) const
{
    return (*this == rhs) ? false : true;
}

template<typename T>
inline Vec3<T> Vec3<T>::operator+(const Vec3 & rhs) const
{
    return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

template<typename T>
inline Vec3<T> Vec3<T>::operator-(const Vec3& rhs) const
{
    return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

template<typename T>
inline Vec3<T> Vec3<T>::operator*(const T rhs) const
{
    return Vec3(x * rhs, y * rhs, z * rhs);
}

template<typename T>
inline Vec3<T> Vec3<T>::operator/(const T rhs) const
{
    return Vec3(x / rhs, y / rhs, z / rhs);
}

template<typename T>
inline Vec3<T> Vec3<T>::operator-() const
{
    return Vec3(-x, -y, -z);
}

template<typename T>
inline const Vec3<T>& Vec3<T>::operator+=(const Vec3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

template<typename T>
inline const Vec3<T>& Vec3<T>::operator-=(const Vec3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

template<typename T>
inline const Vec3<T>& Vec3<T>::operator*=(const T rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

template<typename T>
inline const Vec3<T>& Vec3<T>::operator/=(const T rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

template<typename T>
inline T Vec3<T>::operator[](const size_t idx) const
{
    assert(idx >= 0 && idx <= 2);
    return (&x)[idx];
}

template<typename T>
inline T& Vec3<T>::operator[](const size_t idx)
{
    assert(idx >= 0 && idx <= 2);
    return (&x)[idx];
}

template<typename T> template<typename U>
inline typename std::enable_if<std::is_floating_point<U>::value, const Vec3<T>&>::type Vec3<T>::normalize()
{
        T mag = getMagnitude();
        assert(mag != 0.0f);
        x /= mag;
        y /= mag;
        z /= mag;
        return *this;
}

template<typename T> template<typename U>
inline typename std::enable_if<std::is_floating_point<U>::value, T>::type Vec3<T>::getMagnitude() const
{
    return std::sqrt(x*x + y*y + z*z);
}

template<typename T> template<typename U>
inline typename std::enable_if<std::is_floating_point<U>::value, T>::type Vec3<T>::getLengthSqr() const
{
    return dot(*this);
}

template<typename T> template<typename U>
inline typename std::enable_if<std::is_floating_point<U>::value, void>::type Vec3<T>::getOrtho(Vec3& u, Vec3& v) const
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

template<typename T> template<typename U>
inline typename std::enable_if<std::is_floating_point<U>::value, T>::type Vec3<T>::dot(const Vec3& rhs) const
{
    return x*rhs.x + y*rhs.y + z*rhs.z;
}

template<typename T> template<typename U>
inline typename std::enable_if<std::is_floating_point<U>::value, Vec3<T>>::type Vec3<T>::cross(const Vec3& rhs) const
{
    Vec3 tmp(
        (y * rhs.z) - (rhs.y * z),
        (rhs.x * z) - (x * rhs.z),
        (x * rhs.y) - (rhs.x * y)
    );
    return tmp;
}

template<typename T>
inline const T* Vec3<T>::toPtr() const
{
    return &x;
}

template<typename T>
inline T* Vec3<T>::toPtr()
{
    return &x;
}

} // namespace Delta
