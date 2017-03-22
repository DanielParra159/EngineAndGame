#ifndef _ENGINE_UI_BUTTON_H_
#define _ENGINE_UI_BUTTON_H_

#include "Types.h"
#include "Support\Rect.h"
#include "UI\Menu.h"

namespace graphics
{
	class Sprite;
}

namespace ui
{
	/**
	This class defines a button menu and class a callback function is it's pressed
	*/
	class ButtonMenu
	{
		friend class Menu;
	private:
		/**
		Callback function to call if button is pressed
		*/
		CallbackFunction								mCallback;
	protected:
		/**
		The size of the button on the texture
		*/
		Rect<int32>										mButtonRect;
		/**
		Pointer to the sprite, can be null
		*/
		graphics::Sprite*								mSprite;

	public:
		void											Init(const Rect<int32>& aButtonRect, CallbackFunction aCallback, const char* aImage);

	protected:
		ButtonMenu() : mButtonRect(), mCallback(), mSprite() {}
		virtual ~ButtonMenu() {}
	private:
		/**
		This function is called when the user clicked on screen and detect if he has clicked on the button
		@param aPos, the cursor position on the screen
		*/
		void											OnMouseClick(const Vector2D<>& aPos);
		void											Render();
		void											Release();

	}; // ButtonMenu

} // namespace ui
#endif // _ENGINE_UI_BUTTON_H_
