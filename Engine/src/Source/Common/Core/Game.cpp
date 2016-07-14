#include "Core\Game.h"
#include "Core\GameDescription.h"
#include "Core\IGameState.h"
#include "Core\Log.h"

#include "System\Time.h"

#include "Graphics\RenderManager.h"

#include "Input\InputManager.h"

#include "UI\MenuManager.h"

#include "Audio\AudioManager.h"

#include "Logic\World.h"

#include "Defs.h"

#include "SDL.h"

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

		ui::MenuManager::Instance()->Init();

		audio::AudioManager::Instance()->Init();

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

		ui::MenuManager::Instance()->Release();

		input::InputManager::Instance()->Release();

		graphics::RenderManager::Instance()->Release();
		
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