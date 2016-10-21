#include "Input\MouseController.h"
#include "Input\InputAction.h"

#include "SDL.h"

#include <assert.h>

namespace input
{

	BOOL MouseController::Init()
	{
		return TRUE;
	}
	void MouseController::Release()
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

	void MouseController::Update(SDL_Event& aEvent)
	{
		InputAction *lInputAction = NULL;

		switch (aEvent.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				lInputAction = mActionsByKey[TranslateButtonCode(aEvent.button.button)];
				if (lInputAction)
					lInputAction->SetPressed(TRUE);
				break;
			case SDL_MOUSEBUTTONUP:
				lInputAction = mActionsByKey[TranslateButtonCode(aEvent.button.button)];
				if (lInputAction)
					lInputAction->SetPressed(FALSE);
				break;
		}
	}

	void MouseController::RegisterInputAction(uint32 aId, uint32 aKey)
	{
		InputAction *lInputAction = new InputAction();
		mActionsByKey[aKey] = lInputAction;
		mKeysByActions[aId] = aKey;
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

	BOOL MouseController::IsActionDown(uint32 aActionId)
	{
		InputAction* lInputAction = mActionsByKey[mKeysByActions[aActionId]];
		if (lInputAction != NULL)
			return lInputAction->GetPressed();
		else
			return FALSE;
	}

	BOOL MouseController::IsActionUp(uint32 aActionId)
	{
		InputAction* lInputAction = mActionsByKey[mKeysByActions[aActionId]];
		if (lInputAction != NULL)
			return !lInputAction->GetPressed();
		else
			return FALSE;
	}

	void MouseController::ClearAllActionInput()
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
