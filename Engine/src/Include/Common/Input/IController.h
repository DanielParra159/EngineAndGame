#ifndef _INPUT_ICONTROL_H_
#define _INPUT_ICONTROL_H_

#include "Types.h"

union SDL_Event;

namespace input
{
	enum ETypeControls;
	class InputAction;
	/**
	Pure abstract class that defines a controller behavior
	*/
	class IController
	{
		friend class InputManager;
	private:
		virtual BOOL									Init() = 0;
		virtual void									Release() = 0;

		virtual void									Update(SDL_Event& aEvent) = 0;

		virtual BOOL									IsActionDown(uint32 aActionId) = 0;
		virtual BOOL									IsActionUp(uint32 aActionId) = 0;
	public:
		/**
		Register an input action associating key and action id
		@param aInputActio, an the action
		*/
		virtual void									RegisterInputAction(uint32 aId, uint32 aKey) = 0;
		/**
		Check if is pressed the button associated with an action
		@param aActionId, action id to check
		@return TRUE if is pressed FALSE in other case
		*/
		virtual BOOL									IsActionPressed(uint32 aActionId) = 0;
		/**
		Gets the type of controller
		@return The type of controller
		@see input::ETypeControls
		*/
		virtual input::ETypeControls					GetType() = 0;
	}; // IControl
} // namespace input
#endif // _INPUT_ICONTROL_H_
