#ifndef _ENGINE_PHYSICS_ERRORMANAGER_H_
#define _ENGINE_PHYSICS_ERRORMANAGER_H_

#include "Types.h"

#include <foundation/PxErrorCallback.h>


namespace physics
{
	class ErrorManager : public physx::PxErrorCallback
	{
	public:
		ErrorManager() : physx::PxErrorCallback() {}
		virtual ~ErrorManager() {}

		/**
		* Método invocado por PhysX cada vez que se produce un error. El mensaje de error se
		* imprime por pantalla.
		*/
		void reportError(physx::PxErrorCode::Enum aErrorCode, const int8* aMessage, const int8* aFile, int32 aLine);
	}; // ErrorManager

}; // namespace physics

#endif // _ENGINE_PHYSICS_ERRORMANAGER_H_