#include "Physics/PhysicsManager.h"
#include "Physics/ErrorManager.h"

#include <PxPhysicsAPI.h>
#include <extensions\PxExtensionsAPI.h>
#include <extensions\PxVisualDebuggerExt.h> 

#include <assert.h>

namespace physics
{
	SINGLETON_BODY(PhysicsManager);

	BOOL PhysicsManager::Init()
	{

		mErrorManager = new ErrorManager();

		mAllocator = new physx::PxDefaultAllocator();

		mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, *mAllocator, *mErrorManager);

		mProfileZoneManager = &physx::PxProfileZoneManager::createProfileZoneManager(mFoundation);
		assert(mProfileZoneManager && "Error en PxProfileZoneManager::createProfileZoneManage");

		physx::PxTolerancesScale lToleranceScale;
		bool lRecordMemoryAllocations = true;
		mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, lToleranceScale, lRecordMemoryAllocations, mProfileZoneManager);

		mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, physx::PxCookingParams(lToleranceScale));

		if (!PxInitExtensions(*mPhysics))
			assert(FALSE && "PxInitExtensions failed");

		float32 staticFriction = 0.5f;
		float32 dynamicFriction = 0.5f;
		float32 restitution = 0.1f;
		mDefaultMaterial = mPhysics->createMaterial(staticFriction, dynamicFriction, restitution);

		//PhysX Visual Debugger (PVD)
		mPvdConnection = NULL;

#ifdef _DEBUG
		physx::debugger::comm::PvdConnectionManager *mPvdConnectionManager = mPhysics->getPvdConnectionManager();
		assert(mPvdConnectionManager && "Error en PxPhysics::getPvdConnectionManager");

		const int8* lIp = "127.0.0.1";
		int32 lPort = 5425;
		uint32 lTimeout = 100;

		// Configurar qué información queremos mandar al PVD (debug, profile, memory)
		physx::PxVisualDebuggerConnectionFlags connectionFlags = physx::PxVisualDebuggerExt::getAllConnectionFlags();

		// Intentar establecer la conexión
		mPvdConnection = physx::PxVisualDebuggerExt::createConnection(mPvdConnectionManager, lIp, lPort, lTimeout, connectionFlags);
#endif

		return TRUE;
	}

	void PhysicsManager::Release()
	{
		mPvdConnection->release();
		mPvdConnection = NULL;
		
		mDefaultMaterial->release();
		mDefaultMaterial = NULL;

		mCooking->release();
		mCooking = NULL;

		mPhysics->release();
		mPhysics = NULL;

		mProfileZoneManager->release();
		mProfileZoneManager = NULL;

		PxCloseExtensions();

		mFoundation->release();
		mFoundation = NULL;

		delete mAllocator;
		mAllocator = NULL;

		delete mErrorManager;
		mErrorManager = NULL;
	}

	void PhysicsManager::Update()
	{

	}


} // namespace physics
