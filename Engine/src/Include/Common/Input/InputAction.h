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
	private:
		uint32											mId;
		uint32											mKey; //@TODO: positive/negative
	public:
		InputAction() {}
		InputAction(const InputAction& aInputAction) : mId(aInputAction.mId), mKey(aInputAction.mKey) {}
		~InputAction() {}

		void											Init(uint32 aId, uint32 aKey) { mId = aId; mKey = aKey; }

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
		void											SetKey(uint32 aKey) { mKey = aKey;}

	}; // InputAction
} // namespace input
#endif // _INPUT_ACTION_H_
