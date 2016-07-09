#ifndef _ENGINE_UI_MENU_H_
#define _ENGINE_UI_MENU_H_

#include "Types.h"
#include "Types\Rect.h"
#include "Types\Vector2D.h"
#include "UI\MenuManager.h"

#include <vector>

namespace graphics
{
	class Sprite;
}

namespace ui
{
	class ButtonMenu;
	class Menu
	{
		friend class MenuManager;
		typedef std::vector<ButtonMenu*>				TButtons;
	private:
		TButtons										mButtons;
	public:
		void											AddButton(const Rect<int32>& aPositionRect, const Rect<int32>& aButtonRect, CallbackFunction aCallback, const char* aImage = 0);
	protected:
		Menu() : mButtons() {};
		virtual ~Menu() {}
		virtual void									Update() {};
	private:
		void											Render();
		void											Release();
		void											OnMouseClick(const Vector2D<>& aPos);


	}; // Menu

} // namespace ui
#endif // _ENGINE_UI_MENU_H_
