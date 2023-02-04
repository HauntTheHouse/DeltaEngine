#include "Mat4.hpp"
#include "Constants.hpp"

namespace Delta
{

inline Mat4::Mat4(Vec4 vec0, Vec4 vec1, Vec4 vec2, Vec4 vec3)
{
    rows[0] = std::move(vec0);
    rows[1] = std::move(vec1);
    rows[2] = std::move(vec2);
    rows[3] = std::move(vec3);
}

inline Mat4::Mat4(const float* mat)
{
    for (size_t i = 0; i < 4; ++i)
    {
        size_t ii = i * 4;
        rows[i] = Vec4(mat[ii], mat[ii + 1], mat[ii + 2], mat[ii + 3]);
    }
}

inline Mat4::Mat4(const Mat4& rhs)
{
    for (size_t i = 0; i < 4; ++i)
        rows[i] = rhs.rows[i];
}

inline Mat4& Mat4::operator=(const Mat4& rhs)
{
    for (size_t i = 0; i < 4; ++i)
        rows[i] = rhs.rows[i];
    return *this;
}

inline const Mat4& Mat4::operator*=(const float rhs)
{
    for (size_t i = 0; i < 4; ++i)
        rows[i] *= rhs;
    return *this;
}

inline const Mat4& Mat4::operator+=(const Mat4& rhs)
{
    for (size_t i = 0; i < 4; ++i)
        rows[i] += rhs.rows[i];
    return *this;
}

inline Vec4 Mat4::operator*(const Vec4& rhs) const
{
    Vec4 tmp;
    for (size_t i = 0; i < 4; ++i)
        tmp[i] = rows[i].dot(rhs);
    return tmp;
}

inline Mat4 Mat4::operator*(const float rhs) const
{
    Mat4 tmp;
    for (size_t i = 0; i < 4; ++i)
        tmp.rows[i] = rows[i] * rhs;
    return tmp;
}

inline Mat4 Mat4::operator*(const Mat4& rhs) const
{
    Mat4 tmp;
    for (size_t i = 0; i < 4; ++i)
    {
        tmp.rows[i].x = rows[i].x * rhs.rows[0].x + rows[i].y * rhs.rows[1].x + rows[i].z * rhs.rows[2].x + rows[i].w * rhs.rows[3].x;
        tmp.rows[i].y = rows[i].x * rhs.rows[0].y + rows[i].y * rhs.rows[1].y + rows[i].z * rhs.rows[2].y + rows[i].w * rhs.rows[3].y;
        tmp.rows[i].z = rows[i].x * rhs.rows[0].z + rows[i].y * rhs.rows[1].z + rows[i].z * rhs.rows[2].z + rows[i].w * rhs.rows[3].z;
        tmp.rows[i].w = rows[i].x * rhs.rows[0].w + rows[i].y * rhs.rows[1].w + rows[i].z * rhs.rows[2].w + rows[i].w * rhs.rows[3].w;
    }
    return tmp;
}

inline Mat4 Mat4::operator+(const Mat4& rhs) const
{
    Mat4 tmp;
    for (size_t i = 0; i < 4; ++i)
        tmp.rows[i] = rows[i] + rhs.rows[i];
    return tmp;
}

inline void Mat4::identity()
{
    rows[0] = Vec4(1, 0, 0, 0);
    rows[1] = Vec4(0, 1, 0, 0);
    rows[2] = Vec4(0, 0, 1, 0);
    rows[3] = Vec4(0, 0, 0, 1);
}

inline float Mat4::trace() const
{
    const float xx = rows[0].x * rows[0].x;
    const float yy = rows[1].y * rows[1].y;
    const float zz = rows[2].z * rows[2].z;
    const float ww = rows[3].w * rows[3].w;
    return (xx + yy + zz + ww);
}

inline float Mat4::determinant() const
{
    float det = 0.0f;
    float sign = 1.0f;

    for (size_t j = 0; j < 4; ++j)
    {
        Mat3 minor = Mat4::minor(0, j);
        det += rows[0][j] * minor.determinant() * sign;
        sign = -sign;
    }

    return det;
}

inline Mat4 Mat4::transpose() const
{
    Mat4 transpose;
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            transpose.rows[i][j] = rows[j][i];
        }
    }
    return transpose;
}

