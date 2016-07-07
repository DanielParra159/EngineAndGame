#ifndef _INPUT_CONTROLKEYBOARD_H_
#define _INPUT_CONTROLKEYBOARD_H_

#include "Types.h"
#include "Input\IController.h"

#include <unordered_map>

namespace input
{
	class InputAction;
	class KeyboardController : public IController
	{
		friend class InputManager;

		typedef std::unordered_map<uint32, InputAction*> TActionsByKey; //@TODO: positive/negative

	public:
		enum EKeyCode
		{
			eUnknown = -1,

			eUp, eDown, eLeft, eRight,

			eEscape
		};


	private:
		TActionsByKey									mActionsByKey;
	private:
		KeyboardController() : mActionsByKey(4) {}
		~KeyboardController() {}

		virtual BOOL									Init();
		virtual void									Release();

		virtual int32									Update();

		EKeyCode										TranslateKeyCode(uint32 aKey);
	public:
		virtual void									RegisterInputAction(const InputAction *inputAction);
	}; // ControlKeyboard
} // namespace input
#endif // _INPUT_CONTROLKEYBOARD_H_
