#ifndef _GAME_BUTTON_H_
#define _GAME_BUTTON_H_

#include "Types.h"
#include "Support\Rect.h"
#include "UI\MainMenu.h"
#include "UI\ButtonMenu.h"

namespace game
{
	class Button : public ui::ButtonMenu
	{

	protected:
		Button() : ButtonMenu() {}
		virtual ~Button() {}

	}; // Button

} // namespace game
#endif // _GAME_BUTTON_H_
