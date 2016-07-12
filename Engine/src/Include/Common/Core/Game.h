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
		static Game*								sInstance;		
		IGameState*									mCurrentGameState;
		IGameState*									mNextGameState;

		/**
		Indicates if the application should keep running
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
		Prepare the next game state to be changed in the next update
		@param aGameState the game state to assign
		*/
		void										ChangeGameState(IGameState* aGameState);
	private:
		Game() : mRunning(FALSE), mCurrentGameState(0) {}
		~Game() {}

		void										Update();
		void										Render();
		void										Release();

		/**
		Set the current GameState and initialize it
		@param aGameState the game state to assign
		*/
		BOOL										SetGameState(IGameState* aGameState);

		
		
	}; // Game
} // namespace core
#endif // _CORE_GAME_H_
