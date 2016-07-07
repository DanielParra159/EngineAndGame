#include "Input\InputManager.h"
#include "Input\KeyboardController.h"
#include "Input\InputAction.h"

#include <SDL.h>

namespace input
{
	InputManager* InputManager::sInstance = 0;

	InputManager* InputManager::Instance()
	{
		if (InputManager::sInstance == 0)
		{
			InputManager::sInstance = new InputManager();
			return InputManager::sInstance;
		}
		return InputManager::sInstance;
	}

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
		mLastAction = -1;

		TControllers::const_iterator lIterator = mControllers.begin();
		TControllers::const_iterator lIteratorEnd = mControllers.end();

		if (*lIterator == 0)
			return;

		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			//@TODO: this only allows an action for frame, the fist controller detects an action
			if ((mLastAction = (*lIterator)->Update()) != 0)
				break;
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
					lResult = 0;
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

	int32 InputManager::GetActionId()
	{
		return mLastAction;
	}

} // namespace input