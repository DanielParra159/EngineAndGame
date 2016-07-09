#include "UI\Menu.h"
#include "UI\ButtonMenu.h"

#include "Graphics\Sprite.h"

namespace ui
{
	void Menu::AddButton(const Rect<int32>& aPositionRect, const Rect<int32> &aButtonRect, CallbackFunction aCallback, const char* aImage)
	{
		ButtonMenu *lButtonMenu = new ButtonMenu();
		lButtonMenu->Init(aPositionRect, aButtonRect, aCallback, aImage);
		mButtons.push_back(lButtonMenu);
	}

	void Menu::Render()
	{
		TButtons::const_iterator lIterator = mButtons.begin();
		TButtons::const_iterator lIteratorEnd = mButtons.end();
		
		for ( ; lIterator != lIteratorEnd; ++lIterator)
			(*lIterator)->Render();
	}

	void Menu::Release()
	{
		TButtons::const_iterator lIterator = mButtons.begin();
		TButtons::const_iterator lIteratorEnd = mButtons.end();

		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			(*lIterator)->Release();
			delete (*lIterator);
		}

		mButtons.clear();
	}

	void Menu::OnMouseClick(const Vector2D<>& aPos)
	{
		TButtons::const_iterator lIterator = mButtons.begin();
		TButtons::const_iterator lIteratorEnd = mButtons.end();

		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			(*lIterator)->OnMouseClick(aPos);
		}
	}

} // namespace ui
