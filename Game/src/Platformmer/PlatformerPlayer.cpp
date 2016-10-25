#include "PlatformerPlayer.h"
#include "PlatformGameState.h"
#include "PlatformerProjectile.h"

#include "Input/InputManager.h"

#include "Logic/World.h"

#include "System/Time.h"

#include "Core/Game.h"
#include "Core/Log.h"

#include "Graphics/RenderManager.h"
#include "Graphics/MeshComponent.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"

#include "Support/Vector3D.h"

#include "Physics/PhysicsManager.h"
#include "Physics/Collider.h"
#include "Physics/CapsuleController.h"
namespace game
{
	void PlatformerPlayer::LuaInit(float32 aX, float32 aY)
	{
		Init(TRUE, aX, aY);
	}

	void PlatformerPlayer::Init(BOOL aActive, float32 aX, float32 aY)
	{
		IGameObject::Init(aActive);

		mCapsuleController = physics::PhysicsManager::Instance()->CreateCapsuleController(Vector3D<float32>(aX, aY+1.0f, 0), 1.0f, 1.5f, 0.7f, physics::CapsuleController::eClimbingMode::eEASY, (1 << 1), (1 << 1) | (1 << 0));
		//physics::Collider* lCapsule = physics::PhysicsManager::Instance()->CreateBoxCollider(Vector3D<float32>(aX, aY, 0), Vector3D<float32>(0, 0, 0), Vector3D<float32>(0.5f, 0.5f, 0.5f), FALSE, (1 << 1), (1 << 1) | (1 << 0), physics::Collider::eKinematic, 0.1f);
		AddComponent(mCapsuleController);

		graphics::MeshComponent* lPlayerMesh = graphics::RenderManager::Instance()->LoadMeshComponentFromFile("Player");
		lPlayerMesh->GetMaterial()->SetTextureId(graphics::RenderManager::Instance()->LoadTexture("T_SnakeHead.png"));
		graphics::Material* lMaterial = graphics::RenderManager::Instance()->LoadMaterial("Test02");
		lMaterial->SetColor(&Color(0.5f, 1.0f, 0.5f, 1.0f));
		lPlayerMesh->SetMaterial(lMaterial);
		lPlayerMesh->SetRotationOffset(Vector3D<float32>(0.0f,0.0f,-90.0f));
		AddComponent(lPlayerMesh);
		mScale.mY = 2.5f;
		mJumping = FALSE;

		graphics::RenderManager::Instance()->GetRenderCamera()->FollowTarget(this, Vector3D<float32>(0.0f, 3.0f, 12.0f), Vector3D<float32>(0.0f, 0.0f, 0.0f));

		mNextShoot = 0.0f;
		mRightOrientation = TRUE;
	}

	void PlatformerPlayer::Update()
	{
		IGameObject::Update();

		Vector3D<float32> lDir;
		if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerLeft))
		{
			lDir.mX = -1;
			mRightOrientation = FALSE;
		} 
		else if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerRight))
		{
			lDir.mX = 1;
			mRightOrientation = TRUE;
		}
		
		if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerJump))
		{
			if (mCapsuleController->GetGround())
			{
				mJumping = TRUE;
				mTimeEndJump = sys::Time::GetCurrentSec() + 0.5f;
			}
		}
		if (mJumping)
		{
			if (mTimeEndJump > sys::Time::GetCurrentSec())
				mCapsuleController->AddForce(Vector3D<float32>::up * 30 * sys::Time::GetDeltaSec());
			else
				mJumping = FALSE;
		}
		mCapsuleController->Move(lDir * 20 * sys::Time::GetDeltaSec());


		if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerShoot) 
			&& mNextShoot < sys::Time::GetCurrentSec())
		{
			if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerUp))
			{
				lDir.mY = 1.0f;
			}
			else if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerDown))
			{
				lDir.mY = -1.0f;
			}
			if (lDir.Normalize().LengthSqrt() == 0.0f)
				lDir.mX = mRightOrientation ? 1.0f : -1.0f;

			//@TODO: Pool
			PlatformerProjectile* lProjectile = new PlatformerProjectile();
			logic::World::Instance()->AddGameObject(lProjectile, TRUE);
			lProjectile->Init(mPosition + lDir * 3.0f, lDir, TRUE);
			mNextShoot = sys::Time::GetCurrentSec() + 0.1f;
		}


	}

	void PlatformerPlayer::Render()
	{
		IGameObject::Render();
	}

	void PlatformerPlayer::Release()
	{
		IGameObject::Release();
	}

} // namespace game
