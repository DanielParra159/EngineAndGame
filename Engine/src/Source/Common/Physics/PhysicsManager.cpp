#include "Physics/PhysicsManager.h"
#include "Physics/ErrorManager.h"
#include "Physics/CollisionManager.h"
#include "Physics/PhysicsConversions.h"

#include "System/Time.h"

#include "Core/Log.h"

#include <PxPhysicsAPI.h>
#include <extensions\PxExtensionsAPI.h>
#include <extensions\PxVisualDebuggerExt.h> 

#include <assert.h>

#define VECTOR_TOPXVEC3(vector) return physx::PxVec3(vector.mX, vector.mY, vector.mZ);

namespace physics
{
	SINGLETON_BODY(PhysicsManager);

	BOOL PhysicsManager::Init(float32 aGravity)
	{
		mErrorManager = new ErrorManager();

		mAllocator = new physx::PxDefaultAllocator();

		mCollisionManager = new CollisionManager();

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

		physx::PxVisualDebuggerConnectionFlags connectionFlags = physx::PxVisualDebuggerExt::getAllConnectionFlags();

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

		delete mCollisionManager;
		mCollisionManager = NULL;
	}

	void PhysicsManager::Update()
	{
		core::LogFormatString("Time: %f", sys::Time::Instance()->GetDeltaSec());
		mActiveScene->simulate(sys::Time::Instance()->GetDeltaSec());

		mActiveScene->fetchResults(TRUE);
	}

