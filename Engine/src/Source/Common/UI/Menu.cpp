#include "UI\Menu.h"
#include "UI\ButtonMenu.h"

#include "Graphics\Sprite.h"

namespace ui
{
	ButtonMenu* Menu::AddButton(const Rect<int32> &aButtonRect, CallbackFunction aCallback, float32 aTextScale, const Color32& aTextColor, const std::string& aText, const char* aImage)
	{
		ButtonMenu *lButtonMenu = new ButtonMenu();
		lButtonMenu->Init(aButtonRect, aCallback, aTextScale, aTextColor, aText, aImage);
		mButtons.push_back(lButtonMenu);
		return lButtonMenu;
	}

	ButtonMenu* Menu::AddButtonWithImage(const Rect<int32> &aButtonRect, CallbackFunction aCallback, const char* aImage)
	{
		ButtonMenu *lButtonMenu = new ButtonMenu();
		lButtonMenu->InitWithImage(aButtonRect, aCallback, aImage);
		mButtons.push_back(lButtonMenu);
		return lButtonMenu;
	}

	ButtonMenu* Menu::AddButtonWithText(const Rect<int32> &aButtonRect, CallbackFunction aCallback, const std::string& aText, float32 aTextScale, const Color32& aTextColor)
	{
		ButtonMenu *lButtonMenu = new ButtonMenu();
		lButtonMenu->InitWithText(aButtonRect, aCallback, aText, aTextScale, aTextColor);
		mButtons.push_back(lButtonMenu);
		return lButtonMenu;
	}

	void Menu::Update(const Vector2D<>& aPos)
	{
		TButtons::const_iterator lIterator = mButtons.begin();
		TButtons::const_iterator lIteratorEnd = mButtons.end();

		for (; lIterator != lIteratorEnd; ++lIterator)
			(*lIterator)->Update(aPos);
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

	void Menu::OnMouseClick()
	{
		TButtons::const_iterator lIterator = mButtons.begin();
		TButtons::const_iterator lIteratorEnd = mButtons.end();

		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			if ((*lIterator)->mFocused)
				(*lIterator)->OnMouseClick();
		}
	}

} // namespace ui
