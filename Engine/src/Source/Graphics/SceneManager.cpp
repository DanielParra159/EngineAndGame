#include "Graphics\SceneManager.h"
#include "Graphics\Scene.h"
#include "Graphics\MatrixScene.h"

namespace graphics
{
	SceneManager* SceneManager::sInstance = 0;

	SceneManager* SceneManager::Instance()
	{
		if (SceneManager::sInstance == 0)
		{
			SceneManager::sInstance = new SceneManager();
			return SceneManager::sInstance;
		}
		return SceneManager::sInstance;
	}

	void SceneManager::Init()
	{

	}

	void SceneManager::Release()
	{

	}

	void SceneManager::Update()
	{
		if (mCurrentScene)
			mCurrentScene->Update();
	}

	void SceneManager::Render()
	{
		if (mCurrentScene)
			mCurrentScene->Render();
	}

	/*IScene* SceneManager::CreateScene()
	{
		IScene* lResult;

		return lResult;
	}*/

	MatrixScene* SceneManager::CreateMatrixScene(uint32 aWidth, uint32 aHeight)
	{
		MatrixScene* lResult = new MatrixScene(0);
		lResult->Init(aWidth, aHeight);

		return lResult;
	}

	IScene* SceneManager::GetCurrentScene()
	{
		return mCurrentScene;
	}

	void SceneManager::SetScene(IScene* aScene)
	{
		if (mCurrentScene)
		{
			RemoveCurrentScene();
		}
		mCurrentScene = aScene;
	}

	void SceneManager::RemoveCurrentScene()
	{
		delete mCurrentScene;
	}
}