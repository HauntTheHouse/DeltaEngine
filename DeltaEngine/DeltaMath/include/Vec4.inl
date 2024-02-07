#include "Vec4.hpp"
#include <cassert>
#include <cmath>

namespace Delta
{

template<typename T>
inline Vec4<T>::Vec4() : x(0), y(0), z(0), w(0)
{}

template<typename T>
inline Vec4<T>::Vec4(const T value) : x(value), y(value), z(value), w(value)
{}

template<typename T>
inline Vec4<T>::Vec4(const T x, const T y, const T z, const T w) : x(x), y(y), z(z), w(w)
{}

template<typename T>
inline Vec4<T>::Vec4(const Vec4& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
{}

template<typename T>
inline Vec4<T>::Vec4(const T *xyzw) : x(xyzw[0]), y(xyzw[1]), z(xyzw[2]), w(xyzw[3])
{}

template<typename T>
inline Vec4<T>& Vec4<T>::operator=(const Vec4& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
}

template<typename T>
inline bool Vec4<T>::operator==(const Vec4& rhs) const
{
    return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w) ? true : false;
}

template<typename T>
inline bool Vec4<T>::operator!=(const Vec4& rhs) const
{
    return (*this == rhs) ? false : true;
}

template<typename T>
inline Vec4<T> Vec4<T>::operator+(const Vec4 & rhs) const
{
    return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

template<typename T>
inline Vec4<T> Vec4<T>::operator-(const Vec4& rhs) const
{
    return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

template<typename T>
inline Vec4<T> Vec4<T>::operator*(const T rhs) const
{
    return Vec4(x * rhs, y * rhs, z * rhs, w * rhs);
}

template<typename T>
inline Vec4<T> Vec4<T>::operator/(const T rhs) const
{
    return Vec4(x / rhs, y / rhs, z / rhs, w / rhs);
}

template<typename T>
inline Vec4<T> Vec4<T>::operator-() const
{
    return Vec4(-x, -y, -z, -w);
}

template<typename T>
inline const Vec4<T>& Vec4<T>::operator+=(const Vec4& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

template<typename T>
inline const Vec4<T>& Vec4<T>::operator-=(const Vec4& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

template<typename T>
inline const Vec4<T>& Vec4<T>::operator*=(const T rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

template<typename T>
inline const Vec4<T>& Vec4<T>::operator/=(const T rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
}

template<typename T>
inline T Vec4<T>::operator[](const size_t idx) const
{
    assert(idx >= 0 && idx <= 3);
    return (&x)[idx];
}

template<typename T>
inline T& Vec4<T>::operator[](const size_t idx)
{
    assert(idx >= 0 && idx <= 3);
    return (&x)[idx];
}

template<typename T> template<typename U>
inline typename std::enable_if<std::is_floating_point<U>::value, const Vec4<T>&>::type Vec4<T>::normalize()
{
    T mag = getMagnitude();
    assert(mag != 0.0f);
    x /= mag;
    y /= mag;
    z /= mag;
    w /= mag;
    return *this;
}

template<typename T> template<typename U>
inline typename std::enable_if<std::is_floating_point<U>::value, T>::type Vec4<T>::getMagnitude() const
{
    return std::sqrt(x*x + y*y + z*z + w*w);
}

template<typename T> template<typename U>
inline typename std::enable_if<std::is_floating_point<U>::value, T>::type Vec4<T>::dot(const Vec4& rhs) const
{
    return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
}

template<typename T>
inline const T* Vec4<T>::toPtr() const
{
    return &x;
}

template<typename T>
inline T* Vec4<T>::toPtr()
{
    return &x;
}

} // namespace Delta
