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

    Mat4 getViewProjectionMatrix() { return mViewProjectionMatrix; }

private:
    void updateMatrix();

    Vec3 mPosition;
    Vec3 mRotation;
    ProjectionMode mProjectionMode;

    Mat4 mViewProjectionMatrix;

};

} // namespace Delta