inline Mat4 Mat4::inverse() const
{
    Mat4 inv;
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            // Perform the transpose with the cofactors
            inv.rows[j][i] = Mat4::cofactor(i, j);
        }
    }
    return inv * (1.0f / Mat4::determinant());
}

inline Mat3 Mat4::minor(const size_t i, const size_t j) const
{
    Mat3 minor;

    size_t yy = 0;
    for (size_t y = 0; y < 4; ++y)
    {
        if (y == j) continue;

        size_t xx = 0;
        for (size_t x = 0; x < 4; ++x)
        {
            if (x == i) continue;

            minor.rows[xx][yy] = rows[x][y];
            xx++;
        }
        yy++;
    }

    return minor;
}

inline float Mat4::cofactor(const size_t i, const size_t j) const
{
    const Mat3 minor = Mat4::minor(i, j);
    float sign = (i + j) % 2 == 0 ? 1.0f : -1.0f;

    return sign * minor.determinant();
}

inline void Mat4::orient(const Vec3& pos, const Vec3& forward, const Vec3& up)
{
    Vec3 left = up.cross(forward);

    // For our coordinate system where:
    // +x-axis = forward
    // +y-axis = left
    // +z-axis = up
    rows[0] = Vec4(forward.x, left.x, up.x, pos.x);
    rows[1] = Vec4(forward.y, left.y, up.y, pos.y);
    rows[2] = Vec4(forward.z, left.z, up.z, pos.z);
    rows[3] = Vec4(0.0f,      0.0f,   0.0f, 1.0f);
}

inline void Mat4::lookAt(const Vec3& pos, const Vec3& lookAt, const Vec3& up)
{
    Vec3 forward = pos - lookAt;
    forward.normalize();

    Vec3 right = up.cross(forward);
    right.normalize();

    Vec3 newUp = forward.cross(right);
    newUp.normalize();

    // For NDC coordinate system where:
    // +x-axis = right
    // +y-axis = up
    // +z-axis = forward
    rows[0] = Vec4( right.x,         up.x,         forward.x,        0.0f);
    rows[1] = Vec4( right.y,         up.y,         forward.y,        0.0f);
    rows[2] = Vec4( right.z,         up.z,         forward.z,        0.0f);
    rows[3] = Vec4(-pos.dot(right), -pos.dot(up), -pos.dot(forward), 1.0f);
}

inline void Mat4::orthoOpenGL(float xmin, float xmax, float ymin, float ymax, float znear, float zfar)
{
    const float width  = xmax - xmin;
    const float height = ymax - ymin;
    const float depth  = zfar - znear;

    const float tx = -(xmax + xmin)  / width;
    const float ty = -(ymax + ymin)  / height;
    const float tz = -(zfar + znear) / depth;

    rows[0] = Vec4(2.0f/width, 0.0f,         0.0f,       0.0f);
    rows[1] = Vec4(0.0f,       2.0f/height,  0.0f,       0.0f);
    rows[2] = Vec4(0.0f,       0.0f,        -2.0f/depth, 0.0f);
    rows[3] = Vec4(tx,         ty,           tz,         1.0f);
}

inline void Mat4::orthoVulkan(float xmin, float xmax, float ymin, float ymax, float znear, float zfar)
{
    // Vulkan changed its NDC. It switchs from a left handed coordinate system to a right handed one
    // +x points to the right
    // +y points into the screen
    // +z points dows (it used to point up in OpenGL)
    // It also changed the range from [-1, 1] to [0, 1] for the z
    // Clip space remains [-1, 1] for x and y
    // Check section 23 of the specification
    Mat4 matVulkan;
    matVulkan.rows[0] = Vec4(1.0f,  0.0f, 0.0f, 0.0f);
    matVulkan.rows[1] = Vec4(0.0f, -1.0f, 0.0f, 0.0f);
    matVulkan.rows[2] = Vec4(0.0f,  0.0f, 0.5f, 0.0f);
    matVulkan.rows[3] = Vec4(0.0f,  0.0f, 0.0f, 1.0f);

    Mat4 matOpengl;
    matOpengl.orthoOpenGL(xmin, xmax, ymin, ymax, znear, zfar);
    *this = matVulkan * matOpengl;
}

