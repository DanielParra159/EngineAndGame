#ifndef _ENGINE_LOGIC_ICOMPONENT_H_
#define _ENGINE_LOGIC_ICOMPONENT_H_

#include "Types.h"

namespace logic
{
	/**
	
	*/
	class IComponent {
	protected:
		BOOL											mActive;
	protected:
		virtual void									Init(BOOL aActive);
		virtual void									Release() = 0;
		IComponent() : mActive(FALSE) {}
		virtual ~IComponent() {}
	public:

		virtual void									SetEnabled(BOOL aActive);
		virtual BOOL									GetEnabled() { return mActive;	}

	}; // IComponent
} // namespace logic
#endif // _ENGINE_LOGIC_ICOMPONENT_H_
