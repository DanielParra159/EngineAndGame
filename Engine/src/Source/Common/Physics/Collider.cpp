#include "Physics/Collider.h"
#include "Physics/PhysicsManager.h"

#include "Logic/IGameObject.h"

#include "Core/Log.h"

#include "Support/Math.h"

#include <PxRigidDynamic.h>
#include <assert.h>

namespace physics
{
	REGISTER_COMPONENT_BODY(Collider, physics)

	void Collider::Init(BOOL aActive, PhysicActor* aPhysicsActor, eColliderType aColliderType, BOOL aTrigger)
	{
		IComponent::Init(aActive);
		mPhysicActor = aPhysicsActor;
		mColliderType = aColliderType;
		mTrigger = aTrigger;
		mRegisteredCollisionCallback = eNone;
	}

	void Collider::FixedUpdate()
	{
		float32 lAngle;
		physx::PxVec3 lAxis;
		mPhysicActor->getGlobalPose().q.toRadiansAndUnitAxis(lAngle, lAxis);
		physx::PxVec3 lPosition = mPhysicActor->getGlobalPose().p;
		mParent->SetRotation(Vector3D<float>(lAxis.x, lAxis.y, lAxis.z)*Math::Degrees(lAngle));
		mParent->SetPosition(lPosition.x, lPosition.y, lPosition.z);
	}

	void Collider::Release()
	{
		PhysicsManager::Instance()->RemoveCollider(this);
	}

	void Collider::SetCallbacks(logic::IGameObject* aGameObject, UpdateFunction& aUpdateFunction, FixedUpdateFunction& aFixedUpdateFunction, RenderFunction& aRenderFunction)
	{
		IComponent::SetCallbacks(aGameObject, aUpdateFunction, aFixedUpdateFunction, aRenderFunction);
		aUpdateFunction = NULL;
		aFixedUpdateFunction = IComponent::FixedUpdateCallbackFunction;
		aRenderFunction = NULL;
	}

	void Collider::SetParent(logic::IGameObject* aParent)
	{
		Collider::IComponent::SetParent(aParent);
		float32 lAngle;
		physx::PxVec3 lAxis;
		mPhysicActor->getGlobalPose().q.toRadiansAndUnitAxis(lAngle, lAxis);
		physx::PxVec3 lPosition = mPhysicActor->getGlobalPose().p;
		mParent->SetRotation(Vector3D<float>(lAxis.x, lAxis.y, lAxis.z)*Math::Degrees(lAngle));
		mParent->SetPosition(lPosition.x, lPosition.y, lPosition.z);
	}

	void Collider::SetPosition(const Vector3D<float32> aPosition)
	{
		if (mColliderType == eColliderType::eKinematic)
		{
			physx::PxTransform lTransform = mPhysicActor->getGlobalPose();
			lTransform.p = physx::PxVec3(EXPOSE_VECTOR3D(aPosition));
			((physx::PxRigidDynamic*)mPhysicActor)->setKinematicTarget(lTransform);
		}
	}

	void Collider::Move(const Vector3D<float32>& aDisplacement)
	{
		if (mColliderType == eColliderType::eKinematic)
		{
			physx::PxTransform lTransform = mPhysicActor->getGlobalPose();
			lTransform.p += physx::PxVec3(EXPOSE_VECTOR3D(aDisplacement));
			((physx::PxRigidDynamic*)mPhysicActor)->setKinematicTarget(lTransform);
		}
	}

	void Collider::SetOnTriggerEnterCallback(uint32 aCollisionFlags)
	{
		mRegisteredCollisionCallback = aCollisionFlags;
	}

	void Collider::OnTriggerEnter(Collider* other)
	{
		mParent->OnTriggerEnter(other);
	}

	void Collider::OnTriggerExit(Collider* other)
	{
		mParent->OnTriggerExit(other);
	}

	void Collider::OnTriggerStay(Collider* other)
	{
		mParent->OnTriggerStay(other);
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		mParent->OnCollisionEnter(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		mParent->OnCollisionExit(other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		mParent->OnCollisionStay(other);
	}
	
} // namespace physics
