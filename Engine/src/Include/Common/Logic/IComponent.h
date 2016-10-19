#ifndef _ENGINE_LOGIC_ICOMPONENT_H_
#define _ENGINE_LOGIC_ICOMPONENT_H_

#include "Types.h"
#include "Support/Vector3D.h"

namespace logic
{
	/**
	
	*/
	class IComponent {
		friend class IGameObject;
	protected:
		BOOL											mActive;
	protected:
		virtual void									Init(BOOL aActive);
		virtual void									Release() = 0;
		virtual void									Update() {};
		virtual void									SetPosition(const Vector3D<float32> aPosition) {};
		IComponent() : mActive(FALSE) {}
		virtual ~IComponent() {}
	public:

		virtual void									SetEnabled(BOOL aActive);
		virtual BOOL									GetEnabled() { return mActive;	}

	}; // IComponent
} // namespace logic
#endif // _ENGINE_LOGIC_ICOMPONENT_H_
