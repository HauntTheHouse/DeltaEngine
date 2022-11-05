#pragma once

namespace Delta
{

class Vec4
{
public:
    Vec4();
    Vec4(const float value);
    Vec4(const float x, const float y, const float z, const float w);
    Vec4(const float *xyzw);

    Vec4(const Vec4& rhs);
    Vec4& operator=(const Vec4& rhs);

    bool operator==(const Vec4& rhs) const;
    bool operator!=(const Vec4& rhs) const;

    Vec4 operator+(const Vec4& rhs) const;
    Vec4 operator-(const Vec4& rhs) const;
    Vec4 operator*(const float rhs) const;
    Vec4 operator/(const float rhs) const;

    const Vec4& operator+=(const Vec4& rhs);
    const Vec4& operator-=(const Vec4& rhs);
    const Vec4& operator*=(const float rhs);
    const Vec4& operator/=(const float rhs);

    float operator[](const size_t idx) const;
    float& operator[](const size_t idx);

    const Vec4& normalize();
    float getMagnitude() const;
    float dot(const Vec4& rhs) const;

    const float* toPtr() const;

public:
    float x;
    float y;
    float z;
    float w;

}; // class Vec4

} // namespace Delta

#include "Vec4.inl"
