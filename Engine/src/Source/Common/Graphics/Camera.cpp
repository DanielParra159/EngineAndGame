#include "Graphics\Camera.h"

namespace graphics
{
	void Camera::Init(eTypeCameras aType)
	{
		mType = aType;
	}

	void Camera::Release()
	{

	}

	void Camera::LookAt(const Vector3D<float32>* aCameraPosition, const Vector3D<float32>* aCameraLookAt, const Vector3D<float32>* aUp)
	{
		mViewMatrix = Matrix4x4::lookAt(aCameraPosition, aCameraLookAt, aUp);
	}

	void Camera::Perspective(float32 aFov, float32 aAspect, float32 aNear, float32 aFar)
	{
		mProjMatrix = Matrix4x4::Perspective(aFov, aAspect, aNear, aFar);
	}


} // namespace graphics

