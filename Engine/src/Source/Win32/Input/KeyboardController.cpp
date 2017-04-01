#include "Input\KeyboardController.h"
#include "Input\InputAction.h"

#include "SDL.h"

#include <assert.h>

namespace input
{

	BOOL KeyboardController::Init()
	{
		return TRUE;
	}
	void KeyboardController::Release()
	{
		TActionsByKey::const_iterator lIterator = mActionsByKey.begin();
		TActionsByKey::const_iterator lIteratorEnd = mActionsByKey.end();

		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			delete (*lIterator).second;
		}
		mActionsByKey.clear();
		mKeysByActions.clear();
	}

	void KeyboardController::Update(SDL_Event& aEvent)
	{
		InputAction *lInputAction = NULL;

		TActionsByKey::const_iterator iterator = mActionsByKey.find(TranslateKeyCode(aEvent.key.keysym.scancode));
		switch (aEvent.type)
		{
			case SDL_KEYDOWN:
				if (iterator != mActionsByKey.end()) {
					lInputAction = iterator->second;
					if (lInputAction)
						lInputAction->SetPressed(TRUE);
				}
				break;
			case SDL_KEYUP:
				if (iterator != mActionsByKey.end()) {
					lInputAction = iterator->second;
					if (lInputAction)
						lInputAction->SetPressed(FALSE);
				}
				break;
		}

	}

	void KeyboardController::RegisterInputAction(uint32 aId, uint32 aKey)
	{
		InputAction *lInputAction = new InputAction();
		lInputAction->Init(aId, aKey);
		mActionsByKey[aKey] = lInputAction;
		mKeysByActions[aId] = aKey;
	}

	BOOL KeyboardController::IsActionPressed(uint32 aActionId)
	{
		//&& state[SDL_SCANCODE_UP]
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		TKeyByAction::const_iterator iterator = mKeysByActions.find(aActionId);
		if (iterator != mKeysByActions.end())
		{
			uint32 lKey = iterator->second;
			if (state[lKey]) {
				return TRUE;
			}
		}

		return FALSE;
	}

	KeyboardController::EKeyCode KeyboardController::TranslateKeyCode(uint32 aKey)
	{
		switch (aKey)
		{
			case SDL_SCANCODE_RIGHT:
				return EKeyCode::eRight;
			case SDL_SCANCODE_LEFT:
				return EKeyCode::eLeft;
			case SDL_SCANCODE_DOWN:
				return EKeyCode::eDown;
			case SDL_SCANCODE_UP:
				return EKeyCode::eUp;
			case SDL_SCANCODE_ESCAPE:
				return EKeyCode::eEscape;
			case SDL_SCANCODE_1:
				return EKeyCode::e1;
			case SDL_SCANCODE_2:
				return EKeyCode::e2;
			case SDL_SCANCODE_3:
				return EKeyCode::e3;
			case SDL_SCANCODE_4:
				return EKeyCode::e4;
			case SDL_SCANCODE_SPACE:
				return EKeyCode::eSpace;
			case SDL_SCANCODE_LCTRL:
				return EKeyCode::eLeftControl;
			case SDL_SCANCODE_LSHIFT:
				return EKeyCode::eLeftShift;
			case SDL_SCANCODE_Q:
				return EKeyCode::eQ;
		}
		return EKeyCode::eUnknown;
	}

	BOOL KeyboardController::IsActionDown(uint32 aActionId)
	{
		TKeyByAction::const_iterator iterator = mKeysByActions.find(aActionId);
		if (iterator != mKeysByActions.end())
		{
			InputAction* lInputAction = mActionsByKey[iterator->second];
			return lInputAction->GetPressed();
		}
	}

	BOOL KeyboardController::IsActionUp(uint32 aActionId)
	{
		TKeyByAction::const_iterator iterator = mKeysByActions.find(aActionId);
		if (iterator != mKeysByActions.end())
		{
			InputAction* lInputAction = mActionsByKey[iterator->second];
			return !lInputAction->GetPressed();
		}
	}

	void KeyboardController::ClearAllActionInput()
	{
		TActionsByKey::const_iterator lIterator = mActionsByKey.begin();
		TActionsByKey::const_iterator lIteratorEnd = mActionsByKey.end();

		for (; lIterator != lIteratorEnd; ++lIterator)
		{
			delete (*lIterator).second;
		}
		mActionsByKey.clear();
		mKeysByActions.clear();
	}

} // namespace input
