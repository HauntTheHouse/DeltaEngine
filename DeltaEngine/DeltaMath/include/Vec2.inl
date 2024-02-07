#include "Vec2.hpp"
#include <cassert>
#include <cmath>

namespace Delta
{

template<typename T>
inline Vec2<T>::Vec2() : x(0), y(0)
{}

template<typename T>
inline Vec2<T>::Vec2(const T value) : x(value), y(value)
{}

template<typename T>
inline Vec2<T>::Vec2(const T x, const T y) : x(x), y(y)
{}

template<typename T>
inline Vec2<T>::Vec2(const Vec2& rhs) : x(rhs.x), y(rhs.y)
{}

template<typename T>
inline Vec2<T>::Vec2(const T *xy) : x(xy[0]), y(xy[1])
{}

template<typename T>
inline Vec2<T>& Vec2<T>::operator=(const Vec2& rhs)
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}

template<typename T>
inline bool Vec2<T>::operator==(const Vec2& rhs) const
{
    return (x == rhs.x && y == rhs.y) ? true : false;
}

template<typename T>
inline bool Vec2<T>::operator!=(const Vec2& rhs) const
{
    return (*this == rhs) ? false : true;
}

template<typename T>
inline Vec2<T> Vec2<T>::operator+(const Vec2 & rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator-(const Vec2& rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator*(const T rhs) const
{
    return Vec2(x * rhs, y * rhs);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator/(const T rhs) const
{
    return Vec2(x / rhs, y / rhs);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator-() const
{
    return Vec2(-x, -y);
}

template<typename T>
inline const Vec2<T>& Vec2<T>::operator+=(const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

template<typename T>
inline const Vec2<T>& Vec2<T>::operator-=(const Vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

template<typename T>
inline const Vec2<T>& Vec2<T>::operator*=(const T rhs)
{
    x *= rhs;
    y *= rhs;
    return *this;
}

template<typename T>
inline const Vec2<T>& Vec2<T>::operator/=(const T rhs)
{
    x /= rhs;
    y /= rhs;
    return *this;
}

template<typename T>
inline T Vec2<T>::operator[](const size_t idx) const
{
    assert(idx >= 0 && idx <= 1);
    return (&x)[idx];
}

template<typename T>
inline T& Vec2<T>::operator[](const size_t idx)
{
    assert(idx >= 0 && idx <= 1);
    return (&x)[idx];
}

template<typename T> template<typename U>
inline typename std::enable_if<std::is_floating_point<U>::value, const Vec2<T>&>::type Vec2<T>::normalize()
{
    T mag = getMagnitude();
    assert(mag != 0.0f);
    x /= mag;
    y /= mag;
    return *this;
}

template<typename T> template<typename U>
inline typename std::enable_if<std::is_floating_point<U>::value, T>::type Vec2<T>::getMagnitude() const
{
    return std::sqrt(x*x + y*y);
}

template<typename T> template<typename U>
inline typename std::enable_if<std::is_floating_point<U>::value, T>::type Vec2<T>::dot(const Vec2& rhs) const
{
    return x*rhs.x + y*rhs.y;
}

template<typename T>
inline const T* Vec2<T>::toPtr() const
{
    return &x;
}

template<typename T>
inline T* Vec2<T>::toPtr()
{
    return &x;
}

} // namespace Delta
