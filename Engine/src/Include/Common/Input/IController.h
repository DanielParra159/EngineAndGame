#ifndef _INPUT_ICONTROL_H_
#define _INPUT_ICONTROL_H_

#include "Types.h"

namespace input
{
	class InputAction;
	class IController
	{
		friend class InputManager;
	private:
		virtual BOOL									Init() = 0;
		virtual void									Release() = 0;

		virtual int32									Update() = 0;

	public:
		virtual void									RegisterInputAction(const InputAction *inputAction) = 0;
	}; // IControl
} // namespace input
#endif // _INPUT_ICONTROL_H_
