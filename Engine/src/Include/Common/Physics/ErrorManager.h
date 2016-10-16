#ifndef _ENGINE_PHYSICS_ERRORMANAGER_H_
#define _ENGINE_PHYSICS_ERRORMANAGER_H_

#include "Types.h"

#include <foundation/PxErrorCallback.h>


namespace physics
{
	/**
	PhysX error callback, PhysX invoke reportError if an error ocurrs.
	*/
	class ErrorManager : public physx::PxErrorCallback
	{
	public:
		ErrorManager() : physx::PxErrorCallback() {}
		virtual ~ErrorManager() {}

		/**
		* Method invoked by PhysX each time an error ocurrs. Print the error message on screen.
		@param aErrorCode,
		@param aMessage,
		@param aFile,
		@param aLine,
		*/
		void reportError(physx::PxErrorCode::Enum aErrorCode, const int8* aMessage, const int8* aFile, int32 aLine);
	}; // ErrorManager

}; // namespace physics

#endif // _ENGINE_PHYSICS_ERRORMANAGER_H_