#ifndef _GAME_GAMESTATE_H_
#define _GAME_GAMESTATE_H_

#include "Types.h"

#include "Core\IGameState.h"

namespace game
{
	enum EInputActions
	{
		eExit,
		eUp, eDown, eLeft, eRight
	};

	enum ETypeEntities
	{
		eWall0 = 0,
		eWall1 = 1,
		eNothing = 2,
		eSnakeHead = 3,
		eSnakeTail = 4,
		ePoint = 5
	};

	class Player;
	class GameState : public core::IGameState
	{
	private:
		Player*											mPlayer;
	public:
		GameState() : mPlayer(0) {}
		~GameState() {}
	protected:
		virtual BOOL 									Init();
		virtual void 									Release();

		virtual BOOL									Update();
		virtual void									Render();

		virtual const int8*								GetStateName() const { return "Game"; }
	}; // IGameState
} // namespace game
#endif // _GAME_GAMESTATE_H_
