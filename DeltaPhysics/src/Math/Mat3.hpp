#pragma once

#include "Vec3.hpp"
#include "Mat2.hpp"

namespace Delta
{

class Mat3
{
public:
    Mat3() = default;
    Mat3(Vec3 vec0, Vec3 vec1, Vec3 vec2);
    Mat3(const float* mat);

    Mat3(const Mat3& rhs);
    Mat3& operator=(const Mat3& rhs);

    const Mat3& operator*=(const float rhs);
    const Mat3& operator+=(const Mat3& rhs);
    Vec3 operator*(const Vec3& rhs) const;
    Mat3 operator*(const float rhs) const;
    Mat3 operator*(const Mat3& rhs) const;
    Mat3 operator+(const Mat3& rhs) const;

    void identity();
    float trace() const;
    float determinant() const;
    Mat3 transpose() const;
    Mat3 inverse() const;
    Mat2 minor(const size_t i, const size_t j) const;
    float cofactor(const size_t i, const size_t j) const;

    const float* toPtr() const;

public:
    Vec3 rows[3];

}; // class Mat3

} // namespace Delta

#include "Mat3.inl"
