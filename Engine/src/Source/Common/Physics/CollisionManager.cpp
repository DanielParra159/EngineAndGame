#include "Physics/CollisionManager.h"


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

	void CollisionManager::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
	{

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