inline void Mat4::perspectiveOpenGL(float fovy, float aspect, float near, float far)
{
    const float fovyRadians = fovy * PI / 180.0f;
    const float f = 1.0f / std::tanf(fovyRadians * 0.5f);
    const float xScale = f;
    const float yScale = f * aspect;

    rows[0] = Vec4(xScale, 0.0f,    0.0f,                       0.0f);
    rows[1] = Vec4(0.0f,   yScale,  0.0f,                       0.0f);
    rows[2] = Vec4(0.0f,   0.0f,    (far+near)/(near-far),     -1.0f);
    rows[3] = Vec4(0.0f,   0.0f,    (2.0f*far*near)/(near-far), 0.0f);
}

inline void Mat4::perspectiveVulkan(float fovy, float aspect, float near, float far)
{
    // Vulkan changed its NDC. It switchs from a left handed coordinate system to a right handed one
    // +x points to the right
    // +y points into the screen
    // +z points dows (it used to point up in OpenGL)
    // It also changed the range from [-1, 1] to [0, 1] for the z
    // Clip space remains [-1, 1] for x and y
    // Check section 23 of the specification
    Mat4 matVulkan;
    matVulkan.rows[0] = Vec4(1.0f,  0.0f,  0.0f, 0.0f);
    matVulkan.rows[1] = Vec4(0.0f, -1.0f,  0.0f, 0.0f);
    matVulkan.rows[2] = Vec4(0.0f,  0.0f,  0.5f, 0.0f);
    matVulkan.rows[3] = Vec4(0.0f,  0.0f,  0.0f, 1.0f);

    Mat4 matOpengl;
    matOpengl.perspectiveOpenGL(fovy, aspect, near, far);
    *this = matVulkan * matOpengl;
}

inline void Mat4::transform(const Vec3& translate, const Vec3& rotate, const Vec3& scale)
{
    this->identity();
    this->translate(translate);
    this->rotate(rotate);
    this->scale(scale);
}

inline void Mat4::translate(const Vec3& translate)
{
    *this = Mat4(Vec4(1.0f,        0.0f,        0.0f,        0.0f),
                 Vec4(0.0f,        1.0f,        0.0f,        0.0f),
                 Vec4(0.0f,        0.0f,        1.0f,        0.0f),
                 Vec4(translate.x, translate.y, translate.z, 1.0f)) * *this;
}

inline void Mat4::rotate(const Vec3& angles)
{
    Vec3 radians = angles * (PI / 180.0);

    Mat4 rotX(Vec4(1.0f,  0.0f,             0.0f,            0.0f),
              Vec4(0.0f,  cosf(radians.x),  sinf(radians.x), 0.0f),
              Vec4(0.0f, -sinf(radians.x),  cosf(radians.x), 0.0f),
              Vec4(0.0f,  0.0f,             0.0f,            1.0f));

    Mat4 rotY(Vec4( cosf(radians.y), 0.0f, -sinf(radians.y), 0.0f),
              Vec4( 0.0f,            1.0f,  0.0f,            0.0f),
              Vec4( sinf(radians.y), 0.0f,  cosf(radians.y), 0.0f),
              Vec4( 0.0f,            0.0f,  0.0f,            1.0f));

    Mat4 rotZ(Vec4( cosf(radians.z),  sinf(radians.z), 0.0f, 0.0f),
              Vec4(-sinf(radians.z),  cosf(radians.z), 0.0f, 0.0f),
              Vec4( 0.0f,             0.0f,            1.0f, 0.0f),
              Vec4( 0.0f,             0.0f,            0.0f, 1.0f));

    *this = rotX * rotY * rotZ * *this;
}

inline void Mat4::scale(const Vec3& scale)
{
    *this = Mat4(Vec4(scale.x, 0.0f, 0.0f, 0.0f),
                 Vec4(0.0f, scale.y, 0.0f, 0.0f),
                 Vec4(0.0f, 0.0f, scale.z, 0.0f),
                 Vec4(0.0f, 0.0f, 0.0f,    1.0f)) * *this;
}

inline const float* Mat4::toPtr() const
{
    return rows[0].toPtr();
}

inline float* Mat4::toPtr()
{
    return rows[0].toPtr();
}

} // namespace Delta
