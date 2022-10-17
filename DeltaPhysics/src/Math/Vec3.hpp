#pragma once

namespace Delta
{

class Vec3
{
public:
    Vec3();
    Vec3(const float value);
    Vec3(const float x, const float y, const float z);
    Vec3(const float *xyz);

    Vec3(const Vec3& rhs);
    Vec3& operator=(const Vec3& rhs);

    bool operator==(const Vec3& rhs) const;
    bool operator!=(const Vec3& rhs) const;

    Vec3 operator+(const Vec3& rhs) const;
    Vec3 operator-(const Vec3& rhs) const;
    Vec3 operator*(const float rhs) const;
    Vec3 operator/(const float rhs) const;

    const Vec3& operator+=(const Vec3& rhs);
    const Vec3& operator-=(const Vec3& rhs);
    const Vec3& operator*=(const float rhs);
    const Vec3& operator/=(const float rhs);

    float operator[](const int idx) const;
    float& operator[](const int idx);

    const Vec3& normalize();
    float getMagnitude() const;
    float getLengthSqr() const;
    void getOrtho(Vec3& u, Vec3& v) const;

    float dot(const Vec3& rhs) const;
    Vec3 cross(const Vec3& rhs) const;

    const float* toPtr() const;

public:
    float x;
    float y;
    float z;

}; // class Vec3

} // namespace Delta

#include "Vec3.inl"
