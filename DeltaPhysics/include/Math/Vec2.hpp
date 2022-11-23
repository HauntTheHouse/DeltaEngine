#pragma once

namespace Delta
{

class Vec2
{
public:
    Vec2();
    Vec2(const float value);
    Vec2(const float x, const float y);
    Vec2(const float *xy);

    Vec2(const Vec2& rhs);
    Vec2& operator=(const Vec2& rhs);

    bool operator==(const Vec2& rhs) const;
    bool operator!=(const Vec2& rhs) const;

    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator*(const float rhs) const;
    Vec2 operator/(const float rhs) const;

    const Vec2& operator+=(const Vec2& rhs);
    const Vec2& operator-=(const Vec2& rhs);
    const Vec2& operator*=(const float rhs);
    const Vec2& operator/=(const float rhs);

    float operator[](const size_t idx) const;
    float& operator[](const size_t idx);

    const Vec2& normalize();
    float getMagnitude() const;
    float dot(const Vec2& rhs) const;

    const float* toPtr() const;

public:
    float x;
    float y;

}; // class Vec2

} // namespace Delta

#include "Vec2.inl"
