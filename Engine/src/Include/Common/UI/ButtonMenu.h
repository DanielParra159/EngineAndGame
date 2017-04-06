#ifndef _ENGINE_UI_BUTTON_H_
#define _ENGINE_UI_BUTTON_H_

#include "Types.h"
#include "Support/Rect.h"
#include "Support/Color32.h"
#include "UI/Menu.h"

#include <string>

namespace graphics
{
	class Sprite;
	class TextRenderer;
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
		graphics::TextRenderer*							mTextRenderer;
		std::string										mText;
		float32											mTextScale;
		Color32											mTextColor;

		BOOL											mFocused;
	public:
		void											Init(const Rect<int32>& aButtonRect, CallbackFunction aCallback, float32 aTextScale, const Color32& aTextColor, const std::string& aText, const char* aImage);
		void											InitWithImage(const Rect<int32>& aButtonRect, CallbackFunction aCallback, const char* aImage);
		void											InitWithText(const Rect<int32>& aButtonRect, CallbackFunction aCallback, const std::string& aText, float32 aScale, const Color32& aColor);

	protected:
		ButtonMenu() : mButtonRect(), mCallback(NULL), mSprite(NULL),
			mTextRenderer(NULL), mText(), mTextScale(), mTextColor(), 
			mFocused(FALSE){}
		virtual ~ButtonMenu() {}
	private:
		/**
		This function is called when the user clicked on screen and detect if he has clicked on the button
		@param aPos, the cursor position on the screen
		*/
		void											OnMouseClick();
		void											OnFocusEnter(const Vector2D<>& aPos);
		void											OnFocusExit(const Vector2D<>& aPos);
		BOOL											CheckInside(const Vector2D<>& aPos);
		void											Update(const Vector2D<>& aPos);
		void											Render();
		void											Release();
		void											Init(const Rect<int32>& aButtonRect, CallbackFunction aCallback);

	}; // ButtonMenu

} // namespace ui
#endif // _ENGINE_UI_BUTTON_H_
