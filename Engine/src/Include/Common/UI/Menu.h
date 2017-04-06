#ifndef _ENGINE_UI_MENU_H_
#define _ENGINE_UI_MENU_H_

#include "Types.h"
#include "Support/Rect.h"
#include "Support/Vector2D.h"
#include "Support/Color32.h"
#include "UI/MenuManager.h"

#include <vector>

namespace graphics
{
	class Sprite;
}

namespace ui
{
	class ButtonMenu;
	/**

	*/
	class Menu
	{
		friend class MenuManager;
		typedef std::vector<ButtonMenu*>				TButtons;
	private:
		/**
		All the buttons that contains this menu
		*/
		TButtons										mButtons;
	public:
		/**
		Add a button to the menu
		@param aButtonRect, position and size of the button
		@param aCallback, function to callback if the button is clicked
		@param aImage, image of the button, can be null
		*/
		ButtonMenu*										AddButton(const Rect<int32>& aButtonRect, CallbackFunction aCallback, float32 aTextScale = 1.0f, const Color32& aTextColor = Color32::white, const std::string& aText = NULL, const char* aImage = NULL);
		ButtonMenu*										AddButtonWithImage(const Rect<int32>& aButtonRect, CallbackFunction aCallback, const char* aImage);
		ButtonMenu*										AddButtonWithText(const Rect<int32>& aButtonRect, CallbackFunction aCallback, const std::string& aText, float32 aTextScale = 1.0f, const Color32& aTextColor = Color32::white);
	protected:
		Menu() : mButtons() {};
		virtual ~Menu() {}
	private:
		void											Update(const Vector2D<>& aPos);
		void											Render();
		void											Release();
		/**
		This function is called when the user clicked on screen and communicates to the buttons that contains
		@param aPos, the cursor position on the screen
		*/
		void											OnMouseClick();


	}; // Menu

} // namespace ui
#endif // _ENGINE_UI_MENU_H_
