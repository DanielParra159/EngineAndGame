#ifndef _INPUT_MOUSECONTROLLER_H_
#define _INPUT_MOUSECONTROLLER_H_

#include "Types.h"
#include "Support\Vector2D.h"
#include "Input\IController.h"
#include "Input\InputManager.h"

#include <unordered_map>

namespace input
{
	class InputAction;
	/**
	Implements a mouse controller
	@see input::IController
	*/
	class MouseController : public IController
	{
		friend class InputManager;

		typedef std::unordered_map<uint32, InputAction*> TActionsByKey;
		typedef std::unordered_map<uint32, uint32> TKeyByAction;

	public:
		/**
		Recognizing buttons
		*/
		enum EButtonCode
		{
			eUnknown = -1,

			eLeftButton, eMiddleButton, eRightButton,
		};


	private:
		TActionsByKey									mActionsByKey;
		TKeyByAction									mKeysByActions;
	private:
		MouseController() : mActionsByKey(4), mKeysByActions(4) {}
		~MouseController() {}

		virtual BOOL									Init();
		virtual void									Release();

		virtual void									Update(SDL_Event& aEvent);

		/**
		Translate SDL key to interneal button
		*/
		EButtonCode										TranslateButtonCode(uint32 aKey);

		virtual BOOL									IsActionDown(uint32 aActionId);
		virtual BOOL									IsActionUp(uint32 aActionId);
	public:
		/**
		Register an input action associating key and action id
		@param aInputActio, an the action
		*/
		virtual void									RegisterInputAction(uint32 aId, uint32 aKey);
		/**
		Check if is pressed the button associated with an action
		@param aActionId, action id to check
		@return TRUE if is pressed FALSE in other case
		*/
		virtual BOOL									IsActionPressed(uint32 aActionId);
		/**
		Check if is pressed the button
		@param aButton, button to check
		@return TRUE if is pressed FALSE in other case
		*/
		BOOL											IsButtonPressed(EButtonCode aButton);

		void											GetMousePos(Vector2D<int32>& aMousePos);
		/**
		Gets the type of controller
		@return The type of controller (input::eMouse)
		*/
		virtual input::ETypeControls					GetType() { return input::eMouse; }
	}; // MouseController
} // namespace input
#endif // _INPUT_MOUSECONTROLLER_H_
