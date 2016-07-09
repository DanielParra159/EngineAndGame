#ifndef _INPUT_KEYBOARDCONTROLLER_H_
#define _INPUT_KEYBOARDCONTROLLER_H_

#include "Types.h"
#include "Input\IController.h"
#include "Input\InputManager.h"

#include <unordered_map>

namespace input
{
	class InputAction;
	class KeyboardController : public IController
	{
		friend class InputManager;

		typedef std::unordered_map<uint32, InputAction*> TActionsByKey; //@TODO: positive/negative
		typedef std::unordered_map<uint32, uint32> TKeyByAction;

	public:
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

		EKeyCode										TranslateKeyCode(uint32 aKey);
	public:
		virtual void									RegisterInputAction(const InputAction *aInputAction);
		virtual BOOL									IsActionPressed(uint32 aActionId);
		virtual int32									GetType() { return input::eKeyboard; }
	}; // KeyboardController
} // namespace input
#endif // _INPUT_KEYBOARDCONTROLLER_H_
