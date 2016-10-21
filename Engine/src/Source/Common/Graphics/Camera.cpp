#include "Graphics\Camera.h"

#include "Logic/IGameObject.h"

namespace graphics
{
	REGISTER_COMPONENT_BODY(Camera, graphics)

	void Camera::Init(BOOL aActive, eTypeCameras aType)
	{
		logic::IComponent::Init(aActive);
		mType = aType;
		mTarget = NULL;
	}

	void Camera::Release()
	{

	}

	void Camera::SetCallbacks(logic::IGameObject* aGameObject, UpdateFunction& aUpdateFunction, FixedUpdateFunction& aFixedUpdateFunction, RenderFunction& aRenderFunction)
	{
		IComponent::SetCallbacks(aGameObject, aUpdateFunction, aFixedUpdateFunction, aRenderFunction);
		aUpdateFunction = IComponent::UpdateCallbackFunction;
		aFixedUpdateFunction = NULL;
		aRenderFunction = NULL;
	}

	void Camera::Update() 
	{
		if (mTarget != NULL)
		{
			Vector3D<float32> lTargetPosition = *mTarget->GetPosition();
			LookAt((lTargetPosition + mPositionOffset), (lTargetPosition + mLookAtOffset), mUp);
		}
	}

	void Camera::LookAt(const Vector3D<float32>& aCameraPosition, const Vector3D<float32>& aCameraLookAt, const Vector3D<float32>& aUp)
	{
		mCameraPosition = aCameraPosition;
		mCameraLookAt = aCameraLookAt;
		mUp = aUp;

		mViewMatrix = Matrix4x4::lookAt(&aCameraPosition, &aCameraLookAt, &aUp);
	}

	void Camera::Perspective(float32 aFov, float32 aAspect, float32 aNear, float32 aFar)
	{
		mProjMatrix = Matrix4x4::Perspective(aFov, aAspect, aNear, aFar);
	}

	void Camera::Orthographic(float32 aLeft, float32 aRight, float32 aBottom, float32 aUp, float32 aZNear, float32 aZFar)
	{
		mProjMatrix = Matrix4x4::Orthographic(aLeft, aRight, aBottom, aUp, aZNear, aZFar);
	}

	void Camera::SetPosition(const Vector3D<float32>& aCameraPosition)
	{
		mCameraPosition = aCameraPosition;
		mViewMatrix = Matrix4x4::lookAt(&aCameraPosition, &mCameraLookAt, &mUp);
	}

	void Camera::SetLookAt(const Vector3D<float32>& aCameraLookAt)
	{
		mCameraLookAt = aCameraLookAt;
		mViewMatrix = Matrix4x4::lookAt(&mCameraPosition, &aCameraLookAt, &mUp);
	}
	void Camera::SetUp(const Vector3D<float32>& aUp)
	{
		mUp = aUp;
		mViewMatrix = Matrix4x4::lookAt(&mCameraPosition, &mCameraLookAt, &aUp);
	}
	void Camera::FollowTarget(const logic::IGameObject* aTarget, const Vector3D<float32>& aPositionOffset, const Vector3D<float32>& aLookAtOffset)
	{
		mTarget = aTarget;
		mPositionOffset = aPositionOffset;
		mLookAtOffset = aLookAtOffset;
	}

} // namespace graphics

