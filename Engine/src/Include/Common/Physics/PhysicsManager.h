#ifndef _ENGINE_PHYSICS_PHYSICSMANAGER_H_
#define _ENGINE_PHYSICS_PHYSICSMANAGER_H_

#include "Defs.h"
#include "Types.h"

#include "Support/Vector3D.h"

#include "Physics/Collider.h"

#include "PxFiltering.h"

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
	class PxDefaultCpuDispatcher;
	class PxControllerManager;
	struct PxFilterData;

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
	typedef physx::PxMaterial PhysicsMaterial;
	class CollisionManager;
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
		PhysicsMaterial*								mDefaultMaterial;
		physx::debugger::comm::PvdConnection*			mPvdConnection;
		CollisionManager*								mCollisionManager;
		physx::PxScene*									mActiveScene;
		physx::PxDefaultCpuDispatcher*					mCpuDispatcher;
		physx::PxControllerManager*						mControllerManager;
	public:
		BOOL											Init(float32 aGravity);
		void											Release();
		void											Update();

		/**
		Create an PhysicsMaterial, the user must release it later
		*/
		PhysicsMaterial*								CreateMaterial(float32 aStaticFriction, float32 aDynamicFriction, float32 aRestitution);

		Collider*										CreateBoxCollider(const Vector3D<float32> &aPosition, const Vector3D<float32> &aPositionOffset, const Vector3D<float32> &aDimensions,
																		  BOOL aTrigger, uint32 aLayerMask, uint32 aCollisionMask, Collider::eColliderType aColliderType, float32 aMass = 0.0f);
		Collider*										CreatePlaneCollider(const Vector3D<float32> &aPosition, const Vector3D<float32> &aNormal, uint32 aLayerMask, uint32 aCollisionMask);
	private:
		PhysicsManager() {}
		~PhysicsManager() {}
		static physx::PxFilterFlags FilterShader(
			uint32 aAttributes0, physx::PxFilterData aFilterData0,
			uint32 aAttributes1, physx::PxFilterData aFilterData1,
			physx::PxPairFlags& aPairFlags, const void* aConstantBlock, uint32 aConstantBlockSize);

		void											CreateScene(float32 aGravity);
	}; // PhysicsManager
} // namespace physics
#endif // _ENGINE_PHYSICS_PHYSICSMANAGER_H_
