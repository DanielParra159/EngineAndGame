#include "Physics/PhysicsManager.h"
#include "Physics/ErrorManager.h"
#include "Physics/CollisionManager.h"

#include <PxPhysicsAPI.h>
#include <extensions\PxExtensionsAPI.h>
#include <extensions\PxVisualDebuggerExt.h> 

#include <assert.h>

namespace physics
{
	SINGLETON_BODY(PhysicsManager);

	BOOL PhysicsManager::Init(float32 aGravity)
	{
		mErrorManager = new ErrorManager();

		mAllocator = new physx::PxDefaultAllocator();

		mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, *mAllocator, *mErrorManager);
		assert(mFoundation && "PxCreateFoundation failed");

		mProfileZoneManager = &physx::PxProfileZoneManager::createProfileZoneManager(mFoundation);
		assert(mProfileZoneManager && "PxProfileZoneManager::createProfileZoneManage failed");

		physx::PxTolerancesScale lToleranceScale;
		bool lRecordMemoryAllocations = true;
		mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, lToleranceScale, lRecordMemoryAllocations, mProfileZoneManager);
		assert(mPhysics && "PxCreatePhysics failed");

		mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, physx::PxCookingParams(lToleranceScale));
		assert(mCooking && "PxCreatePhysics failed");

		if (!PxInitExtensions(*mPhysics))
			assert(FALSE && "PxInitExtensions failed");

		mDefaultMaterial = CreateMaterial(0.5f, 0.5f, 0.1f);
		assert(mDefaultMaterial && "CreateMaterial failed");

		//PhysX Visual Debugger (PVD)
		mPvdConnection = NULL;

#ifdef _DEBUG
		physx::debugger::comm::PvdConnectionManager *mPvdConnectionManager = mPhysics->getPvdConnectionManager();
		assert(mPvdConnectionManager && "PxPhysics::getPvdConnectionManager failed");

		const int8* lIp = "127.0.0.1";
		int32 lPort = 5425;
		uint32 lTimeout = 100;

		// Configurar qué información queremos mandar al PVD (debug, profile, memory)
		physx::PxVisualDebuggerConnectionFlags connectionFlags = physx::PxVisualDebuggerExt::getAllConnectionFlags();

		// Intentar establecer la conexión
		mPvdConnection = physx::PxVisualDebuggerExt::createConnection(mPvdConnectionManager, lIp, lPort, lTimeout, connectionFlags);
#endif

		CreateScene(aGravity);

		return TRUE;
	}

	void PhysicsManager::Release()
	{
		if (mPvdConnection) {
			mPvdConnection->release();
			mPvdConnection = NULL;
		}
		
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

	void PhysicsManager::CreateScene(float32 aGravity)
	{
		physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());

		sceneDesc.gravity = physx::PxVec3(0.0f, aGravity, 0.0f);

		sceneDesc.simulationEventCallback = mCollisionManager;

		if (!sceneDesc.cpuDispatcher) {
			int lThreads = 1; 
			mCpuDispatcher = physx::PxDefaultCpuDispatcherCreate(lThreads);
			assert(mCpuDispatcher && "PxDefaultCpuDispatcherCreate failed");

			sceneDesc.cpuDispatcher = mCpuDispatcher;
		}

		if (!sceneDesc.filterShader)
			sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

		// Crear la escena física
		mActiveScene = mPhysics->createScene(sceneDesc);
		assert(mActiveScene && "PxPhysics::createScene failed");

		mControllerManager = PxCreateControllerManager(*mActiveScene);
		assert(mControllerManager && "PxCreateControllerManager failed");
	}

	PhysicsMaterial* PhysicsManager::CreateMaterial(float32 aStaticFriction, float32 aDynamicFriction, float32 aRestitution)
	{
		//@TODO: add to list to release later or user must release it?
		return mPhysics->createMaterial(aStaticFriction, aDynamicFriction, aRestitution);
	}

} // namespace physics
