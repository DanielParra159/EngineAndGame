#ifndef _ENGINE_UI_MENUMANAGER_H_
#define _ENGINE_UI_MENUMANAGER_H_

#include "Defs.h"
#include "Types.h"

#include <vector>

namespace core
{
	class Game;
}

namespace ui
{
	typedef void(*CallbackFunction)();
	class Menu;
	/**
	Controls menus created
	*/
	class MenuManager
	{
		friend class core::Game;
		typedef	std::vector<Menu*>						TMenus;

		SINGLETON_HEAD(MenuManager);
	private:
		/**
		All the menus
		*/
		TMenus											mMenus;
	public:
		BOOL											Init();
		void											Release();

		void											Render();
		void											Update();

		/**
		Allows to create a menu
		@return the menu created or null
		*/
		Menu*											CreateMenu();
		/**
		Remove one menu of the menu manager
		@param aMenu, the menu to remove
		*/
		void											RemoveMenu(Menu* aMenu);
	private:
		MenuManager() : mMenus() {};
		~MenuManager() {}



	}; // MenuManager

} // namespace ui
#endif // _ENGINE_UI_MENUMANAGER_H_
