#include "Physics/CollisionManager.h"
#include "Physics/Collider.h"

#include <PxRigidActor.h>
#include <PxShape.h> 
#include <PxSimulationEventCallback.h> 

#include <assert.h>

namespace physics
{
	//PxSimulationEventCallback
	void CollisionManager::onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count)
	{

	}

	void CollisionManager::onWake(physx::PxActor** actors, physx::PxU32 count)
	{

	}

	void CollisionManager::onSleep(physx::PxActor** actors, physx::PxU32 count)
	{
		
	}


	void CollisionManager::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
	{

	}

	void CollisionManager::onTrigger(physx::PxTriggerPair* aPairs, physx::PxU32 aCount)
	{
		for (uint32 i = 0; i < aCount; ++i) {
			if (aPairs[i].flags & (physx::PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER | physx::PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
				continue;

			bool enter = aPairs[i].status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
			bool exit = aPairs[i].status & physx::PxPairFlag::eNOTIFY_TOUCH_LOST;

			Collider *lTriggerCollider = (Collider*)aPairs[i].triggerShape->getActor()->userData;
			assert(lTriggerCollider && "onTrigger, triggerShape->userData NULL");

			Collider* lOtherCollider = (Collider*)aPairs[i].otherShape->getActor()->userData;
			assert(lOtherCollider && "onTrigger, otherShape->userData NULL");

			if (enter)
				lTriggerCollider->OnTriggerEnter(lOtherCollider);
			else if (exit)
				lTriggerCollider->OnTriggerExit(lOtherCollider);
			else
				lTriggerCollider->OnTriggerStay(lOtherCollider);

			BOOL lOtherIsTrigger = aPairs[i].otherShape->getFlags().isSet(physx::PxShapeFlag::eTRIGGER_SHAPE);
			if (lOtherIsTrigger)
			{
				if (enter)
					lOtherCollider->OnTriggerEnter(lTriggerCollider);
				else if (exit)
					lOtherCollider->OnTriggerExit(lTriggerCollider);
				else
					lOtherCollider->OnTriggerStay(lTriggerCollider);
			}
		}
	}

	//PxUserControllerHitReport
	void CollisionManager::onShapeHit(const physx::PxControllerShapeHit& hit)
	{
		
	}


	void CollisionManager::onControllerHit(const physx::PxControllersHit& hit)
	{
		
	}


	void CollisionManager::onObstacleHit(const physx::PxControllerObstacleHit& hit)
	{

	}

}; // namespace physics
