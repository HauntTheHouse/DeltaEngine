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

    void setAspect(float aAspect);
    void setFov(float aFovDegree);
    void setNearFarPlanes(float aNear, float aFar);
    void setOrthoPlanes(float aLeft, float aRight, float aDown, float aUp);

    float getAspect() const { return mAspect; }
    float getFov() const { return mFov; }
    Vec2 getNearFarPlanes() const { return Vec2(mNearPlane, mFarPlane); }
    Vec4 getOrthoPlanes() const { return Vec4(mLeftPlane, mRightPlane, mDownPlane, mUpPlane); }

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

    float mAspect{ 1.0f };
    float mFov{ 45.0f };
    float mNearPlane{ 0.1f };
    float mFarPlane{ 10.0f };
    float mLeftPlane{ -5.0f };
    float mRightPlane{ 5.0f };
    float mDownPlane{ -5.0f };
    float mUpPlane{ 5.0f };

    Mat4 mView;
    Mat4 mProjection;

    bool mUpdateView;
    bool mUpdateProjection;

};

} // namespace Delta
