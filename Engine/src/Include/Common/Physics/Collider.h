#ifndef _ENGINE_PHYSICS_COLLIDER_H_
#define _ENGINE_PHYSICS_COLLIDER_H_

#include "Types.h"
#include "Logic/IComponent.h"

namespace logic{
	class IGameObject;
}

namespace physics
{
	/**
	
	*/
	class Collider : public logic::IComponent {
	public:
		friend class CollisionManager;
		friend class PhysicsManager;
		typedef void(logic::IGameObject::*OnTrigger)(const Collider*) const;

		enum eColliderType
		{
			eStatic = 0,
			eDynamic,
			eKinematic
		};

	protected:
		struct TColliderCallback
		{
			Collider::OnTrigger							mOnTriggerCallback;
			const logic::IGameObject*					mGameObject;
		};
		BOOL											mTrigger;
		TColliderCallback*								mOnTriggerEnterCallback;
		TColliderCallback*								mOnTriggerExitCallback;
		TColliderCallback*								mOnTriggerStayCallback;
	protected:
		Collider() : logic::IComponent(), mOnTriggerEnterCallback(NULL), mOnTriggerExitCallback(NULL) {}
		virtual ~Collider() {}
		virtual void									Init(BOOL aActive);
		virtual void									Release();
		//@TODO should be public
		virtual void									SetTrigger(BOOL aTrigger) { mTrigger = aTrigger; }

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
	public:
		virtual BOOL									GetTrigger() { return mTrigger; }

		/**
		Set the callback function to trigger enter. 
		@note, If the callback already exits remplaces it
		*/
		void											SetOnTriggerEnterCallback(Collider::OnTrigger aCallback, const logic::IGameObject* aGameObject);
		/**
		Set the callback function to trigger exit. 
		@note, If the callback already exits remplaces it
		*/
		void											SetOnTriggerExitCallback(Collider::OnTrigger aCallback, const logic::IGameObject* aGameObject);
		/**
		Set the callback function to trigger stay.
		@note, If the callback already exits remplaces it
		*/
		void											SetOnTriggerStayCallback(Collider::OnTrigger aCallback, const logic::IGameObject* aGameObject);

	}; // IComponent
} // namespace physics
#endif // _ENGINE_PHYSICS_COLLIDER_H_
