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

namespace graphics
{
	class TextRenderer;
	class Sprite;
}

namespace game
{
	class MenuState : public core::IGameState
	{
	private:
		ui::Menu*										mMenu;
		audio::Sound2D*									mMusic;
		graphics::TextRenderer*							mTextRenderer;
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
		static void										StartGame1();
		static void										StartGame2();
		static void										StartGame3();
		static void										Exit();
	}; // MenuState
} // namespace game
#endif // _GAME_MENUSTATE_H_
