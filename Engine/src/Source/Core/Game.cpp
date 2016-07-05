#include "Core\Game.h"
#include "Core\GameDescription.h"
#include "Core\Log.h"

#include "System\GameState.h"
#include "System\Time.h"

#include "Graphics\RenderManager.h"

#include "Core\Application.h"

#include "Logic\World.h"

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

		core::Application::Instance()->Init();

		graphics::RenderManager::Instance()->Init(title, aGameDescription.mScreenSize, aGameDescription.mScreenPosition,
												  aGameDescription.mRenderDrawColor, aGameDescription.mFullScreen);

		logic::World::Instance()->Init(32, 32);

		return TRUE;
	}

	void Game::Run() {
		mRunning = TRUE;

		sys::Time::Instance()->Update();

		while (mRunning)
		{
			sys::Time::Instance()->Update();			
			HandleEvents();
			Update();
			Render();
		}

		Release();
	}

	void Game::Update() {
		logic::World::Instance()->Update();
		//mCurrentGameState->Update(0.2f);
	}

	void Game::Render() {
		graphics::RenderManager::Instance()->Render();
	}

	void Game::Release()
	{
		//mCurrentGameState->Release();

		graphics::RenderManager::Instance()->Release();

		core::Application::Instance()->Release();

		logic::World::Instance()->Release();
	}

	void Game::HandleEvents()
	{
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					mRunning = false;
					break;
				default:
					break;
			}
		}
	}

	void Game::CloseGame()
	{
		mRunning = FALSE;
	}
} // namespace core