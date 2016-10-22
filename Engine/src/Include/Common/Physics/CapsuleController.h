#ifndef _ENGINE_PHYSICS_CAPSULECONTROLLER_H_
#define _ENGINE_PHYSICS_CAPSULECONTROLLER_H_

#include "Types.h"

#include "Support/Vector3D.h"

#include "Physics/Collider.h"

#include "characterkinematic/PxCapsuleController.h"

namespace physics
{
	/**

	*/
	class CapsuleController : public Collider
	{
		friend class PhysicsManager;
		REGISTER_COMPONENT_HEAD(CapsuleController)
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
		Vector3D<float32>								mDisplacement;
		float32											mMinDistance;
	public:
		virtual void									SetPosition(const Vector3D<float32> aPosition);
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
		*/
		void											Move(const Vector3D<float32>& aDisplacement, float32 aMinDistance);
		virtual void									Move(const Vector3D<float32>& aDisplacement);
		virtual void									AddForce(const Vector3D<float32>& aForce);
	protected:
		CapsuleController() : Collider() {}
		virtual ~CapsuleController() {}
		virtual void									Init(BOOL aActive);
		virtual void									Init(BOOL aActive, PhysicActor* aPhysicsActor, eColliderType aColliderType, BOOL aTrigger);
		virtual void									FixedUpdate();
		virtual void									SetPhysicCampsuleController(PhysicCampsuleController* aPhysicCampsuleController);
	}; // CapsuleController
} // namespace physics
#endif // _ENGINE_PHYSICS_CAPSULECONTROLLER_H_
