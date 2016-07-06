#ifndef _INPUT_INPUTMANAGER_H_
#define _INPUT_INPUTMANAGER_H_

#include "Types.h"

#include <vector>

namespace input
{
	enum eTypeControls
	{
		Keyboard,
		Mouse
	};

	class IController;
	class InputAction;

	class InputManager
	{
		typedef std::vector<IController*>				TControllers;
	private:
		static InputManager*							sInstance;

		TControllers									mControllers;
		int32											mLastAction;

	public:
		static InputManager*							Instance();
		BOOL											Init();
		void 											Release();

		void											Update();

		IController*									CreateController(eTypeControls aType);
		int32											PullActionId();
		int32											GetActionId();
	private:
		InputManager() : mControllers(1), mLastAction(-1) {}
		~InputManager() {}

	}; // InputManager
} // namespace input
#endif // _INPUT_INPUTMANAGER_H_
