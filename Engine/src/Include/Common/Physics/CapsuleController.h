#ifndef _ENGINE_PHYSICS_CAPSULECONTROLLER_H_
#define _ENGINE_PHYSICS_CAPSULECONTROLLER_H_

#include "Types.h"

#include "Support/Vector3D.h"

#include "Physics/Collider.h"

#include "System/Time.h"

#include "characterkinematic/PxCapsuleController.h"

namespace physics
{
	/**

	*/
	class CapsuleController : public Collider
	{
		friend class PhysicsManager;
	public:
		enum eClimbingMode
		{
			eEASY = physx::PxCapsuleClimbingMode::eEASY, /**Standard mode, let the capsule climb over surfaces according to impact normal*/
			eCONSTRAINED = physx::PxCapsuleClimbingMode::eCONSTRAINED, /**Constrained mode, try to limit climbing according to the step offset*/
			eLAST = physx::PxCapsuleClimbingMode::eLAST
		};
		typedef physx::PxCapsuleController PhysicCampsuleController;
	protected:
		PhysicCampsuleController*						mPhysicCampsuleController;
		BOOL											mGround;
	public:
		virtual void									Init(BOOL aActive);
		virtual void									Init(BOOL aActive, PhysicActor* aPhysicsActor, eColliderType aColliderType, BOOL aTrigger);
		BOOL											GetGround()	{ return mGround; }
		void											SetHeight(float32 aHeight) { mPhysicCampsuleController->setHeight(aHeight); }
		float32											GetHeight() { return mPhysicCampsuleController->getHeight(); }
		void											SetRadius(float32 aRadius) { mPhysicCampsuleController->setRadius(aRadius); }
		float32											GetRadius() { return mPhysicCampsuleController->getRadius(); }
		void											SetClimbingMode(eClimbingMode aClimbingMode) { mPhysicCampsuleController->setClimbingMode((physx::PxCapsuleClimbingMode::Enum)aClimbingMode); }
		eClimbingMode									GetClimbingMode() { return (CapsuleController::eClimbingMode)mPhysicCampsuleController->getClimbingMode(); }
		void											SetSlopeLimit(float32 aSlopeLimit) { mPhysicCampsuleController->setSlopeLimit(aSlopeLimit); }
		float32											GetSlopeLimit() { return mPhysicCampsuleController->getSlopeLimit(); }

		/**
		Moves the character using a "collide-and-slide" algorithm.
		@param aDisplacement, Displacement vector
		@param aMinDistance The minimum travelled distance to consider. If travelled distance is smaller, the character doesn't move.
		This is used to stop the recursive motion algorithm when remaining distance to travel is small.
		@param aElapsedTime, Time elapsed since last call
		*/
		//@TODO: Encapsulate move and call only on update?
		void											Move(const Vector3D<float32>& aDisplacement, float32 aMinDistance, float32 aElapsedTime = sys::Time::Instance()->GetDeltaSec());
	protected:
		CapsuleController() : Collider() {}
		virtual ~CapsuleController() {}
		virtual void									SetPhysicCampsuleController(PhysicCampsuleController* aPhysicCampsuleController);
		//virtual void									Init(BOOL aActive, PhysicActor* aPhysicsActor, eColliderType aColliderType, BOOL aTrigger);
		//virtual void									Release();

	}; // CapsuleController
} // namespace physics
#endif // _ENGINE_PHYSICS_CAPSULECONTROLLER_H_
