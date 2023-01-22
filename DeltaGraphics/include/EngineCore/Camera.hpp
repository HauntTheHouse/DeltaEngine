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

    void init(const Vec3& aPosition, const Vec3& aRotation, ProjectionMode aProjectionMode = ProjectionMode::PERSPECTIVE);

    void setPosition(const Vec3& aPosition);
    void setRotation(const Vec3& aRotation);
    void setTransform(const Vec3& aPosition, const Vec3& aRotation);
    void setProjectionMode(ProjectionMode aProjectionMode);

    const Mat4& getView();
    const Mat4& getProjection();
    Mat4 getViewProjection();

    void move(const Vec3& aMovementDelta, const Vec3& aRotationDelta);

private:
    void updateView();
    void updateProjection();

    ProjectionMode mProjectionMode;

    Vec3 mPosition;
    Vec3 mRotation;

    Vec3 mDirection;
    Vec3 mRight;
    Vec3 mUp;

    static const Vec3 sWorldForward;
    static const Vec3 sWorldRight;
    static const Vec3 sWorldUp;

    Mat4 mView;
    Mat4 mProjection;

    bool mUpdateView;
    bool mUpdateProjection;

};

} // namespace Delta
