#include "PlatformmerPlayer.h"
#include "PlatformGameState.h"

#include "Input/InputManager.h"

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
	void PlatformmerPlayer::LuaInit(float32 aX, float32 aY)
	{
		Init(TRUE, aX, aY);
	}

	void PlatformmerPlayer::Init(BOOL aActive, float32 aX, float32 aY)
	{
		IGameObject::Init(aActive);

		mCapsuleController = physics::PhysicsManager::Instance()->CreateCapsuleController(Vector3D<float32>(aX, aY+1.0f, 0), 1.0f, 1.5f, 0.7f, physics::CapsuleController::eClimbingMode::eEASY, (1 << 1), (1 << 1) | (1 << 0));
		//physics::Collider* lCapsule = physics::PhysicsManager::Instance()->CreateBoxCollider(Vector3D<float32>(aX, aY, 0), Vector3D<float32>(0, 0, 0), Vector3D<float32>(0.5f, 0.5f, 0.5f), FALSE, (1 << 1), (1 << 1) | (1 << 0), physics::Collider::eKinematic, 0.1f);
		AddComponent(mCapsuleController);

		graphics::MeshComponent* lPlayerMesh = graphics::RenderManager::Instance()->LoadMeshComponentFromFile("Player");
		lPlayerMesh->GetMaterial()->SetTextureId(graphics::RenderManager::Instance()->LoadTexture("T_SnakeHead.png"));
		lPlayerMesh->GetMaterial()->SetColor(&Color(0.5f, 1.0f, 0.5f, 1.0f));
		lPlayerMesh->SetRotationOffset(Vector3D<float32>(0.0f,0.0f,-90.0f));
		AddComponent(lPlayerMesh);
		mScale.mY = 2.5f;
		mJumping = FALSE;

		graphics::RenderManager::Instance()->GetRenderCamera()->FollowTarget(this, Vector3D<float32>(0.0f, 3.0f, 12.0f), Vector3D<float32>(0.0f, 0.0f, 0.0f));
	}

	void PlatformmerPlayer::Update()
	{
		IGameObject::Update();

		Vector3D<float32> lDir;
		if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerLeft))
		{
			lDir.mX = -1;
		} 
		else if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerRight))
		{
			lDir.mX = 1;
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
	}

	void PlatformmerPlayer::Render()
	{
		IGameObject::Render();
	}

	void PlatformmerPlayer::Release()
	{
		IGameObject::Release();
	}

} // namespace game

