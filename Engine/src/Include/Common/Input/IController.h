#ifndef _INPUT_ICONTROL_H_
#define _INPUT_ICONTROL_H_

#include "Types.h"

union SDL_Event;

namespace input
{
	class InputAction;
	class IController
	{
		friend class InputManager;
	private:
		virtual BOOL									Init() = 0;
		virtual void									Release() = 0;

		virtual int32									Update(SDL_Event& aEvent) = 0;

	public:
		virtual void									RegisterInputAction(const InputAction *aInputAction) = 0;
		virtual BOOL									IsActionPressed(uint32 aActionId) = 0;
		virtual int32									GetType() = 0;
	}; // IControl
} // namespace input
#endif // _INPUT_ICONTROL_H_
