#ifndef _SYS_GAME_H_
#define _SYS_GAME_H_

#include "Types.h"

#include <SDL.h>

namespace graphics
{
	class Sprite;
}

namespace sys
{
	class IGameState;
	class GameDescription;

	class Game {
	friend class TextureManager;
	private:
		IGameState*									mCurrentGameState;
		static Game*								sInstance;
		SDL_Window*									mWindow;	
		SDL_Renderer*								mRenderer;
		BOOL										mRunning;

		graphics::Sprite *aux;
	public:
		static Game*								Instance();

		BOOL		 								Init(const int8* title, const GameDescription *aGameDescription);
		void										Run();

		void										CloseGame();
		SDL_Renderer*								GetRenderer();
	private:
		void										Update();
		void										Render();
		void										HandleEvents();
		void										Release();
		Game();
		~Game();
		
	}; // Game
} // namespace sys
#endif // _SYS_GAME_H_
