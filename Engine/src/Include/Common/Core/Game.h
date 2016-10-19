#ifndef _CORE_GAME_H_
#define _CORE_GAME_H_

#include "Defs.h"
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
		SINGLETON_HEAD(Game);
	private:	
		IGameState*									mCurrentGameState;
		IGameState*									mNextGameState;
		float32										mAccumulatePhysicTime;
		uint8										mNumPhysicUpdateLoops;
		const uint8									mMaxmNumPhysicUpdateLoops = 2;

		/**
		Indicates if the application should keep running
		*/
		BOOL										mRunning;
	public:
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
		void										FixedUpdate();
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
