#include "System\Game.h"

#include "System\GameState.h"
#include "System\GameDescription.h"

#include "Graphics\TextureManager.h"
#include "Graphics\Sprite.h"

namespace sys
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

	Game::~Game()
	{
		Game::sInstance = 0;
	}

	Game::Game() : mRenderer(0), mWindow(0), mRunning(FALSE)
	{

	}

	BOOL Game::Init(const int8* title, const GameDescription *aGameDescription) {

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			return FALSE;

		mWindow = SDL_CreateWindow(title,
									aGameDescription->mScreenPositionX, aGameDescription->mScreenPositionY,
									aGameDescription->mScreenSizeX, aGameDescription->mScreenSizeY,
									aGameDescription->mFullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);

		// if the window creation succeeded create our renderer
		if (mWindow == 0)
			return FALSE;
					
		mRenderer = SDL_CreateRenderer(mWindow, -1, 0);

		if (mRenderer == 0)
			return FALSE;

		SDL_SetRenderDrawColor(mRenderer,
			aGameDescription->mRenderDrawColor.GetR(),
			aGameDescription->mRenderDrawColor.GetG(),
			aGameDescription->mRenderDrawColor.GetB(),
			aGameDescription->mRenderDrawColor.GetA());


		graphics::TextureManager::Instance()->Init();

		return TRUE;
	}

	void Game::Run() {
		mRunning = TRUE;

		aux = graphics::TextureManager::Instance()->CreateSprite("assets/prueba.png");
		aux->SetSize(450, 450);

		while (mRunning)
		{
			HandleEvents();
			Update();
			Render();
		}

		Release();
	}

	void Game::Update() {
		//mCurrentGameState->Update(0.2f);
	}

	void Game::Render() {
		SDL_RenderClear(mRenderer);
			
		aux->Render(mRenderer, 100, 100);

		SDL_RenderPresent(mRenderer); // draw to the screen

		//mCurrentGameState->Render();
	}

	void Game::Release()
	{
		//mCurrentGameState->Release();

		graphics::TextureManager::Instance()->Release();

		SDL_DestroyWindow(mWindow);
		SDL_DestroyRenderer(mRenderer);
		SDL_Quit();
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

	SDL_Renderer* Game::GetRenderer()
	{
		return mRenderer;
	}
}