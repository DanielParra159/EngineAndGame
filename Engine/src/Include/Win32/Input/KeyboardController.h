#ifndef _INPUT_KEYBOARDCONTROLLER_H_
#define _INPUT_KEYBOARDCONTROLLER_H_

#include "Types.h"
#include "Input\IController.h"
#include "Input\InputManager.h"

#include <unordered_map>

namespace input
{
	class InputAction;
	/**
	Implements a keyboard controller
	@see input::IController
	*/
	class KeyboardController : public IController
	{
		friend class InputManager;

		typedef std::unordered_map<uint32, InputAction*> TActionsByKey; //@TODO: positive/negative
		typedef std::unordered_map<uint32, uint32> TKeyByAction;

	public:
		/**
		Recognizing keys
		*/
		enum EKeyCode
		{
			eUnknown = -1,

			eUp, eDown, eLeft, eRight,

			eEscape
		};


	private:
		TActionsByKey									mActionsByKey;
		TKeyByAction									mKeysByActions;
	private:
		KeyboardController() : mActionsByKey(4), mKeysByActions(4) {}
		~KeyboardController() {}

		virtual BOOL									Init();
		virtual void									Release();

		virtual int32									Update(SDL_Event& aEvent);

		/**
		Translate SDL key to interneal key
		*/
		EKeyCode										TranslateKeyCode(uint32 aKey);
	public:
		/**
		Register an input action associating key and action id
		@param aInputActio, an the action
		*/
		virtual void									RegisterInputAction(const InputAction *aInputAction);
		/**
		Check if is pressed the key associated with an action
		@param aActionId, action id to check
		@return TRUE if is pressed FALSE in other case
		*/
		virtual BOOL									IsActionPressed(uint32 aActionId);
		/**
		Gets the type of controller
		@return The type of controller (input::eKeyboard)
		*/
		virtual input::ETypeControls					GetType() { return input::eKeyboard; }
	}; // KeyboardController
} // namespace input
#endif // _INPUT_KEYBOARDCONTROLLER_H_
