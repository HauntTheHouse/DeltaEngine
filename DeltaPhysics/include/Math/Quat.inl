#include "Quat.hpp"

namespace Delta
{

inline Quat::Quat() : x(0), y(0), z(0), w(1)
{}

inline Quat::Quat(float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w)
{}

inline Quat::Quat(Vec3 n, const float angleRadians)
{
    const float halfAngle = angleRadians * 0.5f;
    const float halfSin = std::sinf(halfAngle);
    n.normalize();

    x = n.x * halfSin;
    y = n.y * halfSin;
    z = n.z * halfSin;
    w = std::cosf(halfAngle);
}

inline Quat::Quat(const Quat& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
{}

inline Quat& Quat::operator=(const Quat& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
}

inline Quat& Quat::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

inline Quat& Quat::operator*=(const Quat& rhs)
{
    Quat tmp = *this * rhs;
    x = tmp.x;
    y = tmp.y;
    z = tmp.z;
    w = tmp.w;
    return *this;
}

inline Quat Quat::operator*(const Quat& rhs) const
{
    Quat tmp;
    tmp.x = (x * rhs.w) + (w * rhs.x) + (y * rhs.z) - (z * rhs.y);
    tmp.y = (y * rhs.w) + (w * rhs.y) + (z * rhs.x) - (x * rhs.z);
    tmp.z = (z * rhs.w) + (w * rhs.z) + (x * rhs.y) - (y * rhs.x);
    tmp.w = (w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z);
    return tmp;
}

inline void Quat::normalize()
{
    const float mag = getMagnitude();
    assert(mag != 0.0f);

    const float invMag = 1.0f / mag;
    x *= invMag;
    y *= invMag;
    z *= invMag;
    w *= invMag;
}

inline void Quat::invert()
{
    const float magSqr = getMagnitudeSquared();
    assert(magSqr != 0.0f);

    *this *= 1.0f / magSqr;
    x = -x;
    y = -y;
    z = -z;
}

inline Quat Quat::inverse() const
{
    Quat tmp(*this);
    tmp.invert();
    return tmp;
}

inline float Quat::getMagnitudeSquared() const
{
    return x * x + y * y + z * z + w * w;
}

inline float Quat::getMagnitude() const
{
    return std::sqrtf(Quat::getMagnitudeSquared());
}

inline Vec3 Quat::rotatePoint(const Vec3& rhs) const
{
    Quat vector(rhs.x, rhs.y, rhs.z, 0);
    Quat final = *this * vector * Quat::inverse();
    return Vec3(final.x, final.y, final.z);
}

inline Mat3 Quat::rotateMatrix(const Mat3& rhs) const
{
    Mat3 mat;
    mat.rows[0] = Quat::rotatePoint(rhs.rows[0]);
    mat.rows[1] = Quat::rotatePoint(rhs.rows[1]);
    mat.rows[2] = Quat::rotatePoint(rhs.rows[2]);
    return mat;
}

inline Vec3 Quat::xyz() const
{
    return Vec3(x, y, z);
}

inline Vec4 Quat::toVec4() const
{
    return Vec4(w, x, y, z);
}

inline Mat3 Quat::toMat3() const
{
    Mat3 mat;
    mat.identity();

    mat.rows[0] = Quat::rotatePoint(mat.rows[0]);
    mat.rows[1] = Quat::rotatePoint(mat.rows[1]);
    mat.rows[2] = Quat::rotatePoint(mat.rows[2]);
    return mat;

}

} // namespace Delta
