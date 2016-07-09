#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_

#include "Types.h"
#include "Types\Rect.h"

#include "UI\Menu.h"

namespace game
{
	class Button;
	class MainMenu : public ui::Menu
	{
	private:

	public:
		
	protected:
		MainMenu() {}
		virtual ~MainMenu() {}

		virtual void									Update();


	}; // MainMenu

} // namespace game
#endif // _GAME_MENU_H_
