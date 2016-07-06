#ifndef _INPUT_ACTION_H_
#define _INPUT_ACTION_H_

#include "Types.h"

namespace input
{
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

		uint32											GetId() const { return mId; }
		uint32											GetKey() const { return mKey; }
		void											SetId(uint32 aId) { mId = aId; }
		void											SetKey(uint32 aKey) { mKey = aKey;}

	}; // InputAction
} // namespace input
#endif // _INPUT_ACTION_H_
