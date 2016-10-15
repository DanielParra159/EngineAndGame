#ifndef _ENGINE_PHYSICS_PHYSICSMANAGER_H_
#define _ENGINE_PHYSICS_PHYSICSMANAGER_H_

#include "Defs.h"
#include "Types.h"

namespace physx
{
	class PxErrorCallback;
	class PxAllocatorCallback;
	class PxFoundation;
	class PxProfileZoneManager;
	class PxCooking;
	class PxMaterial;
	class PxPhysics;
	class PxScene;

	namespace debugger
	{
		namespace comm
		{
			class PvdConnection;
		};
	};
};

namespace physics
{
	
	/**
	
	*/
	class PhysicsManager
	{
		SINGLETON_HEAD(PhysicsManager);
	private:
		physx::PxErrorCallback*							mErrorManager;
		physx::PxAllocatorCallback*						mAllocator;
		physx::PxFoundation*							mFoundation;
		physx::PxProfileZoneManager*					mProfileZoneManager;
		physx::PxPhysics*								mPhysics;
		physx::PxCooking*								mCooking;
		physx::PxMaterial*								mDefaultMaterial;
		physx::debugger::comm::PvdConnection*			mPvdConnection;
	public:
		BOOL											Init();
		void											Release();
		void											Update();

	private:
		PhysicsManager() {}
		~PhysicsManager() {}

	}; // PhysicsManager
} // namespace physics
#endif // _ENGINE_PHYSICS_PHYSICSMANAGER_H_
