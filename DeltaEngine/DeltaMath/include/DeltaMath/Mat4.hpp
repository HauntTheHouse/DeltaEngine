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
    Mat4(Vec4f vec0, Vec4f vec1, Vec4f vec2, Vec4f vec3);
    Mat4(const float* mat);

    Mat4(const Mat4& rhs);
    Mat4& operator=(const Mat4& rhs);

    const Mat4& operator*=(const float rhs);
    const Mat4& operator+=(const Mat4& rhs);
    Vec4f operator*(const Vec4f& rhs) const;
    Mat4 operator*(const float rhs) const;
    Mat4 operator*(const Mat4& rhs) const;
    Mat4 operator+(const Mat4& rhs) const;

    void identity();
    float trace() const;
    float determinant() const;
    Mat4 transpose() const;
    Mat4 inverse() const;
    Mat3 minor(const size_t i, const size_t j) const;
    float cofactor(const size_t i, const size_t j) const;

    void orient(const Vec3f& pos, const Vec3f& forward, const Vec3f& up);
    void lookAt(const Vec3f& pos, const Vec3f& lookAt, const Vec3f& up);
    void orthoOpenGL(float xmin, float xmax, float ymin, float ymax, float znear, float zfar);
    void orthoVulkan(float xmin, float xmax, float ymin, float ymax, float znear, float zfar);
    void perspectiveOpenGL(float fovy, float aspect, float nearPlane, float farPlane);
    void perspectiveVulkan(float fovy, float aspect, float nearPlane, float farPlane);

    void transform(const Vec3f& translate, const Vec3f& rotate, const Vec3f& scale = Vec3f(1.0f));
    void translate(const Vec3f& translate);
    void rotate(const Vec3f& angles);
    void scale(const Vec3f& scale);

    const float* toPtr() const;
    float* toPtr();

public:
    Vec4f rows[4];

}; // class Mat4

} // namespace Delta

#include "Mat4.inl"
