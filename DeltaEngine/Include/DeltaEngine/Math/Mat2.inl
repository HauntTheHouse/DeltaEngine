#include "Mat2.hpp"
#include <utility>

namespace Delta
{

inline Mat2::Mat2(Vec2f vec0, Vec2f vec1)
{
    rows[0] = std::move(vec0);
    rows[1] = std::move(vec1);
}

inline Mat2::Mat2(const float* mat)
{
    rows[0] = Vec2f(mat[0], mat[1]);
    rows[1] = Vec2f(mat[2], mat[3]);
}

inline Mat2::Mat2(const Mat2& rhs)
{
    rows[0] = rhs.rows[0];
    rows[1] = rhs.rows[1];
}

inline Mat2& Mat2::operator=(const Mat2& rhs)
{
    rows[0] = rhs.rows[0];
    rows[1] = rhs.rows[1];
    return *this;
}

inline const Mat2& Mat2::operator*=(const float rhs)
{
    rows[0] *= rhs;
    rows[1] *= rhs;
    return *this;
}

inline const Mat2& Mat2::operator+=(const Mat2& rhs)
{
    rows[0] += rhs.rows[0];
    rows[1] += rhs.rows[1];
    return *this;
}

inline float Mat2::determinant() const
{
    return rows[0].x * rows[1].y - rows[0].y * rows[1].x;
}

inline const float* Mat2::toPtr() const
{
    return rows[0].toPtr();
}

inline float* Mat2::toPtr()
{
    return rows[0].toPtr();
}

} // namespace Delta
