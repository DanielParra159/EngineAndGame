#include "Physics/CapsuleController.h"
#include "Physics/PhysicsManager.h"

#include "System/Time.h"

#include "characterkinematic/PxCapsuleController.h"

namespace physics
{
	REGISTER_COMPONENT_BODY(CapsuleController, physics)

	void CapsuleController::Init(BOOL aActive)
	{
		IComponent::Init(mActive);
		mGround = FALSE;
	}

	void CapsuleController::Init(BOOL aActive, PhysicActor* aPhysicsActor, eColliderType aColliderType, BOOL aTrigger)
	{
		Collider::Init(aActive, aPhysicsActor, aColliderType, aTrigger);
		mGround = FALSE;
		mDisplacement = Vector3D<float32>::zero;	
		mMinDistance = 0.2f;
	}


	void CapsuleController::FixedUpdate()
	{
		float32 lDeltaTime = sys::Time::Instance()->GetDeltaSec();

		if (!mGround) {
			mDisplacement += PhysicsManager::Instance()->GetGravity() * lDeltaTime;
		}

		uint32 lFlags = mPhysicCampsuleController->move(physx::PxVec3(EXPOSE_VECTOR3D(mDisplacement)), mMinDistance, lDeltaTime , physx::PxControllerFilters());
		mGround = (lFlags & physx::PxControllerFlag::eCOLLISION_DOWN);

		mDisplacement = Vector3D<float32>::zero;

		Collider::FixedUpdate();
	}

	void CapsuleController::SetPosition(const Vector3D<float32> aPosition)
	{
		mPhysicCampsuleController->setPosition(physx::PxExtendedVec3(EXPOSE_VECTOR3D(aPosition)));
	}

	void CapsuleController::SetPhysicCampsuleController(PhysicCampsuleController* aPhysicCampsuleController)
	{
		mPhysicCampsuleController = aPhysicCampsuleController;
		SetPhysicActor((physx::PxRigidActor*)mPhysicCampsuleController->getActor());
	}

	void CapsuleController::Move(const Vector3D<float32>& aDisplacement)
	{
		mDisplacement = aDisplacement;
	}
	void CapsuleController::Move(const Vector3D<float32>& aDisplacement, float32 aMinDistance)
	{
		mDisplacement = aDisplacement;
		mMinDistance = aMinDistance;
	}
} // namespace physics
