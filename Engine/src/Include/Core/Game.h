#ifndef _CORE_GAME_H_
#define _CORE_GAME_H_

#include "Types.h"

namespace core
{
	class IGameState;
	class GameDescription;

	class Game {
	private:
		IGameState*									mCurrentGameState;
		static Game*								sInstance;		
		BOOL										mRunning;
	public:
		static Game*								Instance();

		BOOL		 								Init(const int8* title, const GameDescription& aGameDescription);
		void										Run();

		void										CloseGame();
	private:
		void										Update();
		void										Render();
		void										HandleEvents();
		void										Release();
		Game() : mRunning(FALSE) {}
		~Game() {}
		
	}; // Game
} // namespace core
#endif // _CORE_GAME_H_
