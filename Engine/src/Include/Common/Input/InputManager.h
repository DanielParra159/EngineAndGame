#ifndef _ENGINE_INPUT_INPUTMANAGER_H_
#define _ENGINE_INPUT_INPUTMANAGER_H_

#include "Defs.h"
#include "Types.h"

#include <vector>
namespace input
{
	/**
	Types of controls
	*/
	enum ETypeControls
	{
		eKeyboard,
		eMouse
	};

	class IController;
	class InputAction;

	/**
	The InputManager is in charge of manage everything related to the input and create the controllers
	*/
	class InputManager
	{
		typedef std::vector<IController*>				TControllers;
		SINGLETON_HEAD(InputManager);
	private:
		/**
		All the controllers
		*/
		TControllers									mControllers;
		/**
		Last action pressed, this is reset each
		*/
		int32											mLastAction;

	public:
		BOOL											Init();
		void 											Release();

		void											Update();

		/**
		Create and initializes a controller
		@param aType, controller type
		@return the controller created or null
		*/
		IController*									CreateController(ETypeControls aType);
		/**
		Gets a controller by type
		@param aType, controller type
		@return the controller
		*/
		IController*									GetController(ETypeControls aType);
		/**
		Gets the last action id pressed, this is reset each
		@return the last action id or -1
		*/
		int32											GetLastActionId() { return mLastAction; }
	private:
		InputManager() : mControllers(0), mLastAction(-1) {}
		~InputManager() {}

	}; // InputManager
} // namespace input
#endif // _ENGINE_INPUT_INPUTMANAGER_H_
