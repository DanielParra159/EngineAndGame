#ifndef _ENGINE_PHYSICS_COLLIDER_H_
#define _ENGINE_PHYSICS_COLLIDER_H_

#include "Defs.h"
#include "Types.h"
#include "Logic/IComponent.h"

namespace logic{
	class IGameObject;
}

namespace physx
{
	class PxRigidActor;
}

namespace physics
{
	/**
	
	*/
	class Collider : public logic::IComponent {
		REGISTER_COMPONENT_HEAD(Collider)
	public:
		friend class CollisionManager;
		friend class PhysicsManager;
		typedef void(logic::IGameObject::*OnCollision)(const Collider*) const;
		typedef physx::PxRigidActor PhysicActor;

		enum eColliderType
		{
			eStatic = 0,
			eDynamic,
			eKinematic
		};

	protected:
		struct TColliderCallback
		{
			Collider::OnCollision						mOnTriggerCallback;
			const logic::IGameObject*					mGameObject;
		};
		BOOL											mTrigger;
		eColliderType									mColliderType;
		PhysicActor*									mPhysicActor;
		TColliderCallback*								mOnTriggerEnterCallback;
		TColliderCallback*								mOnTriggerExitCallback;
		TColliderCallback*								mOnTriggerStayCallback;
		TColliderCallback*								mOnCollisionEnterCallback;
		TColliderCallback*								mOnCollisionExitCallback;
		TColliderCallback*								mOnCollisionStayCallback;
	protected:
		Collider() : logic::IComponent(), mOnTriggerEnterCallback(NULL), mOnTriggerExitCallback(NULL), mOnTriggerStayCallback(NULL),
			mOnCollisionEnterCallback(NULL), mOnCollisionExitCallback(NULL), mOnCollisionStayCallback(NULL)
		{}
		virtual ~Collider() {}
		virtual void									Init(BOOL aActive, PhysicActor* aPhysicsActor, eColliderType aColliderType, BOOL aTrigger);
		virtual void									Release();
		virtual void									FixedUpdate();
		virtual void									SetCallbacks(logic::IGameObject* aGameObject, UpdateFunction& aUpdateFunction, FixedUpdateFunction& aFixedUpdateFunction, RenderFunction& aRenderFunction);
		//@TODO should be public and modify PhysX
		virtual void									SetTrigger(BOOL aTrigger) { mTrigger = aTrigger; }
		virtual void									SetPhysicActor(PhysicActor* aPhysicActor) { mPhysicActor = aPhysicActor; }
		/**
		Method called when collider enter on this collider configured as trigger
		*/
		void											OnTriggerEnter(const Collider* other);
		/**
		Method called when collider exit on this collider configured as trigger
		*/
		void											OnTriggerExit(const Collider* other);
		/**
		Method called when collider stay on this collider configured as trigger
		*/
		void											OnTriggerStay(const Collider* other);

		void											OnCollisionEnter(const Collider* other);
		void											OnCollisionExit(const Collider* other);
		void											OnCollisionStay(const Collider* other);
	public:
		virtual void									SetPosition(const Vector3D<float32> aPosition);
		virtual void									Move(const Vector3D<float32>& aDisplacement);
		virtual BOOL									GetTrigger() { return mTrigger; }

		/**
		Set the callback function to trigger enter. 
		@note, If the callback already exits remplaces it
		*/
		void											SetOnTriggerEnterCallback(Collider::OnCollision aCallback, const logic::IGameObject* aGameObject);
		/**
		Set the callback function to trigger exit. 
		@note, If the callback already exits remplaces it
		*/
		void											SetOnTriggerExitCallback(Collider::OnCollision aCallback, const logic::IGameObject* aGameObject);
		/**
		Set the callback function to trigger stay.
		@note, If the callback already exits remplaces it
		*/
		void											SetOnTriggerStayCallback(Collider::OnCollision aCallback, const logic::IGameObject* aGameObject);

		void											SetOnCollisionEnterCallback(Collider::OnCollision aCallback, const logic::IGameObject* aGameObject);
		void											SetOnCollisionExitCallback(Collider::OnCollision aCallback, const logic::IGameObject* aGameObject);
		void											SetOnCollisionStayCallback(Collider::OnCollision aCallback, const logic::IGameObject* aGameObject);

	}; // Collider
} // namespace physics
#endif // _ENGINE_PHYSICS_COLLIDER_H_
