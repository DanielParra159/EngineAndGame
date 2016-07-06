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
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					if (SDL_SCANCODE_UP == event.key.keysym.scancode)
					{

					}
					break;
				default:
					break;
			}
		}
		return lResult;
	}

	void KeyboardController::RegisterInputAction(const InputAction *inputAction)
	{
		InputAction *linputAction = new InputAction(*inputAction);
		mActionsByKey[inputAction->GetKey()] = linputAction;
	}

} // namespace input
