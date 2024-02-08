#pragma once

#include <type_traits>

namespace Delta
{

template<typename T>
class Vec2
{
public:
    Vec2();
    Vec2(const T value);
    Vec2(const T x, const T y);
    Vec2(const T *xy);

    Vec2(const Vec2& rhs);
    Vec2& operator=(const Vec2& rhs);

    bool operator==(const Vec2& rhs) const;
    bool operator!=(const Vec2& rhs) const;

    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator*(const T rhs) const;
    Vec2 operator/(const T rhs) const;
    Vec2 operator-() const;

    const Vec2& operator+=(const Vec2& rhs);
    const Vec2& operator-=(const Vec2& rhs);
    const Vec2& operator*=(const T rhs);
    const Vec2& operator/=(const T rhs);

    bool operator> (Vec2 rhs) const;
    bool operator< (Vec2 rhs) const;
    bool operator>=(Vec2 rhs) const;
    bool operator<=(Vec2 rhs) const;

    T operator[](const size_t idx) const;
    T& operator[](const size_t idx);

    template<typename U = T>
    inline typename std::enable_if<std::is_floating_point<U>::value, const Vec2&>::type normalize();

    template<typename U = T>
    typename std::enable_if<std::is_floating_point<U>::value, T>::type getMagnitude() const;

    template<typename U = T>
    typename std::enable_if<std::is_floating_point<U>::value, T>::type dot(const Vec2& rhs) const;

	const T* toPtr() const;
	T* toPtr();

public:
    T x;
    T y;

}; // class Vec2

using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned int>;

} // namespace Delta

#include "Vec2.inl"
