#include "Logic\IGameObject.h"

namespace logic
{

	void IGameObject::SetEnabled(BOOL aEnabled)
	{
		mEnabled = aEnabled;
		//@TODO: Notify to world
	}

	//POSITION FUNCTIONS
	void IGameObject::SetPosition(const Vector3D<float32>& aPosition)
	{
		mPosition.mX = aPosition.mX;
		mPosition.mY = aPosition.mY;
		mPosition.mZ = aPosition.mZ;
	}
	void IGameObject::SetPosition(float32 aX, float32 aY, float32 aZ)
	{
		mPosition.mX = aX;
		mPosition.mY = aY;
		mPosition.mZ = aZ;
	}
	//const Vector3D<float32>&					GetPosition() const { return mPosition; }
	void IGameObject::GetPosition(Vector3D<float32>& aPosition) const {
		aPosition.mX = mPosition.mX;
		aPosition.mY = mPosition.mY;
		aPosition.mZ = mPosition.mZ;
	}
	void IGameObject::Translate(const Vector3D<float32>& aPosition)
	{
		mPosition += aPosition;
	}
	void IGameObject::Translate(float32 aX, float32 aY, float32 aZ)
	{
		mPosition.mX += aX;
		mPosition.mY += aY;
		mPosition.mZ += aZ;
	}
	//SCALE FUNCTIONS
	void IGameObject::SetScale(const Vector3D<float32>& aScale)
	{
		mScale.mX = aScale.mX;
		mScale.mY = aScale.mY;
		mScale.mZ = aScale.mZ;
	}
	void IGameObject::SetScale(float32 aX, float32 aY, float32 aZ)
	{
		mScale.mX = aX;
		mScale.mY = aY;
		mScale.mZ = aZ;
	}
	void IGameObject::SetScale(float32 aScale)
	{
		mScale.mX = aScale;
		mScale.mY = aScale;
		mScale.mZ = aScale;
	}
	//const Vector3D<float32>&					GetScale() const { return mScale; }
	void IGameObject::GetScale(Vector3D<float32>& aScale) const
	{
		aScale.mX = mScale.mX;
		aScale.mY = mScale.mY;
		aScale.mZ = mScale.mZ;
	}
	void IGameObject::Scale(const Vector3D<float32>& aScale)
	{
		mScale *= aScale;
	}
	void IGameObject::Scale(float32 aX, float32 aY, float32 aZ)
	{
		mScale.mX *= aX;
		mScale.mY *= aY;
		mScale.mZ *= aZ;
	}
	//ROTATION FUNCTIONS
	void IGameObject::SetRotation(const Vector3D<float32>& aRotation)
	{
		mRotation.mX = aRotation.mX;
		mRotation.mY = aRotation.mY;
		mRotation.mZ = aRotation.mZ;
	}
	void IGameObject::SetRotation(float32 aX, float32 aY, float32 aZ)
	{
		mRotation.mX = aX;
		mRotation.mY = aY;
		mRotation.mZ = aZ;
	}
	//const Vector3D<float32>&					GetRotation() const { return mRotation; }
	void IGameObject::GetRotation(Vector3D<float32>& aRotation) const
	{
		aRotation.mX = mRotation.mX;
		aRotation.mY = mRotation.mY;
		aRotation.mZ = mRotation.mZ;
	}
	void IGameObject::Rotate(const Vector3D<float32>& aRotation)
	{
		mRotation += aRotation;
	}
	void IGameObject::Rotate(float32 aX, float32 aY, float32 aZ)
	{
		mRotation.mX += aX;
		mRotation.mY += aY;
		mRotation.mZ += aZ;
	}
	void IGameObject::Rotate(float32 aAngle, const Vector3D<float32>& aAxis)
	{
		mRotation += aAxis*aAngle;
	}

} // namespace logic
