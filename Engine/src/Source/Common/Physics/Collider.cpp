#include "Physics/Collider.h"
#include "Physics/PhysicsManager.h"

#include "Logic/IGameObject.h"

#include "Core/Log.h"

#include "Support/Math.h"

#include <PxRigidDynamic.h>

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
		mPhysicsCallbacks.clear();
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

	void Collider::OnTriggerEnter(Collider* other)
	{
		mPhysicsCallbacks[eTriggerEnter](other);
	}

	void Collider::OnTriggerExit(Collider* other)
	{
		mPhysicsCallbacks[eTriggerExit](other);
	}

	void Collider::OnTriggerStay(Collider* other)
	{
		mPhysicsCallbacks[eTriggerStay](other);
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		mPhysicsCallbacks[eCollisionEnter](other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		mPhysicsCallbacks[eCollisionExit](other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		mPhysicsCallbacks[eCollisionStay](other);
	}

	void Collider::AddForce(const Vector3D<float32>& aForce)
	{
		if (mColliderType != eColliderType::eStatic)
		{
			((physx::PxRigidDynamic*)mPhysicActor)->addForce(physx::PxVec3(EXPOSE_VECTOR3D(aForce)));
		}
	}
	
} // namespace physics
