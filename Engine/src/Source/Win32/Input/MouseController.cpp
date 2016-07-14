#include "Input\MouseController.h"
#include "Input\InputAction.h"

#include "SDL.h"

namespace input
{

	BOOL MouseController::Init()
	{
		return TRUE;
	}
	void MouseController::Release()
	{

	}

	int32 MouseController::Update(SDL_Event& aEvent)
	{
		int32 lResult = -1;
		InputAction *lInputAction = 0;

		switch (aEvent.type)
		{
			//case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				lInputAction = mActionsByKey[TranslateButtonCode(aEvent.button.button)];
				break;
		}

		if (lInputAction)
		{
			lResult = lInputAction->GetId();
		}
		return lResult;
	}

	void MouseController::RegisterInputAction(const InputAction *aInputAction)
	{
		InputAction *linputAction = new InputAction(*aInputAction);
		uint32 lButton = aInputAction->GetKey();
		mActionsByKey[lButton] = linputAction;
		mKeysByActions[aInputAction->GetId()] = lButton;
	}

	BOOL MouseController::IsActionPressed(uint32 aActionId)
	{
		SDL_PumpEvents();
		uint32 lButton = mKeysByActions[aActionId];
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(lButton)) {
			return TRUE;
		}
		return FALSE;
	}

	BOOL MouseController::IsButtonPressed(EButtonCode aButton)
	{
		SDL_PumpEvents();

		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			return TRUE;
		}
		return FALSE;
	}

	void MouseController::GetMousePos(Vector2D<int32>& aMousePos)
	{
		SDL_GetMouseState(&aMousePos.mX, &aMousePos.mY);
	}

	MouseController::EButtonCode MouseController::TranslateButtonCode(uint32 aKey)
	{
		switch (aKey)
		{
			case SDL_BUTTON_LEFT:
				return EButtonCode::eLeftButton;
			case SDL_BUTTON_MIDDLE:
				return EButtonCode::eMiddleButton;
			case SDL_BUTTON_RIGHT:
				return EButtonCode::eRightButton;
		}
		return EButtonCode::eUnknown;
	}

} // namespace input
