#pragma once

#include <Vec3.hpp>
#include <Mat4.hpp>

namespace Delta
{

class Camera
{
public:
    enum class ProjectionMode
    {
        ORTHO,
        PERSPECTIVE
    };

    Camera() = default;

    void Init(const Vec3& position, const Vec3& rotation, ProjectionMode projectionMode = ProjectionMode::PERSPECTIVE);

    void SetPosition(const Vec3& position);
    void SetRotation(const Vec3& rotation);
    void SetTransform(const Vec3& position, const Vec3& rotation);
    void SetProjectionMode(ProjectionMode projectionMode);

    void SetAspect(float aspect);
    void SetFov(float fovDegree);
    void SetNearFarPlanes(float near, float far);
    void SetOrthoPlanes(float left, float right, float down, float up);

    float GetAspect() const { return m_Aspect; }
    float GetFov() const { return m_Fov; }
    Vec2 GetNearFarPlanes() const { return Vec2(m_NearPlane, m_FarPlane); }
    Vec4 GetOrthoPlanes() const { return Vec4(m_LeftPlane, m_RightPlane, m_DownPlane, m_UpPlane); }

    const Mat4& GetView();
    const Mat4& GetProjection();
    Mat4 GetViewProjection();

    void Move(const Vec3& movementDelta, const Vec3& rotationDelta);

private:
    void UpdateView();
    void UpdateProjection();

    ProjectionMode m_ProjectionMode;

    Vec3 m_Position;
    Vec3 m_Rotation;

    Vec3 m_Direction;
    Vec3 m_Right;
    Vec3 m_Up;

    static const Vec3 s_WorldForward;
    static const Vec3 s_WorldRight;
    static const Vec3 s_WorldUp;

    float m_Aspect{ 1.0f };
    float m_Fov{ 45.0f };
    float m_NearPlane{ 0.1f };
    float m_FarPlane{ 10.0f };
    float m_LeftPlane{ -5.0f };
    float m_RightPlane{ 5.0f };
    float m_DownPlane{ -5.0f };
    float m_UpPlane{ 5.0f };

    Mat4 m_View;
    Mat4 m_Projection;

    bool m_UpdateView;
    bool m_UpdateProjection;

};

} // namespace Delta
