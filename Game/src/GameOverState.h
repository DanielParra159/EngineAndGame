#ifndef _GAME_GAMEOVERTATE_H_
#define _GAME_GAMEOVERTATE_H_

#include "Types.h"

#include "Core\IGameState.h"

namespace ui
{
	class Menu;
}

namespace game
{
	class GameOverState : public core::IGameState
	{
	private:
		ui::Menu*										mMenu;
	public:
		GameOverState() {}
		~GameOverState() {}
	protected:
		virtual BOOL 									Init();
		virtual void 									Release();

		virtual BOOL									Update();
		virtual void									Render();

		virtual const int8*								GetStateName() const { return "GameOver"; }
	private:
		static void										StartGame();
	}; // GameOverState
} // namespace game
#endif // _GAME_GAMEOVERTATE_H_
