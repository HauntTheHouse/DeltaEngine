#pragma once

#include <type_traits>

namespace Delta
{

template<typename T>
class Vec4
{
public:
    Vec4();
    Vec4(const T value);
    Vec4(const T x, const T y, const T z, const T w);
    Vec4(const T *xyzw);

    Vec4(const Vec4& rhs);
    Vec4& operator=(const Vec4& rhs);

    bool operator==(const Vec4& rhs) const;
    bool operator!=(const Vec4& rhs) const;

    Vec4 operator+(const Vec4& rhs) const;
    Vec4 operator-(const Vec4& rhs) const;
    Vec4 operator*(const T rhs) const;
    Vec4 operator/(const T rhs) const;
    Vec4 operator-() const;

    const Vec4& operator+=(const Vec4& rhs);
    const Vec4& operator-=(const Vec4& rhs);
    const Vec4& operator*=(const T rhs);
    const Vec4& operator/=(const T rhs);

    T operator[](const size_t idx) const;
    T& operator[](const size_t idx);

    template<typename U = T>
    inline typename std::enable_if<std::is_floating_point<U>::value, const Vec4&>::type normalize();

    template<typename U = T>
    inline typename std::enable_if<std::is_floating_point<U>::value, T>::type getMagnitude() const;

    template<typename U = T>
    inline typename std::enable_if<std::is_floating_point<U>::value, T>::type dot(const Vec4& rhs) const;

    const T* toPtr() const;
    T* toPtr();

public:
    T x;
    T y;
    T z;
    T w;

}; // class Vec4

using Vec4f = Vec4<float>;
using Vec4d = Vec4<double>;
using Vec4i = Vec4<int>;
using Vec4u = Vec4<unsigned int>;

} // namespace Delta

#include "Vec4.inl"
