#pragma once

#include "Vec4.hpp"
#include "Vec3.hpp"
#include "Mat3.hpp"

namespace Delta
{

class Mat4
{
public:
    Mat4() = default;
    Mat4(Vec4 vec0, Vec4 vec1, Vec4 vec2, Vec4 vec3);
    Mat4(const float* mat);

    Mat4(const Mat4& rhs);
    Mat4& operator=(const Mat4& rhs);

    const Mat4& operator*=(const float rhs);
    const Mat4& operator+=(const Mat4& rhs);
    Vec4 operator*(const Vec4& rhs) const;
    Mat4 operator*(const float rhs) const;
    Mat4 operator*(const Mat4& rhs) const;
    Mat4 operator+(const Mat4& rhs) const;

    void identity();
    float trace() const;
    float determinant() const;
    Mat4 transpose() const;
    Mat4 inverse() const;
    Mat3 minor(const int i, const int j) const;
    float cofactor(const int i, const int j) const;

    void orient(const Vec3& pos, const Vec3& forward, const Vec3& up);
    void lookAt(const Vec3& pos, const Vec3& lookAt, const Vec3& up);
    void orthoOpenGL(float xmin, float xmax, float ymin, float ymax, float znear, float zfar);
    void orthoVulkan(float xmin, float xmax, float ymin, float ymax, float znear, float zfar);
    void perspectiveOpenGL(float fovy, float aspect, float near, float far);
    void perspectiveVulkan(float fovy, float aspect, float near, float far);

    const float* toPtr() const;

public:
    Vec4 rows[4];

}; // class Mat4

} // namespace Delta

#include "Mat4.inl"
