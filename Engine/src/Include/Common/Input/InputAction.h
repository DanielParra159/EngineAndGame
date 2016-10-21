#ifndef _INPUT_ACTION_H_
#define _INPUT_ACTION_H_

#include "Types.h"

namespace input
{
	/**
	Defines an action associating key with action id
	*/
	class InputAction
	{
		friend class KeyboadController;
		friend class MouseController;
	private:
		uint32											mId;
		uint32											mKey;
		BOOL											mPressed;
		
	public:
		InputAction() : mPressed(FALSE) {}
		~InputAction() {}

		void											Init(uint32 aId, uint32 aKey) { mId = aId; mKey = aKey; mPressed = FALSE; }

		/**
		Gets the action id
		@return the action id
		*/
		uint32											GetId() const { return mId; }
		/**
		Gets the key
		@return the key
		*/
		uint32											GetKey() const { return mKey; }
		/**
		Sets the action id
		@param aId, action id
		*/
		void											SetId(uint32 aId) { mId = aId; }
		/**
		Sets the key
		@param aKey, key
		*/
		void											SetKey(uint32 aKey) { mKey = aKey; }
		BOOL											GetPressed() { return mPressed; }
		void											SetPressed(BOOL aPressed) { mPressed = aPressed; }

	}; // InputAction
} // namespace input
#endif // _INPUT_ACTION_H_
