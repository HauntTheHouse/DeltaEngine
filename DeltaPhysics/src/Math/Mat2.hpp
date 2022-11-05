#pragma once

#include "Vec2.hpp"

namespace Delta
{

class Mat2
{
public:
    Mat2() = default;
    Mat2(Vec2 vec0, Vec2 vec1);
    Mat2(const float* mat);

    Mat2(const Mat2& rhs);
    Mat2& operator=(const Mat2& rhs);

    const Mat2& operator*=(const float rhs);
    const Mat2& operator+=(const Mat2& rhs);

    float determinant() const;

    const float* toPtr() const;

public:
    Vec2 rows[2];

}; // class Mat2

} // namespace Delta

#include "Mat2.inl"
