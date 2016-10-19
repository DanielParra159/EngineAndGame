#include "Core/Game.h"
#include "Core/GameDescription.h"
#include "Core/IGameState.h"
#include "Core/Log.h"

#include "System/Time.h"

#include "Graphics/RenderManager.h"

#include "Input/InputManager.h"

#include "UI/MenuManager.h"

#include "Audio/AudioManager.h"

#include "IO/FileSystem.h"

#include "Script/ScriptManager.h"

#include "Physics/PhysicsManager.h"

#include "Logic/World.h"
#include "Logic/ComponentFactory.h"

#include "Defs.h"

#include <SDL.h>

namespace core
{
	SINGLETON_BODY(Game);

	BOOL Game::Init(const int8* title, const GameDescription& aGameDescription)
	{
		logic::ComponentFactory::Instance()->Init();

		io::FileSystem::Instance()->Init(aGameDescription.mRootDir);

		physics::PhysicsManager::Instance()->Init(aGameDescription.mPhysicsGravity);

		graphics::RenderManager::Instance()->Init(title, aGameDescription.mScreenSize, aGameDescription.mScreenPosition,
												  aGameDescription.mClearColor, aGameDescription.mFullScreen);
		
		input::InputManager::Instance()->Init();

		ui::MenuManager::Instance()->Init();

		script::ScriptManager::Instance()->Init();

		audio::AudioManager::Instance()->Init(1.0f);

		return TRUE;
	}

	void Game::Run() {
		mRunning = TRUE;

		sys::Time::Instance()->Update();

		while (mRunning)
		{
			sys::Time::Instance()->Update();			
			input::InputManager::Instance()->Update();
			input::InputManager::Instance()->GetLastActionId();
			ui::MenuManager::Instance()->Update();
			audio::AudioManager::Instance()->Update();
			physics::PhysicsManager::Instance()->Update(); //@TODO fixedUpdate
			Update();
			Render();
		}

		Release();
	}

	void Game::Update() {
		if (mNextGameState)
		{
			SetGameState(mNextGameState);
			mNextGameState = 0;
		}
		else if (mCurrentGameState)
			mRunning = mCurrentGameState->Update();
	}

	void Game::Render() {
		if (mCurrentGameState)
			mCurrentGameState->Render();
	}

	void Game::Release()
	{
		if (mCurrentGameState)
			mCurrentGameState->Release();

		audio::AudioManager::Instance()->Release();

		script::ScriptManager::Instance()->Release();

		ui::MenuManager::Instance()->Release();

		input::InputManager::Instance()->Release();

		graphics::RenderManager::Instance()->Release();

		physics::PhysicsManager::Instance()->Release();
		
		io::FileSystem::Instance()->Release();

		logic::ComponentFactory::Instance()->Release();

		SDL_Quit();

	}

	BOOL Game::SetGameState(IGameState* aGameState)
	{
		if (mCurrentGameState)
		{
			mCurrentGameState->Release();
			delete mCurrentGameState;
		}
		mCurrentGameState = aGameState;
		return aGameState->Init();
	}

	void Game::ChangeGameState(IGameState* aGameState)
	{
		mNextGameState = aGameState;
	}

} // namespace core