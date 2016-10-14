#include "Logic\World.h"
#include "Logic\IGameObject.h"

#include "Defs.h"

#include "Graphics\Sprite.h"
#include "Graphics\RenderManager.h"

#include "System\Time.h"
#include "Core\Log.h"

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

	void World::Render()
	{
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

} // namespace logic