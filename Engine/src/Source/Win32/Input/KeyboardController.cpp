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

	int32 KeyboardController::Update()
	{
		SDL_Event event;
		int32 lResult = -1;
		InputAction *lInputAction = 0;
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					lInputAction = mActionsByKey[TranslateKeyCode(event.key.keysym.scancode)];
					break;
			}
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
		mActionsByKey[aInputAction->GetKey()] = linputAction;
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
