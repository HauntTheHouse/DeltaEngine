#include "DeltaEngine/Camera.hpp"

namespace Delta
{

const Vec3f Camera::s_WorldForward = Vec3f{ 0.0f, 0.0f, -1.0f };
const Vec3f Camera::s_WorldRight = Vec3f{ 1.0f, 0.0f, 0.0f };
const Vec3f Camera::s_WorldUp = Vec3f{ 0.0f, 1.0f, 0.0f };

void Camera::Init(const Vec3f& position, const Vec3f& rotation, ProjectionMode projectionMode)
{
    m_Position = position;
    m_Rotation = rotation;
    m_ProjectionMode = projectionMode;

    m_UpdateView = true;
    m_UpdateProjection = true;
}

void Camera::SetPosition(const Vec3f& position)
{
    m_Position = position;
    m_UpdateView = true;
}

void Camera::SetRotation(const Vec3f& rotation)
{
    m_Rotation = rotation;
    m_UpdateView = true;
}

void Camera::SetTransform(const Vec3f& position, const Vec3f& rotation)
{
    m_Position = position;
    m_Rotation = rotation;
    m_UpdateView = true;
}

void Camera::SetProjectionMode(ProjectionMode projectionMode)
{
    m_ProjectionMode = projectionMode;
    m_UpdateProjection = true;
}

void Camera::SetAspect(float aspect)
{
    m_Aspect = aspect;
    m_UpdateProjection = true;
}

void Camera::SetFov(float fovDegree)
{
    m_Fov = fovDegree;
    m_UpdateProjection = true;
}

void Camera::SetNearFarPlanes(float nearPlane, float farPlane)
{
    m_NearPlane = nearPlane;
    m_FarPlane = farPlane;
    m_UpdateProjection = true;
}

void Camera::SetOrthoPlanes(float left, float right, float down, float up)
{
    m_LeftPlane = left;
    m_RightPlane = right;
    m_DownPlane = down;
    m_UpPlane = up;
    m_UpdateProjection = true;
}

const Mat4& Camera::GetView()
{
    if (m_UpdateView) UpdateView();
    return m_View;
}

const Mat4& Camera::GetProjection()
{
    if (m_UpdateProjection) UpdateProjection();
    return m_Projection;
}

Mat4 Camera::GetViewProjection()
{
    return GetView() * GetProjection();
}

void Camera::Move(const Vec3f& movementDelta, const Vec3f& rotationDelta)
{
    m_Position += m_Direction * movementDelta.z;
    m_Position += m_Right * movementDelta.x;
    m_Position += m_Up * movementDelta.y;
    m_Rotation += rotationDelta;

    m_UpdateView = true;
}

void Camera::UpdateView()
{
    Mat3 eulerRotate;
    eulerRotate.identity();
    eulerRotate.rotate(m_Rotation);

    m_Direction = eulerRotate * s_WorldForward;
    m_Direction.normalize();

    m_Right = eulerRotate * s_WorldRight;
    m_Right.normalize();

    m_Up = m_Right.cross(m_Direction);

    m_View.lookAt(m_Position, m_Direction + m_Position, m_Up);

    m_UpdateView = false;
}

void Camera::UpdateProjection()
{
    m_ProjectionMode == ProjectionMode::PERSPECTIVE
        ? m_Projection.perspectiveOpenGL(m_Fov, m_Aspect, m_NearPlane, m_FarPlane)
        : m_Projection.orthoOpenGL(m_LeftPlane * m_Aspect, m_RightPlane * m_Aspect, m_DownPlane, m_UpPlane, m_NearPlane, m_FarPlane);

    m_UpdateProjection = false;
}

} // namespace Delta
