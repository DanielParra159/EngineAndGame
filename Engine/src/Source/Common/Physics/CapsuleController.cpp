#include "Physics/CapsuleController.h"

#include "System/Time.h"

#include "characterkinematic/PxCapsuleController.h"

namespace physics
{
	void CapsuleController::Init(BOOL aActive)
	{
		Collider::Init(mActive);
		mGround = FALSE;
	}

	void CapsuleController::Init(BOOL aActive, PhysicActor* aPhysicsActor, eColliderType aColliderType, BOOL aTrigger)
	{
		Collider::Init(aActive, aPhysicsActor, aColliderType, aTrigger);
		mGround = FALSE;
	}

	void CapsuleController::SetPhysicCampsuleController(PhysicCampsuleController* aPhysicCampsuleController)
	{
		mPhysicCampsuleController = aPhysicCampsuleController;
		SetPhysicActor((physx::PxRigidActor*)mPhysicCampsuleController->getActor());
	}

	void CapsuleController::Move(const Vector3D<float32>& aDisplacement, float32 aMinDistance, float32 aElapsedTime)
	{
		uint32 lFlags = mPhysicCampsuleController->move(physx::PxVec3(EXPOSE_VECTOR3D(aDisplacement)), aMinDistance, aElapsedTime, physx::PxControllerFilters());
		mGround = (lFlags & physx::PxControllerFlag::eCOLLISION_DOWN);
	}
} // namespace physics
