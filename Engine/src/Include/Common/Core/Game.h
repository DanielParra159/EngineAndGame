#ifndef _CORE_GAME_H_
#define _CORE_GAME_H_

#include "Types.h"

namespace core
{
	class IGameState;
	class GameDescription;

	/**
	This class is responsible for init all manager and contains the game loop.
	Also it contains  the current state.
	The user must instantiate it, assign a state and run it.
	*/
	class Game {
	private:
		IGameState*									mCurrentGameState;
		static Game*								sInstance;		

		/**
		indicates if the application should keep running
		*/
		BOOL										mRunning;
	public:
		static Game*								Instance();

		BOOL		 								Init(const int8* title, const GameDescription& aGameDescription);
		/**
		Eject the game loop.
		@note Bloking call.
		*/
		void										Run();

		/**
		Set the current GameState and initialize it
		@param aGameState the game state to assign
		*/
		BOOL										SetGameState(IGameState* aGameState);
	private:
		void										Update();
		void										Render();
		void										Release();
		Game() : mRunning(FALSE), mCurrentGameState(0) {}
		~Game() {}
		
	}; // Game
} // namespace core
#endif // _CORE_GAME_H_
