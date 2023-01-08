#include "EngineCore/Camera.hpp"

void Delta::Camera::init(const Vec3& aPosition, const Vec3& aRotation, ProjectionMode aProjectionMode)
{
	mPosition = aPosition;
	mRotation = aRotation;
	mProjectionMode = aProjectionMode;

	updateMatrix();
}

void Delta::Camera::setPosition(const Vec3& aPosition)
{
	mPosition = aPosition;
	updateMatrix();
}

void Delta::Camera::setRotation(const Vec3& aRotation)
{
	mRotation = aRotation;
	updateMatrix();
}

void Delta::Camera::setTransform(const Vec3& aPosition, const Vec3& aRotation)
{
	mPosition = aPosition;
	mRotation = aRotation;
	updateMatrix();
}

void Delta::Camera::setProjectionMode(ProjectionMode aProjectionMode)
{
	mProjectionMode = aProjectionMode;
	updateMatrix();
}

void Delta::Camera::updateMatrix()
{
	Mat4 view;
	view.identity();
	view.rotate(-mRotation);
	view.translate(-mPosition);

	Mat4 projection;
	mProjectionMode == ProjectionMode::PERSPECTIVE
		? projection.perspectiveOpenGL(45.0f, 1.0f, 0.1f, 10.0f)
		: projection.orthoOpenGL(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 10.0f);

	mViewProjectionMatrix = view * projection;
}
