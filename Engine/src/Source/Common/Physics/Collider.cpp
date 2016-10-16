#include "Physics\Collider.h"

#include <assert.h>

namespace physics
{

	void Collider::Init(BOOL aActive)
	{
		IComponent::Init(mActive);
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

	void Collider::SetOnTriggerEnterCallback(Collider::OnTrigger aCallback, const logic::IGameObject* aGameObject)
	{
		assert(aGameObject && "SetOnTriggerEnterCallback, aGameObject NULL");
		if (mOnTriggerEnterCallback)
			delete mOnTriggerEnterCallback;

		mOnTriggerEnterCallback = new TColliderCallback();
		mOnTriggerEnterCallback->mOnTriggerCallback = aCallback;
		mOnTriggerEnterCallback->mGameObject = aGameObject;
	}

	void Collider::SetOnTriggerExitCallback(Collider::OnTrigger aCallback, const logic::IGameObject* aGameObject)
	{
		assert(aGameObject && "SetOnTriggerExitCallback, aGameObject NULL");
		if (mOnTriggerExitCallback)
			delete mOnTriggerExitCallback;

		mOnTriggerExitCallback = new TColliderCallback();
		mOnTriggerExitCallback->mOnTriggerCallback = aCallback;
		mOnTriggerExitCallback->mGameObject = aGameObject;
	}

	void Collider::SetOnTriggerStayCallback(Collider::OnTrigger aCallback, const logic::IGameObject* aGameObject)
	{
		assert(aGameObject && "SetOnTriggerStayCallback, aGameObject NULL");
		if (mOnTriggerStayCallback)
			delete mOnTriggerStayCallback;

		mOnTriggerStayCallback = new TColliderCallback();
		mOnTriggerStayCallback->mOnTriggerCallback = aCallback;
		mOnTriggerStayCallback->mGameObject = aGameObject;
	}

} // namespace physics
