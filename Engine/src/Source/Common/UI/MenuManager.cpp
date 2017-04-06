#include "UI\MenuManager.h"
#include "UI\Menu.h"

#include "Input\InputManager.h"
#include "Input\MouseController.h"

namespace ui
{

	SINGLETON_BODY(MenuManager);

	BOOL MenuManager::Init()
	{
		return TRUE;
	}

	void MenuManager::Release()
	{
		TMenus::const_iterator lIterator = mMenus.begin();
		TMenus::const_iterator lIteratorEnd = mMenus.end();
		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			(*lIterator)->Release();
			delete (*lIterator);
		}

		mMenus.clear();
	}

	void MenuManager::Render()
	{
		TMenus::const_iterator lIterator = mMenus.begin();
		TMenus::const_iterator lIteratorEnd = mMenus.end();
		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			(*lIterator)->Render();
		}
	}

	void MenuManager::Update()
	{
		input::MouseController* lMouseController = (input::MouseController*)input::InputManager::Instance()->GetController(input::eMouse);

		BOOL lButtonPressed = lMouseController->IsButtonPressed(input::MouseController::eLeftButton);
		Vector2D<> lMousePos = Vector2D<>();
		lMouseController->GetMousePos(lMousePos);

		TMenus::const_iterator lIterator = mMenus.begin();
		TMenus::const_iterator lIteratorEnd = mMenus.end();
		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			(*lIterator)->Update(lMousePos);
			if (lButtonPressed)
			{
				(*lIterator)->OnMouseClick();
			}
		}
	}

	Menu* MenuManager::CreateMenu()
	{
		Menu* lMenu = new Menu();
		mMenus.push_back(lMenu);

		return lMenu;
	}

	void MenuManager::RemoveMenu(Menu* aMenu)
	{
		TMenus::const_iterator lIterator = mMenus.begin();
		TMenus::const_iterator lIteratorEnd = mMenus.end();
		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			if ((*lIterator) == aMenu)
			{
				mMenus.erase(lIterator);
				break;
			}
		}
	}

} // namespace ui
