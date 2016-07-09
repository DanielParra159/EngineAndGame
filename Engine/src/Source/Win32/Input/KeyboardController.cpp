#include "Input\KeyboardController.h"
#include "Input\InputAction.h"

#include <SDL.h>

namespace input
{

	BOOL KeyboardController::Init()
	{
		return TRUE;
	}
	void KeyboardController::Release()
	{

	}

	int32 KeyboardController::Update(SDL_Event& aEvent)
	{
		int32 lResult = -1;
		InputAction *lInputAction = 0;

		switch (aEvent.type)
		{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				lInputAction = mActionsByKey[TranslateKeyCode(aEvent.key.keysym.scancode)];
				break;
		}

		if (lInputAction)
		{
			lResult = lInputAction->GetId();
		}
		return lResult;
	}

	void KeyboardController::RegisterInputAction(const InputAction *aInputAction)
	{
		InputAction *linputAction = new InputAction(*aInputAction);
		uint32 lKey = aInputAction->GetKey();
		mActionsByKey[lKey] = linputAction;
		mKeysByActions[aInputAction->GetId()] = lKey;
	}

	BOOL KeyboardController::IsActionPressed(uint32 aActionId)
	{
		//&& state[SDL_SCANCODE_UP]
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		uint32 lKey = mKeysByActions[aActionId];
		if (state[lKey]) {
			return TRUE;
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
		}
		return EKeyCode::eUnknown;
	}

} // namespace input
