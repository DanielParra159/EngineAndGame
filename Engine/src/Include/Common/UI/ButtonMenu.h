#ifndef _ENGINE_UI_BUTTON_H_
#define _ENGINE_UI_BUTTON_H_

#include "Types.h"
#include "Types\Rect.h"
#include "UI\Menu.h"

namespace graphics
{
	class Sprite;
}

namespace ui
{
	class ButtonMenu
	{
		friend class Menu;
	private:
		CallbackFunction								mCallback;
	protected:
		Rect<int32>										mButtonImageRect;
		graphics::Sprite*								mImage;
		Rect<int32>										mPositionRect;

	public:
		void											Init(const Rect<int32>& aPositionRect, const Rect<int32>& aButtonRect, CallbackFunction aCallback, const char* aImage);

	protected:
		ButtonMenu() : mButtonImageRect(), mCallback(), mImage(), mPositionRect() {}
		virtual ~ButtonMenu() {}
	private:
		void											OnMouseClick(const Vector2D<>& aPos);
		void											Render();
		void											Release();

	}; // ButtonMenu

} // namespace ui
#endif // _ENGINE_UI_BUTTON_H_
