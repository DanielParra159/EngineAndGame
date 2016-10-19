#ifndef _GAME_GAMESTATE_H_
#define _GAME_GAMESTATE_H_

#include "Types.h"

#include "Core\IGameState.h"

namespace ui
{
	class Menu;
}

namespace graphics
{
	class Mesh;
}

namespace game
{
	enum EInputActions
	{
		eExit,
		eUp, eDown, eLeft, eRight
	};

	class Map;

	class GameState : public core::IGameState
	{
	private:
		ui::Menu*										mMenu;
	public:
		GameState() {}
		~GameState() {}
	protected:
		virtual BOOL 									Init();
		virtual void 									Release();

		virtual BOOL									Update();
		virtual void									FixedUpdate();
		virtual void									Render();

		virtual const int8*								GetStateName() const { return "Snake"; }
	}; // GameState
} // namespace game
#endif // _GAME_GAMESTATE_H_
