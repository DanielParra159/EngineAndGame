#ifndef _ENGINE_INPUT_INPUTMANAGER_H_
#define _ENGINE_INPUT_INPUTMANAGER_H_

#include "Defs.h"
#include "Types.h"

#include <vector>

namespace core
{
	class Game;
}

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
		friend class core::Game;
		typedef std::vector<IController*>				TControllers;
		SINGLETON_HEAD(InputManager);
	private:
		/**
		All the controllers
		*/
		TControllers									mControllers;

	public:
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

		BOOL											IsActionDown(uint32 aActionId);
		BOOL											IsActionUp(uint32 aActionId);
		void											ClearAllActionInput();
	private:
		InputManager() : mControllers(0) {}
		~InputManager() {}

		BOOL											Init();
		void 											Release();

		void											Update();

	}; // InputManager
} // namespace input
#endif // _ENGINE_INPUT_INPUTMANAGER_H_
