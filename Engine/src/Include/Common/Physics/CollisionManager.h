#ifndef _ENGINE_PHYSICS_COLLISIONMANAGER_H_
#define _ENGINE_PHYSICS_COLLISIONMANAGER_H_

#include "Types.h"

#include <PxSimulationEventCallback.h> 
#include <characterkinematic/PxController.h>

namespace physics
{
	/**
	
	*/
	class CollisionManager : public physx::PxSimulationEventCallback,
								public physx::PxUserControllerHitReport
	{
		friend class PhysicsManager;
	protected:
		CollisionManager() {}
		virtual ~CollisionManager() {}

		//PxSimulationEventCallback
		virtual void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count);
		virtual void onWake(physx::PxActor** actors, physx::PxU32 count);
		virtual void onSleep(physx::PxActor** actors, physx::PxU32 count);
		virtual void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs);
		virtual void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count);

		//PxUserControllerHitReport
		virtual void onShapeHit(const physx::PxControllerShapeHit& hit);
		virtual void onControllerHit(const physx::PxControllersHit& hit);
		virtual void onObstacleHit(const physx::PxControllerObstacleHit& hit);

	}; // CollisionManager

}; // namespace physics

#endif // _ENGINE_PHYSICS_COLLISIONMANAGER_H_