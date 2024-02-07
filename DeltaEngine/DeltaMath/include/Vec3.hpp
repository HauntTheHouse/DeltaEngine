#pragma once

#include <type_traits>

namespace Delta
{

template<typename T>
class Vec3
{
public:
    Vec3();
    Vec3(const T value);
    Vec3(const T x, const T y, const T z);
    Vec3(const T *xyz);

    Vec3(const Vec3& rhs);
    Vec3& operator=(const Vec3& rhs);

    bool operator==(const Vec3& rhs) const;
    bool operator!=(const Vec3& rhs) const;

    Vec3 operator+(const Vec3& rhs) const;
    Vec3 operator-(const Vec3& rhs) const;
    Vec3 operator*(const T rhs) const;
    Vec3 operator/(const T rhs) const;
    Vec3 operator-() const;

    const Vec3& operator+=(const Vec3& rhs);
    const Vec3& operator-=(const Vec3& rhs);
    const Vec3& operator*=(const T rhs);
    const Vec3& operator/=(const T rhs);

    T operator[](const size_t idx) const;
    T& operator[](const size_t idx);

    template<typename U = T>
    inline typename std::enable_if<std::is_floating_point<U>::value, const Vec3&>::type normalize();

    template<typename U = T>
    inline typename std::enable_if<std::is_floating_point<U>::value, T>::type getMagnitude() const;

    template<typename U = T>
    inline typename std::enable_if<std::is_floating_point<U>::value, T>::type getLengthSqr() const;

    template<typename U = T>
    inline typename std::enable_if<std::is_floating_point<U>::value, void>::type getOrtho(Vec3& u, Vec3& v) const;

    template<typename U = T>
    inline typename std::enable_if<std::is_floating_point<U>::value, T>::type dot(const Vec3& rhs) const;

    template<typename U = T>
    inline typename std::enable_if<std::is_floating_point<U>::value, Vec3>::type cross(const Vec3& rhs) const;

    const T* toPtr() const;
    T* toPtr();

public:
    T x;
    T y;
    T z;

}; // class Vec3

using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;
using Vec3i = Vec3<int>;
using Vec3u = Vec3<unsigned int>;

} // namespace Delta

#include "Vec3.inl"
