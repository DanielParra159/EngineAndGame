#include "Input\InputManager.h"
#include "Input\KeyboardController.h"
#include "Input\InputAction.h"


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
		return TRUE;
	}
	void InputManager::Release()
	{

	}

	void InputManager::Update()
	{
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

	IController* InputManager::CreateController(eTypeControls aType)
	{
		IController* lResult;

		switch (aType)
		{
			case eTypeControls::Keyboard:
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

	int32 InputManager::PullActionId()
	{
		return mLastAction;
	}

	int32 InputManager::GetActionId()
	{
		return mLastAction;
	}

} // namespace input