	physx::PxFilterFlags PhysicsManager::FilterShader(
		uint32 aAttributes0, physx::PxFilterData aFilterData0,
		uint32 aAttributes1, physx::PxFilterData aFilterData1,
		physx::PxPairFlags& aPairFlags, const void* aConstantBlock, uint32 aConstantBlockSize)
	{
		// let triggers through
		if (physx::PxFilterObjectIsTrigger(aAttributes0) || physx::PxFilterObjectIsTrigger(aAttributes1))
		{
			aPairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
			return physx::PxFilterFlag::eDEFAULT;
		}
		// generate contacts for all that were not filtered above
		//pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;

		// trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if ((aFilterData0.word0 & aFilterData1.word1) && (aFilterData1.word0 & aFilterData0.word1))
		{
			aPairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;
			aPairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
		}

		return physx::PxFilterFlag::eDEFAULT;
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
			sceneDesc.filterShader = FilterShader;
			//sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

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

	

	Collider* PhysicsManager::CreateBoxCollider(const Vector3D<float32> &aPosition, const Vector3D<float32> &aPositionOffset, const Vector3D<float32> &aDimensions,
																	  BOOL aTrigger, uint32 aLayerMask, uint32 aCollisionMask, Collider::eColliderType aColliderType, float32 aMass)
	{
		assert(mActiveScene && "mActiveScene NULL");

		physx::PxTransform lPosition(EXPOSE_VECTOR3D(aPosition));
		physx::PxBoxGeometry lGeometry(EXPOSE_VECTOR3D(aDimensions));
		physx::PxMaterial *lMaterial = mDefaultMaterial;
		physx::PxTransform lOffset(EXPOSE_VECTOR3D(aPositionOffset));

		physx::PxRigidActor* lActor = NULL;

		if (aColliderType != Collider::eStatic)
		{
			float32 lDensity = aMass / (aDimensions.mX * aDimensions.mY * aDimensions.mZ);

			if (aColliderType == Collider::eKinematic)
				lActor = PxCreateKinematic(*mPhysics, lPosition, lGeometry, *lMaterial, lDensity, lOffset);
			else
				lActor = PxCreateDynamic(*mPhysics, lPosition, lGeometry, *lMaterial, lDensity, lOffset); 
		}
		else {
			lActor = physx::PxCreateStatic(*mPhysics, lPosition, lGeometry, *lMaterial, lOffset);
		}
		
		if (aTrigger) {
			physx::PxShape *lShape;
			lActor->getShapes(&lShape, 1, 0);
			lShape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
			lShape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
		}
	
		const physx::PxU32 numShapes = lActor->getNbShapes();
		physx::PxShape** shapes = new physx::PxShape*[numShapes];
		lActor->getShapes(shapes, numShapes);
		for (physx::PxU32 i = 0; i < numShapes; i++)
		{
			physx::PxShape* shape = shapes[i];
			physx::PxFilterData filterData;
			filterData.word0 = aLayerMask; // word0 = own ID
			filterData.word1 = aCollisionMask;	// word1 = ID mask to filter pairs that trigger a contact callback;
			shape->setSimulationFilterData(filterData);
		}
		delete [] shapes;

		Collider* lCollider = new Collider();
		lCollider->Init(TRUE, lActor, aColliderType, aTrigger);
		lActor->userData = (void *)lCollider;

		//physx::PxSetGroup(*lActor, aGroup);

		mActiveScene->addActor(*lActor);

		return lCollider;
	}

	Collider* PhysicsManager::CreatePlaneCollider(const Vector3D<float32> &aPosition, const Vector3D<float32> &aNormal, uint32 aLayerMask, uint32 aCollisionMask)
	{
		assert(mActiveScene);

		// Crear un plano estático
		physx::PxPlane lPlane(Vector3DToPxVec3(aPosition), Vector3DToPxVec3(aNormal));
		physx::PxMaterial *lMaterial = mDefaultMaterial;
		physx::PxRigidStatic *lActor = physx::PxCreatePlane(*mPhysics, lPlane, *lMaterial);

		Collider* lCollider = new Collider();
		lCollider->Init(TRUE, lActor, Collider::eStatic, FALSE);
		lActor->userData = (void *)lCollider;

		//physx::PxSetGroup(*lActor, aGroup);
		const physx::PxU32 numShapes = lActor->getNbShapes();
		physx::PxShape** shapes = new physx::PxShape*[numShapes];
		lActor->getShapes(shapes, numShapes);
		for (physx::PxU32 i = 0; i < numShapes; i++)
		{
			physx::PxShape* shape = shapes[i];
			physx::PxFilterData filterData;
			filterData.word0 = aLayerMask; // word0 = own ID
			filterData.word1 = aCollisionMask;	// word1 = ID mask to filter pairs that trigger a contact callback;
			shape->setSimulationFilterData(filterData);
		}
		delete[] shapes;

		mActiveScene->addActor(*lActor);

		return lCollider;
	}

	CapsuleController* PhysicsManager::CreateCapsuleController(const Vector3D<float32> &aCenter, float32 aRadius, float32 aHeight, float32 aSlopeLimit, CapsuleController::eClimbingMode aClimbingMode, uint32 aLayerMask, uint32 aCollisionMask)
	{
		float32 lOffsetY = aHeight / 2.0f + aRadius;

		physx::PxCapsuleControllerDesc desc;
		desc.position = physx::PxExtendedVec3(EXPOSE_VECTOR3D(aCenter));
		desc.height = aHeight;
		desc.radius = aRadius;
		desc.material = mDefaultMaterial;
		desc.climbingMode = (physx::PxCapsuleClimbingMode::Enum)aClimbingMode;
		desc.slopeLimit = aSlopeLimit;
		desc.reportCallback = mCollisionManager;

		CapsuleController* lCapsuleController = new CapsuleController();
		lCapsuleController->Init(TRUE, NULL, Collider::eKinematic, FALSE);

		desc.userData = (void *)lCapsuleController;

		physx::PxCapsuleController *controller = (physx::PxCapsuleController *)mControllerManager->createController(desc);

		physx::PxRigidDynamic* lActor = controller->getActor();
		const physx::PxU32 numShapes = lActor->getNbShapes();
		physx::PxShape** shapes = new physx::PxShape*[numShapes];
		lActor->getShapes(shapes, numShapes);
		for (physx::PxU32 i = 0; i < numShapes; i++)
		{
			physx::PxShape* shape = shapes[i];
			physx::PxFilterData filterData;
			filterData.word0 = aLayerMask; // word0 = own ID
			filterData.word1 = aCollisionMask;	// word1 = ID mask to filter pairs that trigger a contact callback;
			shape->setSimulationFilterData(filterData);
		}
		delete[] shapes;

		lActor->userData = (void *)lCapsuleController;
		lCapsuleController->SetPhysicCampsuleController(controller);

		return lCapsuleController;
	}

} // namespace physics
