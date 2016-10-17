#include "Physics/CollisionManager.h"
#include "Physics/Collider.h"
#include "Core/Log.h"

#include <PxRigidActor.h>
#include <PxShape.h> 
#include <PxSimulationEventCallback.h> 

#include <assert.h>

namespace physics
{
	CollisionManager::CollisionManager() {}
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


	void CollisionManager::onContact(const physx::PxContactPairHeader& aPairHeader, const physx::PxContactPair* aPairs, physx::PxU32 aNumPairs)
	{
		for (uint32 i = 0; i < aNumPairs; ++i) {

			//if (aPairs[i].flags & (physx::PxContactPairFlag::eREMOVED_SHAPE_0 | physx::PxContactPairFlag::eREMOVED_SHAPE_1))
			//	continue;
			
			const physx::PxContactPair& lContactPair = aPairs[i];
			
			Collider *lCollider = (Collider*)aPairHeader.actors[0]->userData;
			assert(lCollider && "onTrigger, triggerShape->userData NULL");

			Collider* lOtherCollider = (Collider*)aPairHeader.actors[1]->userData;
			assert(lOtherCollider && "onTrigger, otherShape->userData NULL");

			if (lContactPair.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
			{
				lCollider->OnCollisionEnter(lOtherCollider);
				lOtherCollider->OnCollisionEnter(lCollider);
			} 
			else if (lContactPair.events & physx::PxPairFlag::eNOTIFY_TOUCH_LOST)
			{
				lCollider->OnCollisionExit(lOtherCollider);
				lOtherCollider->OnCollisionExit(lCollider);
			}
			else if (lContactPair.events & physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS)
			{
				lCollider->OnCollisionStay(lOtherCollider);
				lOtherCollider->OnCollisionStay(lCollider);
			}
		}
	}

	void CollisionManager::onTrigger(physx::PxTriggerPair* aPairs, physx::PxU32 aCount)
	{
		for (uint32 i = 0; i < aCount; ++i) {
			core::LogString("onTrigger");
			const physx::PxTriggerPair& lTriggerPair = aPairs[i];
			if (lTriggerPair.flags & (physx::PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER | physx::PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
				continue;

			bool enter = lTriggerPair.status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
			bool exit = lTriggerPair.status & physx::PxPairFlag::eNOTIFY_TOUCH_LOST;

			Collider *lTriggerCollider = (Collider*)lTriggerPair.triggerShape->getActor()->userData;
			assert(lTriggerCollider && "onTrigger, triggerShape->userData NULL");

			Collider* lOtherCollider = (Collider*)lTriggerPair.otherShape->getActor()->userData;
			assert(lOtherCollider && "onTrigger, otherShape->userData NULL");

			if (enter)
				lTriggerCollider->OnTriggerEnter(lOtherCollider);
			else if (exit)
				lTriggerCollider->OnTriggerExit(lOtherCollider);
			else
				lTriggerCollider->OnTriggerStay(lOtherCollider);

			if (lTriggerPair.otherShape->getFlags().isSet(physx::PxShapeFlag::eTRIGGER_SHAPE))
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
