#include "Core\Game.h"
#include "Core\GameDescription.h"
#include "Core\IGameState.h"
#include "Core\Log.h"

#include "System\Time.h"

#include "Graphics\RenderManager.h"

#include "Input\InputManager.h"

#include "Defs.h"

#include <SDL.h>

namespace core
{
	Game* Game::sInstance = 0;

	Game* Game::Instance()
	{
		if (Game::sInstance == 0)
		{
			Game::sInstance = new Game();
			return Game::sInstance;
		}
		return Game::sInstance;
	}

	BOOL Game::Init(const int8* title, const GameDescription& aGameDescription)
	{
		graphics::RenderManager::Instance()->Init(title, aGameDescription.mScreenSize, aGameDescription.mScreenPosition,
												  aGameDescription.mRenderDrawColor, aGameDescription.mFullScreen);
		
		input::InputManager::Instance()->Init();

		return TRUE;
	}

	void Game::Run() {
		mRunning = TRUE;

		sys::Time::Instance()->Update();

		while (mRunning)
		{
			sys::Time::Instance()->Update();			
			input::InputManager::Instance()->Update();
			input::InputManager::Instance()->GetActionId();
			Update();
			Render();
		}

		Release();
	}

	void Game::Update() {
		if (mCurrentGameState)
			mRunning = mCurrentGameState->Update();
	}

	void Game::Render() {
		graphics::RenderManager::Instance()->Render();
	}

	void Game::Release()
	{
		if (mCurrentGameState)
			mCurrentGameState->Release();

		graphics::RenderManager::Instance()->Release();

		input::InputManager::Instance()->Release();
		
		SDL_Quit();

	}

	BOOL Game::SetGameState(IGameState* aGameState)
	{
		mCurrentGameState = aGameState;
		return aGameState->Init();
	}

} // namespace core