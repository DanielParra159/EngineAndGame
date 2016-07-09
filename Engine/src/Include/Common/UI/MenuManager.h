#ifndef _ENGINE_UI_MENUMANAGER_H_
#define _ENGINE_UI_MENUMANAGER_H_

#include "Types.h"

#include <vector>

namespace ui
{
	typedef void(*CallbackFunction)();
	class Menu;
	class MenuManager
	{
		typedef	std::vector<Menu*>						TMenus;
	private:
		static MenuManager*								sInstance;
		TMenus											mMenus;
	public:
		static MenuManager*								Instance();
		BOOL											Init();
		void											Release();

		void											Render();
		void											Update();

		Menu*											CreateMenu();
		void											RemoveMenu(Menu* aMenu);
	private:
		MenuManager() : mMenus() {};
		~MenuManager() {}



	}; // MenuManager

} // namespace ui
#endif // _ENGINE_UI_MENUMANAGER_H_
