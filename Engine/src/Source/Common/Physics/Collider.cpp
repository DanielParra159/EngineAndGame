#include "Physics\Collider.h"

#include <assert.h>

namespace physics
{
	REGISTER_COMPONENT_BODY(Collider, physics)

	void Collider::Init(BOOL aActive, PhysicActor* aPhysicsActor, eColliderType aColliderType, BOOL aTrigger)
	{
		IComponent::Init(aActive);
		mPhysicActor = aPhysicsActor;
		mColliderType = aColliderType;
		mTrigger = aTrigger;
	}

	void Collider::Release()
	{
		if (mOnTriggerEnterCallback)
			delete mOnTriggerEnterCallback;
		mOnTriggerEnterCallback = NULL;

		if (mOnTriggerExitCallback)
			delete mOnTriggerExitCallback;
		mOnTriggerExitCallback = NULL;

		if (mOnTriggerStayCallback)
			delete mOnTriggerStayCallback;
		mOnTriggerStayCallback = NULL;

		if (mOnTriggerEnterCallback)
			delete mOnTriggerEnterCallback;
		mOnTriggerEnterCallback = NULL;

		if (mOnTriggerExitCallback)
			delete mOnTriggerExitCallback;
		mOnTriggerExitCallback = NULL;

		if (mOnCollisionStayCallback)
			delete mOnCollisionStayCallback;
		mOnCollisionStayCallback = NULL;
	}

	void Collider::OnTriggerEnter(const Collider* other)
	{
		if (mOnTriggerEnterCallback)
		{
			assert(mOnTriggerEnterCallback->mGameObject && "OnTriggerEnter, mOnTriggerEnterCallback->mGameObject NULL");
			(mOnTriggerEnterCallback->mGameObject->*mOnTriggerEnterCallback->mOnTriggerCallback)(other);
		}
	}

	void Collider::OnTriggerExit(const Collider* other)
	{
		if (mOnTriggerEnterCallback)
		{
			assert(mOnTriggerExitCallback->mGameObject && "OnTriggerExit, mOnTriggerExitCallback->mGameObject NULL");
			(mOnTriggerExitCallback->mGameObject->*mOnTriggerExitCallback->mOnTriggerCallback)(other);
		}
	}

	void Collider::OnTriggerStay(const Collider* other)
	{
		if (mOnTriggerStayCallback)
		{
			assert(mOnTriggerStayCallback->mGameObject && "OnTriggerStay, mOnTriggerStayCallback->mGameObject NULL");
			(mOnTriggerStayCallback->mGameObject->*mOnTriggerStayCallback->mOnTriggerCallback)(other);
		}
	}

	void Collider::SetOnTriggerEnterCallback(Collider::OnCollision aCallback, const logic::IGameObject* aGameObject)
	{
		assert(aGameObject && "SetOnTriggerEnterCallback, aGameObject NULL");
		if (mOnTriggerEnterCallback)
			delete mOnTriggerEnterCallback;

		mOnTriggerEnterCallback = new TColliderCallback();
		mOnTriggerEnterCallback->mOnTriggerCallback = aCallback;
		mOnTriggerEnterCallback->mGameObject = aGameObject;
	}

	void Collider::SetOnTriggerExitCallback(Collider::OnCollision aCallback, const logic::IGameObject* aGameObject)
	{
		assert(aGameObject && "SetOnTriggerExitCallback, aGameObject NULL");
		if (mOnTriggerExitCallback)
			delete mOnTriggerExitCallback;

		mOnTriggerExitCallback = new TColliderCallback();
		mOnTriggerExitCallback->mOnTriggerCallback = aCallback;
		mOnTriggerExitCallback->mGameObject = aGameObject;
	}

	void Collider::SetOnTriggerStayCallback(Collider::OnCollision aCallback, const logic::IGameObject* aGameObject)
	{
		assert(aGameObject && "SetOnTriggerStayCallback, aGameObject NULL");
		if (mOnTriggerStayCallback)
			delete mOnTriggerStayCallback;

		mOnTriggerStayCallback = new TColliderCallback();
		mOnTriggerStayCallback->mOnTriggerCallback = aCallback;
		mOnTriggerStayCallback->mGameObject = aGameObject;
	}

	void Collider::OnCollisionEnter(const Collider* other)
	{
		if (mOnTriggerEnterCallback)
		{
			assert(mOnTriggerEnterCallback->mGameObject && "OnCollisionEnter, mOnTriggerEnterCallback->mGameObject NULL");
			(mOnTriggerEnterCallback->mGameObject->*mOnTriggerEnterCallback->mOnTriggerCallback)(other);
		}
	}

	void Collider::OnCollisionExit(const Collider* other)
	{
		if (mOnTriggerExitCallback)
		{
			assert(mOnTriggerExitCallback->mGameObject && "OnCollisionExit, mOnTriggerExitCallback->mGameObject NULL");
			(mOnTriggerExitCallback->mGameObject->*mOnTriggerExitCallback->mOnTriggerCallback)(other);
		}
	}

	void Collider::OnCollisionStay(const Collider* other)
	{
		if (mOnCollisionStayCallback)
		{
			assert(mOnCollisionStayCallback->mGameObject && "OnCollisionEnter, mOnCollisionStayCallback->mGameObject NULL");
			(mOnCollisionStayCallback->mGameObject->*mOnCollisionStayCallback->mOnTriggerCallback)(other);
		}
	}

	void Collider::SetOnCollisionEnterCallback(Collider::OnCollision aCallback, const logic::IGameObject* aGameObject)
	{
		assert(aGameObject && "SetOnCollisionEnterCallback, aGameObject NULL");
		if (mOnTriggerEnterCallback)
			delete mOnTriggerEnterCallback;

		mOnTriggerEnterCallback = new TColliderCallback();
		mOnTriggerEnterCallback->mOnTriggerCallback = aCallback;
		mOnTriggerEnterCallback->mGameObject = aGameObject;
	}

	void Collider::SetOnCollisionExitCallback(Collider::OnCollision aCallback, const logic::IGameObject* aGameObject)
	{
		assert(aGameObject && "SetOnCollisionExitCallback, aGameObject NULL");
		if (mOnTriggerExitCallback)
			delete mOnTriggerExitCallback;

		mOnTriggerExitCallback = new TColliderCallback();
		mOnTriggerExitCallback->mOnTriggerCallback = aCallback;
		mOnTriggerExitCallback->mGameObject = aGameObject;
	}

	void Collider::SetOnCollisionStayCallback(Collider::OnCollision aCallback, const logic::IGameObject* aGameObject)
	{
		assert(aGameObject && "SetOnCollisionStayCallback, aGameObject NULL");
		if (mOnCollisionStayCallback)
			delete mOnCollisionStayCallback;

		mOnCollisionStayCallback = new TColliderCallback();
		mOnCollisionStayCallback->mOnTriggerCallback = aCallback;
		mOnCollisionStayCallback->mGameObject = aGameObject;
	}
} // namespace physics
