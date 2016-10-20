#ifndef _GAME_MENUSTATE_H_
#define _GAME_MENUSTATE_H_

#include "Types.h"

#include "Core\IGameState.h"

namespace audio
{
	class Sound2D;
}

namespace ui
{
	class Menu;
}

namespace game
{
	class MenuState : public core::IGameState
	{
	private:
		ui::Menu*										mMenu;
		audio::Sound2D*									mMusic;
	public:
		MenuState() {}
		~MenuState() {}
	protected:
		virtual BOOL 									Init();
		virtual void 									Release();

		virtual BOOL									Update();
		virtual void									Render();

		virtual const int8*								GetStateName() const { return "Menu"; }
	private:
		static void										StartGame();
	}; // MenuState
} // namespace game
#endif // _GAME_MENUSTATE_H_
