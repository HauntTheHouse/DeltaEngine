#pragma once

#include <DeltaMath/Vec3.hpp>
#include <DeltaMath/Mat4.hpp>

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

    void Init(const Vec3f& position, const Vec3f& rotation, ProjectionMode projectionMode = ProjectionMode::PERSPECTIVE);

    void SetPosition(const Vec3f& position);
    void SetRotation(const Vec3f& rotation);
    void SetTransform(const Vec3f& position, const Vec3f& rotation);
    void SetProjectionMode(ProjectionMode projectionMode);

    void SetAspect(float aspect);
    void SetFov(float fovDegree);
    void SetNearFarPlanes(float nearPlane, float farPlane);
    void SetOrthoPlanes(float left, float right, float down, float up);

    float GetAspect() const { return m_Aspect; }
    float GetFov() const { return m_Fov; }
    Vec2f GetNearFarPlanes() const { return Vec2f(m_NearPlane, m_FarPlane); }
    Vec4f GetOrthoPlanes() const { return Vec4f(m_LeftPlane, m_RightPlane, m_DownPlane, m_UpPlane); }

    const Mat4& GetView();
    const Mat4& GetProjection();
    Mat4 GetViewProjection();

    void Move(const Vec3f& movementDelta, const Vec3f& rotationDelta);

private:
    void UpdateView();
    void UpdateProjection();

    ProjectionMode m_ProjectionMode;

    Vec3f m_Position;
    Vec3f m_Rotation;

    Vec3f m_Direction;
    Vec3f m_Right;
    Vec3f m_Up;

    static const Vec3f s_WorldForward;
    static const Vec3f s_WorldRight;
    static const Vec3f s_WorldUp;

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
