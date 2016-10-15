#include "Physics\ErrorManager.h"
#include "Core\Log.h"

#include <string>

namespace physics
{
	//---------------------------------------------------------

	void ErrorManager::reportError(physx::PxErrorCode::Enum aErrorCode, const int8* aMessage, const int8* aFile, int32 aLine)
	{
		std::string aCodeStr;

		switch (aErrorCode) {
			case physx::PxErrorCode::eNO_ERROR: aCodeStr = "NO_ERROR"; break;
			case physx::PxErrorCode::eDEBUG_INFO: aCodeStr = "DEBUG_INFO"; break;
			case physx::PxErrorCode::eDEBUG_WARNING: aCodeStr = "DEBUG_WARNING"; break;
			case physx::PxErrorCode::eINVALID_PARAMETER: aCodeStr = "INVALID_PARAMETER"; break;
			case physx::PxErrorCode::eINVALID_OPERATION: aCodeStr = "INVALID_OPERATION"; break;
			case physx::PxErrorCode::eOUT_OF_MEMORY: aCodeStr = "OUT_OF_MEMORY"; break;
			case physx::PxErrorCode::eINTERNAL_ERROR: aCodeStr = "INTERNAL_ERROR"; break;
			case physx::PxErrorCode::eABORT: aCodeStr = "ABORT"; break;
			case physx::PxErrorCode::ePERF_WARNING: aCodeStr = "PERF_WARNING"; break;
		}

		core::LogFormatString("PhysX error: File: %s, Line: %d, Code: %s, Message: %s\n", aFile, aLine, aCodeStr, aMessage);
	}

}