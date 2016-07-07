#include "Core\Game.h"
#include "Core\GameDescription.h"
#include "Core\IGameState.h"
#include "Core\Log.h"

#include "System\Time.h"

#include "Graphics\RenderManager.h"

#include "Input\InputManager.h"

#include "Core\Application.h"

#include "Defs.h"

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
		core::Application::Instance()->Release();

	}

	BOOL Game::SetGameState(IGameState* aGameState)
	{
		mCurrentGameState = aGameState;
		return aGameState->Init();
	}

} // namespace core