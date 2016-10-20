#ifndef _ENGINE_LOGIC_MATRIXSCENE_H_
#define _ENGINE_LOGIC_MATRIXSCENE_H_

#include "Defs.h"
#include "Types.h"

#include <vector>
#include <unordered_set>

namespace logic
{
	class IGameObject;

	typedef std::vector<IGameObject*>					TGameObjectsList;
	typedef std::unordered_set<IGameObject*>			TGameObjectsSet;
	/**
	It represents the world in the scene. This uses a vector of GameObjects
	@see logic::WorldCell
	*/
	class World
	{
		SINGLETON_HEAD(World);
	private:
		TGameObjectsSet									mActivatedGameObjects;
		TGameObjectsList								mGameObjectsToBeActivated;
		TGameObjectsSet									mDisabledGameObjects;
		TGameObjectsList								mGameObjectsToBeDisabled;
		TGameObjectsList								mGameObjectsToRemove;
	public:
		void											Init();
		void											Release();

		void											Update();
		void											FixedUpdate();
		void											Render();

		void											AddGameObject(IGameObject* aGameObject, BOOL aActivated);
		void											RemoveGameObject(IGameObject* aGameObject);
		void											DisableGameObject(IGameObject* aGameObject);
		void											ActiveGameObject(IGameObject* aGameObject);

	private:
		World() : mActivatedGameObjects(), mGameObjectsToBeActivated(), mDisabledGameObjects(), 
			mGameObjectsToBeDisabled(), mGameObjectsToRemove(){}
		~World() {}
		void											RemoveGameObjects();

	}; // World

} // namespace logic
#endif // _ENGINE_LOGIC_MATRIXSCENE_H_
