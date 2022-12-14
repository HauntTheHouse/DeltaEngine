#pragma once

#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat3.hpp"

namespace Delta
{

class Quat
{
public:
    Quat();
    Quat(float x, const float y, const float z, const float w);
    Quat(Vec3 n, const float angleRadians);

    Quat(const Quat& rhs);
    Quat& operator=(const Quat& rhs);

    Quat& operator*=(const float rhs);
    Quat& operator*=(const Quat& rhs);
    Quat operator*(const Quat& rhs) const;

    void normalize();
    void invert();
    Quat inverse() const;
    float getMagnitudeSquared() const;
    float getMagnitude() const;
    Vec3 rotatePoint(const Vec3& rhs) const;
    Mat3 rotateMatrix(const Mat3& rhs) const;
    Vec3 xyz() const;

    Vec4 toVec4() const;
    Mat3 toMat3() const;

public:
    float w;
    float x;
    float y;
    float z;

}; // class Quat

} // namespace Delta

#include "Quat.inl"
