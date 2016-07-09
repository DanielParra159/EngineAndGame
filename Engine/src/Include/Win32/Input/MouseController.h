#ifndef _INPUT_MOUSECONTROLLER_H_
#define _INPUT_MOUSECONTROLLER_H_

#include "Types.h"
#include "Types\Vector2D.h"
#include "Input\IController.h"
#include "Input\InputManager.h"

#include <unordered_map>

namespace input
{
	class InputAction;
	class MouseController : public IController
	{
		friend class InputManager;

		typedef std::unordered_map<uint32, InputAction*> TActionsByKey;
		typedef std::unordered_map<uint32, uint32> TKeyByAction;

	public:
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

		virtual int32									Update(SDL_Event& aEvent);

		EButtonCode										TranslateButtonCode(uint32 aKey);
	public:
		virtual void									RegisterInputAction(const InputAction *aInputAction);
		virtual BOOL									IsActionPressed(uint32 aActionId);
		BOOL											IsButtonPressed(EButtonCode aButton);

		void											GetMousePos(Vector2D<int32>& aMousePos);
		virtual int32									GetType() { return input::eMouse; }
	}; // MouseController
} // namespace input
#endif // _INPUT_MOUSECONTROLLER_H_
