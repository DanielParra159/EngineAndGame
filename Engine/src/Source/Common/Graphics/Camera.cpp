#include "Graphics\Camera.h"

namespace graphics
{
	void Camera::Init(const Vector3D<float32>* aEye, const Vector3D<float32>* aCenter, const Vector3D<float32>* aUp)
	{

	}

	void Camera::Release()
	{

	}

	void Camera::LookAt(const Vector3D<float32>* aEye, const Vector3D<float32>* aPosition, const Vector3D<float32>* aUp)
	{

	}

	void Camera::LookAt(const Vector3D<float32>* aEye, const Vector3D<float32>* aUp)
	{
		
	}
	void Camera::SetPosition(const Vector3D<float32>& aPosition)
	{
		mPosition.mX = aPosition.mX;
		mPosition.mY = aPosition.mY;
		mPosition.mZ = aPosition.mZ;
	}
	void Camera::SetPosition(float32 aX, float32 aY, float32 aZ)
	{
		mPosition.mX = aX;
		mPosition.mY = aY;
		mPosition.mZ = aZ;
	}

} // namespace graphics

