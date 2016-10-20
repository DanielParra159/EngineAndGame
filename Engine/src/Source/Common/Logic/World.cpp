#include "Logic\World.h"
#include "Logic\IGameObject.h"

#include "Defs.h"

#include "Graphics\Sprite.h"
#include "Graphics\RenderManager.h"

#include "System\Time.h"
#include "Core\Log.h"

#include <assert.h>

namespace logic
{

	SINGLETON_BODY(World);

	void World::Init()
	{
		
	}

	void World::Release()
	{
		TGameObjectsSet::const_iterator lIterator = mActivatedGameObjects.begin();
		TGameObjectsSet::const_iterator lIteratorEnd = mActivatedGameObjects.end();
		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			(*lIterator)->Release();
			delete (*lIterator);
		}
		mActivatedGameObjects.clear();

		lIterator = mDisabledGameObjects.begin();
		lIteratorEnd = mDisabledGameObjects.end();
		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			(*lIterator)->Release();
			delete (*lIterator);
		}
		mDisabledGameObjects.clear();

		mGameObjectsToBeActivated.clear();
		mGameObjectsToBeDisabled.clear();

	}

	void World::Update()
	{
		if (mGameObjectsToRemove.size() > 0)
			RemoveGameObjects();

		TGameObjectsSet::const_iterator lSetIterator = mActivatedGameObjects.begin();
		TGameObjectsSet::const_iterator lSetIteratorEnd = mActivatedGameObjects.end();
		for (; lSetIterator != lSetIteratorEnd; ++lSetIterator)
		{
			(*lSetIterator)->Update();
		}

		TGameObjectsList::const_iterator lListIterator = mGameObjectsToBeDisabled.begin();
		TGameObjectsList::const_iterator lListIteratorEnd = mGameObjectsToBeDisabled.end();
		for (; lListIterator != lListIteratorEnd; ++lListIterator)
		{
			mActivatedGameObjects.erase(*(lListIterator));
			mDisabledGameObjects.insert(*(lListIterator));
		}
		mGameObjectsToBeDisabled.clear();

		lListIterator = mGameObjectsToBeActivated.begin();
		lListIteratorEnd = mGameObjectsToBeActivated.end();
		for (; lListIterator != lListIteratorEnd; ++lListIterator)
		{
			mDisabledGameObjects.erase(*(lListIterator));
			mActivatedGameObjects.insert(*(lListIterator));
		}
		mGameObjectsToBeActivated.clear();
		
	}

	void World::FixedUpdate()
	{
		if (mGameObjectsToRemove.size() > 0)
			RemoveGameObjects();

		TGameObjectsSet::const_iterator lSetIterator = mActivatedGameObjects.begin();
		TGameObjectsSet::const_iterator lSetIteratorEnd = mActivatedGameObjects.end();
		for (; lSetIterator != lSetIteratorEnd; ++lSetIterator)
		{
			(*lSetIterator)->FixedUpdate();
		}
	}

	void World::Render()
	{
		if (mGameObjectsToRemove.size() > 0)
			RemoveGameObjects();
		//@TODO: sort
		TGameObjectsSet::const_iterator lSetIterator = mActivatedGameObjects.begin();
		TGameObjectsSet::const_iterator lSetIteratorEnd = mActivatedGameObjects.end();
		for (; lSetIterator != lSetIteratorEnd; ++lSetIterator)
		{
			(*lSetIterator)->Render();
		}
	}

	void World::AddGameObject(IGameObject* aGameObject, BOOL aActivated)
	{
		aGameObject->Init(aActivated);
		if (aActivated)
			mActivatedGameObjects.insert(aGameObject);
		else
			mDisabledGameObjects.insert(aGameObject);
	}

	void World::RemoveGameObject(IGameObject* aGameObject){
		mGameObjectsToRemove.push_back(aGameObject);
	}

	void World::RemoveGameObjects()
	{
		TGameObjectsList::const_iterator lListRemoveIterator = mGameObjectsToRemove.begin();
		TGameObjectsList::const_iterator lListRemoveIteratorEnd = mGameObjectsToRemove.end();
		for (; lListRemoveIterator != lListRemoveIteratorEnd; ++lListRemoveIterator) {
			IGameObject* lGameObject = *lListRemoveIterator;
			if (lGameObject->mActive)
			{
				TGameObjectsSet::const_iterator lSetIterator = mActivatedGameObjects.find(lGameObject);
				if (lSetIterator != mActivatedGameObjects.end())
				{
					mActivatedGameObjects.erase(lSetIterator);
					lGameObject->Release();
				}
				else {
					TGameObjectsList::const_iterator lListIterator = mGameObjectsToBeDisabled.begin();
					TGameObjectsList::const_iterator lListIteratorEnd = mGameObjectsToBeDisabled.end();
					for (; lListIterator != lListIteratorEnd; ++lListIterator)
					{
						if (*lListIterator == lGameObject)
						{
							mGameObjectsToBeDisabled.erase(lListIterator);
							lGameObject->Release();
						}
					}
				}
			}
			else {
				TGameObjectsSet::const_iterator lSetIterator = mDisabledGameObjects.find(lGameObject);
				if (lSetIterator != mDisabledGameObjects.end())
				{
					mDisabledGameObjects.erase(lSetIterator);
					lGameObject->Release();
				}
				else {
					TGameObjectsList::const_iterator lListIterator = mGameObjectsToBeActivated.begin();
					TGameObjectsList::const_iterator lListIteratorEnd = mGameObjectsToBeActivated.end();
					for (; lListIterator != lListIteratorEnd; ++lListIterator)
					{
						if (*lListIterator == lGameObject)
						{
							mGameObjectsToBeActivated.erase(lListIterator);
							lGameObject->Release();
						}
					}
				}
			}
		}
	}
	void World::DisableGameObject(IGameObject* aGameObject)
	{
		assert(mActivatedGameObjects.find(aGameObject) != mActivatedGameObjects.end());
		mGameObjectsToBeDisabled.push_back(aGameObject);
	}
	void World::ActiveGameObject(IGameObject* aGameObject)
	{
		assert(mDisabledGameObjects.find(aGameObject) != mDisabledGameObjects.end());
		mGameObjectsToBeActivated.push_back(aGameObject);
	}

} // namespace logic