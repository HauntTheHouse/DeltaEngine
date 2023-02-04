#include "EngineCore/Camera.hpp"

namespace Delta
{

const Vec3 Camera::sWorldForward = Vec3{ 0.0f, 0.0f, -1.0f };
const Vec3 Camera::sWorldRight = Vec3{ 1.0f, 0.0f, 0.0f };
const Vec3 Camera::sWorldUp = Vec3{ 0.0f, 1.0f, 0.0f };

void Camera::init(const Vec3& aPosition, const Vec3& aRotation, ProjectionMode aProjectionMode)
{
    mPosition = aPosition;
    mRotation = aRotation;
    mProjectionMode = aProjectionMode;

    mUpdateView = true;
    mUpdateProjection = true;
}

void Camera::setPosition(const Vec3& aPosition)
{
    mPosition = aPosition;
    mUpdateView = true;
}

void Camera::setRotation(const Vec3& aRotation)
{
    mRotation = aRotation;
    mUpdateView = true;
}

void Camera::setTransform(const Vec3& aPosition, const Vec3& aRotation)
{
    mPosition = aPosition;
    mRotation = aRotation;
    mUpdateView = true;
}

void Camera::setProjectionMode(ProjectionMode aProjectionMode)
{
    mProjectionMode = aProjectionMode;
    mUpdateProjection = true;
}

void Camera::setAspect(float aAspect)
{
    mAspect = aAspect;
    mUpdateProjection = true;
}

void Camera::setFov(float aFovDegree)
{
    mFov = aFovDegree;
    mUpdateProjection = true;
}

void Camera::setNearFarPlanes(float aNear, float aFar)
{
    mNearPlane = aNear;
    mFarPlane = aFar;
    mUpdateProjection = true;
}

void Camera::setOrthoPlanes(float aLeft, float aRight, float aDown, float aUp)
{
    mLeftPlane = aLeft;
    mRightPlane = aRight;
    mDownPlane = aDown;
    mUpPlane = aUp;
    mUpdateProjection = true;
}

const Mat4& Camera::getView()
{
    if (mUpdateView) updateView();
    return mView;
}

const Mat4& Camera::getProjection()
{
    if (mUpdateProjection) updateProjection();
    return mProjection;
}

Mat4 Camera::getViewProjection()
{
    return getView() * getProjection();
}

void Camera::move(const Vec3& aMovementDelta, const Vec3& aRotationDelta)
{
    mPosition += mDirection * aMovementDelta.z;
    mPosition += mRight * aMovementDelta.x;
    mPosition += mUp * aMovementDelta.y;
    mRotation += aRotationDelta;

    mUpdateView = true;
}

void Camera::updateView()
{
    Mat3 eulerRotate;
    eulerRotate.identity();
    eulerRotate.rotate(mRotation);

    mDirection = eulerRotate * sWorldForward;
    mDirection.normalize();

    mRight = eulerRotate * sWorldRight;
    mRight.normalize();

    mUp = mRight.cross(mDirection);

    mView.lookAt(mPosition, mDirection + mPosition, mUp);

    mUpdateView = false;
}

void Camera::updateProjection()
{
    mProjectionMode == ProjectionMode::PERSPECTIVE
        ? mProjection.perspectiveOpenGL(mFov, mAspect, mNearPlane, mFarPlane)
        : mProjection.orthoOpenGL(mLeftPlane * mAspect, mRightPlane * mAspect, mDownPlane, mUpPlane, mNearPlane, mFarPlane);

    mUpdateProjection = false;
}

} // namespace Delta
