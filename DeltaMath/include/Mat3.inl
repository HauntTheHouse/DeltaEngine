#include "Mat3.hpp"

namespace Delta
{

inline Mat3::Mat3(Vec3 vec0, Vec3 vec1, Vec3 vec2)
{
    rows[0] = std::move(vec0);
    rows[1] = std::move(vec1);
    rows[2] = std::move(vec2);
}

inline Mat3::Mat3(const float* mat)
{
    rows[0] = Vec3(mat[0], mat[1], mat[2]);
    rows[1] = Vec3(mat[3], mat[4], mat[5]);
    rows[2] = Vec3(mat[6], mat[7], mat[8]);
}

inline Mat3::Mat3(const Mat3& rhs)
{
    rows[0] = rhs.rows[0];
    rows[1] = rhs.rows[1];
    rows[2] = rhs.rows[2];
}

inline Mat3& Mat3::operator=(const Mat3& rhs)
{
    rows[0] = rhs.rows[0];
    rows[1] = rhs.rows[1];
    rows[2] = rhs.rows[2];
    return *this;
}

inline const Mat3& Mat3::operator*=(const float rhs)
{
    rows[0] *= rhs;
    rows[1] *= rhs;
    rows[2] *= rhs;
    return *this;
}

inline const Mat3& Mat3::operator+=(const Mat3& rhs)
{
    rows[0] += rhs.rows[0];
    rows[1] += rhs.rows[1];
    rows[2] += rhs.rows[2];
    return *this;
}

inline Vec3 Mat3::operator*(const Vec3& rhs) const
{
    Vec3 tmp;
    tmp[0] = rows[0].dot(rhs);
    tmp[1] = rows[1].dot(rhs);
    tmp[2] = rows[2].dot(rhs);
    return tmp;
}

inline Mat3 Mat3::operator*(const float rhs) const
{
    Mat3 tmp;
    tmp.rows[0] = rows[0] * rhs;
    tmp.rows[1] = rows[1] * rhs;
    tmp.rows[2] = rows[2] * rhs;
    return tmp;
}

inline Mat3 Mat3::operator*(const Mat3& rhs) const
{
    Mat3 tmp;
    for (size_t i = 0; i < 3; ++i)
    {
        tmp.rows[i].x = rows[i].x * rhs.rows[0].x + rows[i].y * rhs.rows[1].x + rows[i].z * rhs.rows[2].x;
        tmp.rows[i].y = rows[i].x * rhs.rows[0].y + rows[i].y * rhs.rows[1].y + rows[i].z * rhs.rows[2].y;
        tmp.rows[i].z = rows[i].x * rhs.rows[0].z + rows[i].y * rhs.rows[1].z + rows[i].z * rhs.rows[2].z;
    }
    return tmp;
}

inline Mat3 Mat3::operator+(const Mat3& rhs) const
{
    Mat3 tmp;
    tmp.rows[0] = rows[0] + rhs.rows[0];
    tmp.rows[1] = rows[1] + rhs.rows[1];
    tmp.rows[2] = rows[2] + rhs.rows[2];
    return tmp;
}

inline void Mat3::identity()
{
    rows[0] = Vec3(1, 0, 0);
    rows[1] = Vec3(0, 1, 0);
    rows[2] = Vec3(0, 0, 1);
}

inline float Mat3::trace() const
{
    const float xx = rows[0].x * rows[0].x;
    const float yy = rows[1].y * rows[1].y;
    const float zz = rows[2].z * rows[2].z;
    return (xx + yy + zz);
}

inline float Mat3::determinant() const
{
    const float i = rows[0].x * (rows[1].y * rows[2].z - rows[1].z * rows[2].y);
    const float j = rows[0].y * (rows[1].x * rows[2].z - rows[1].z * rows[2].x);
    const float k = rows[0].z * (rows[1].x * rows[2].y - rows[1].y * rows[2].x);
    return (i - j + k);
}

inline Mat3 Mat3::transpose() const
{
    Mat3 transpose;
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            transpose.rows[i][j] = rows[j][i];
        }
    }
    return transpose;
}

inline Mat3 Mat3::inverse() const
{
    Mat3 inv;
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            // Perform the transpose with the cofactors
            inv.rows[j][i] = Mat3::cofactor(i, j);
        }
    }
    return inv * (1.0f / Mat3::determinant());
}

inline Mat2 Mat3::minor(const size_t i, const size_t j) const
{
    Mat2 minor;

    size_t yy = 0;
    for (size_t y = 0; y < 3; ++y)
    {
        if (y == j) continue;

        size_t xx = 0;
        for (size_t x = 0; x < 3; ++x)
        {
            if (x == i) continue;

            minor.rows[xx][yy] = rows[x][y];
            xx++;
        }
        yy++;
    }

    return minor;
}

inline float Mat3::cofactor(const size_t i, const size_t j) const
{
    const Mat2 minor = Mat3::minor(i, j);
    float sign = (i + j) % 2 == 0 ? 1.0f : -1.0f;

    return sign * minor.determinant();
}

inline void Mat3::rotate(const Vec3& angles)
{
    Vec3 radians = angles * (PI / 180.0);

    Mat3 rotX(Vec3(1.0f,  0.0f,             0.0f),
              Vec3(0.0f,  cosf(radians.x),  sinf(radians.x)),
              Vec3(0.0f, -sinf(radians.x),  cosf(radians.x)));

    Mat3 rotY(Vec3(cosf(radians.y), 0.0f, -sinf(radians.y)),
              Vec3(0.0f,            1.0f,  0.0f),
              Vec3(sinf(radians.y), 0.0f,  cosf(radians.y)));

    Mat3 rotZ(Vec3( cosf(radians.z),  sinf(radians.z), 0.0f),
              Vec3(-sinf(radians.z),  cosf(radians.z), 0.0f),
              Vec3( 0.0f,             0.0f,            1.0f));

    *this = rotZ * rotY * rotX * *this;
}

inline const float* Mat3::toPtr() const
{
    return rows[0].toPtr();
}

inline float* Mat3::toPtr()
{
    return rows[0].toPtr();
}

} // namespace Delta
