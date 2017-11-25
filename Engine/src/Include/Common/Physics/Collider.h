#ifndef _ENGINE_PHYSICS_COLLIDER_H_
#define _ENGINE_PHYSICS_COLLIDER_H_

#include "Defs.h"
#include "Types.h"
#include "Logic/IComponent.h"

#include <unordered_map>
#include <assert.h>
#include <functional>

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
		enum eColliderType
		{
			eStatic = 0,
			eDynamic,
			eKinematic
		};

		enum eRegisterCollisionCallback
		{
			eNone = (1 >> 1),
			eTriggerEnter = (1 << 1),
			eTriggerExit = (1 << 2),
			eTriggerStay = (1 << 3),
			eCollisionEnter = (1 << 4),
			eCollisionExit = (1 << 5),
			eCollisionStay = (1 << 6)
		};

		friend class CollisionManager;
		friend class PhysicsManager;
		typedef physx::PxRigidActor PhysicActor;
		typedef void (CallbackMethodPtr2)(Collider*);

		typedef std::unordered_map<eRegisterCollisionCallback, std::function<CallbackMethodPtr2>>	TPhysicsCallbacks;


		template <typename UserClass>
		struct ObjectMethodDelegate {
			typedef void (UserClass::* CallbackMethodPtr)(Collider*);
		};
	
		template<class UserClass>
		void BindPhysicsCallback(eRegisterCollisionCallback aCallback, UserClass *obj, typename ObjectMethodDelegate<UserClass>::CallbackMethodPtr method)
		{
			assert((aCallback | eNone) != eNone && "eRegisterCollisionCallback can't be eNone");
			assert(mPhysicsCallbacks.find(aCallback) == mPhysicsCallbacks.end() && "Callback already binded");

			mRegisteredCollisionCallback |= aCallback;

			mPhysicsCallbacks[aCallback] = std::bind(method, obj, std::placeholders::_1);
		}

	protected:
		BOOL											mTrigger;
		eColliderType									mColliderType;
		PhysicActor*									mPhysicActor;
		uint32											mRegisteredCollisionCallback;

		TPhysicsCallbacks								mPhysicsCallbacks;
	protected:
		Collider() : logic::IComponent(), mPhysicActor(0), mTrigger(FALSE),
			mColliderType(), mRegisteredCollisionCallback(eNone) {}
		virtual ~Collider() {}
		virtual void									Init(BOOL aActive, PhysicActor* aPhysicsActor, eColliderType aColliderType, BOOL aTrigger);
		virtual void									Release();
		virtual void									FixedUpdate();
		virtual void									SetCallbacks(logic::IGameObject* aGameObject, UpdateFunction& aUpdateFunction, FixedUpdateFunction& aFixedUpdateFunction, RenderFunction& aRenderFunction);
		virtual void									SetParent(logic::IGameObject* aParent);
		//@TODO should be public and modify PhysX
		virtual void									SetTrigger(BOOL aTrigger) { mTrigger = aTrigger; }
		virtual void									SetPhysicActor(PhysicActor* aPhysicActor) { mPhysicActor = aPhysicActor; }
		/**
		Method called when collider enter on this collider configured as trigger
		*/
		void											OnTriggerEnter(Collider* other);
		/**
		Method called when collider exit on this collider configured as trigger
		*/
		void											OnTriggerExit(Collider* other);
		/**
		Method called when collider stay on this collider configured as trigger
		*/
		void											OnTriggerStay(Collider* other);

		void											OnCollisionEnter(Collider* other);
		void											OnCollisionExit(Collider* other);
		void											OnCollisionStay(Collider* other);
	public:
		virtual void									SetPosition(const Vector3D<float32> aPosition);
		virtual void									Move(const Vector3D<float32>& aDisplacement);
		virtual BOOL									GetTrigger() { return mTrigger; }


		virtual void									AddForce(const Vector3D<float32>& aForce);
	}; // Collider
} // namespace physics
#endif // _ENGINE_PHYSICS_COLLIDER_H_
