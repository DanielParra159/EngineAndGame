#include "Input\InputManager.h"
#include "Input\KeyboardController.h"
#include "Input\MouseController.h"
#include "Input\InputAction.h"

#include "SDL.h"

namespace input
{
	SINGLETON_BODY(InputManager);

	BOOL InputManager::Init()
	{
		if (SDL_Init(SDL_INIT_EVENTS) < 0)
			return FALSE;
		return TRUE;
	}
	void InputManager::Release()
	{

	}

	void InputManager::Update()
	{
		SDL_Event lEvent;
		if (SDL_PollEvent(&lEvent))
		{
			//if (lEvent.type == SDL_QUIT)
			TControllers::const_iterator lIterator = mControllers.begin();
			TControllers::const_iterator lIteratorEnd = mControllers.end();

			for (; lIterator != lIteratorEnd; ++lIterator)
			{
				(*lIterator)->Update(lEvent);
			}
		}

		
	}

	IController* InputManager::CreateController(ETypeControls aType)
	{
		IController* lResult;

		switch (aType)
		{
			case ETypeControls::eKeyboard:
				lResult = new KeyboardController();
				if (!lResult->Init())
				{
					delete lResult;
					lResult = NULL;
				}
				else 
				{
					mControllers.push_back(lResult);
				}
				break;
			case ETypeControls::eMouse:
				lResult = new MouseController();
				if (!lResult->Init())
				{
					delete lResult;
					lResult = NULL;
				}
				else
				{
					mControllers.push_back(lResult);
				}
				break;
			default:
				break;
		}
		return lResult;
	}

	IController* InputManager::GetController(ETypeControls aType)
	{
		IController* lResult = NULL;

		TControllers::const_iterator lIterator = mControllers.begin();
		TControllers::const_iterator lIteratorEnd = mControllers.end();
		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			if ((*lIterator)->GetType() == aType)
			{
				lResult = *lIterator;
				break;
			}
		}

		return lResult;
	}

	BOOL InputManager::IsActionDown(uint32 aActionId)
	{
		BOOL lResult = FALSE;
		TControllers::const_iterator lIterator = mControllers.begin();
		TControllers::const_iterator lIteratorEnd = mControllers.end();
		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			lResult |= (*lIterator)->IsActionDown(aActionId);
		}
		return lResult;
	}

	BOOL InputManager::IsActionUp(uint32 aActionId)
	{
		BOOL lResult = FALSE;
		TControllers::const_iterator lIterator = mControllers.begin();
		TControllers::const_iterator lIteratorEnd = mControllers.end();
		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			lResult |= (*lIterator)->IsActionUp(aActionId);
		}
		return lResult;
	}

} // namespace input
