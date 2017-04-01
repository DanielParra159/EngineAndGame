#include "PlatformerPlayer.h"
#include "PlatformGameState.h"
#include "PlatformerProjectile.h"

#include "Input/InputManager.h"

#include "Logic/World.h"

#include "System/Time.h"

#include "IO/FileSystem.h"

#include "Core/Game.h"
#include "Core/Log.h"

#include "Graphics/RenderManager.h"
#include "Graphics/MeshComponent.h"
#include "Graphics/SpriteAnimatorComponent.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"
//#include "Graphics/TextRenderer.h"

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

		mSprite = graphics::RenderManager::Instance()->CreateSpriteAnimatorComponent("NinjaSprites.png", graphics::eRGBA, 4, 10);
		mSprite->AddState(0, 1, 10, 2.5f, FALSE);
		mSprite->AddState(1, 11, 10, 2.5f, TRUE);
		mSprite->AddState(2, 21, 6, 2.5f, FALSE);
		mSprite->AddState(3, 27, 4, 2.5f, FALSE);
		mSprite->AddState(4, 31, 10, 2.0f, FALSE);
		mSprite->PlayState(1);
		mSprite->SetRotationOffset(Vector3D<float32>(0.0f, 0.0f, -90.0f));
		AddComponent(mSprite);

		//mSprite = graphics::RenderManager::Instance()->CreateSpriteComponent("Ninja.png", graphics::eRGBA);
		//mSprite->SetFlipX(FALSE);
		//AddComponent(mSprite);

		/*graphics::MeshComponent* lPlayerMesh = graphics::RenderManager::Instance()->LoadMeshComponentFromFile("Human.obj");
		lPlayerMesh->GetMaterial()->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("T_SnakeHead.png", graphics::eRGB));
		graphics::Material* lMaterial = graphics::RenderManager::Instance()->LoadMaterial("Test02");
		lMaterial->SetColor(&Color(0.5f, 1.0f, 0.5f, 1.0f));
		lPlayerMesh->SetMaterial(lMaterial);
		lPlayerMesh->SetRotationOffset(Vector3D<float32>(0.0f,0.0f,-90.0f));
		AddComponent(lPlayerMesh);
		mScale.mY = 2.5f;*/
		mJumping = FALSE;

		graphics::RenderManager::Instance()->GetRenderCamera()->FollowTarget(this, Vector3D<float32>(0.0f, 3.0f, 12.0f), Vector3D<float32>(0.0f, 0.0f, 0.0f));

		mNextShoot = 0.0f;
		//mSprite->SetRotationOffset(Vector3D<float32>(0.0f, 0.0f, -90.0f));

		mPosition.mZ = 0.5f;

		mScale.mX = 1.0f * 2.0f;
		mScale.mY = 1.77f * 2.0f;

		io::FileSystem::Instance()->ChangeDirectory(".\\materials");
		/*mTextRenderer = new graphics::TextRenderer(800,600);
		mTextRenderer->Load("PerfectPixel.ttf", 18);*/
	}

	void PlatformerPlayer::Update()
	{
		IGameObject::Update();

		Vector3D<float32> lDir;
		if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerLeft))
		{
			lDir.mX = -1;
			mSprite->SetFlipX(TRUE);
		} 
		else if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerRight))
		{
			lDir.mX = 1;
			mSprite->SetFlipX(FALSE);
		}
		
		if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerJump))
		{
			if (mCapsuleController->GetGround())
			{
				mJumping = TRUE;
				mTimeEndJump = sys::Time::GetCurrentSec() + 0.5f;
				mSprite->PlayState(2);
			}
		}
		if (mJumping)
		{
			if (mTimeEndJump > sys::Time::GetCurrentSec()) {
				mCapsuleController->AddForce(Vector3D<float32>::up * 30 * sys::Time::GetDeltaSec());
			} else if (mCapsuleController->GetGround()) {
				mJumping = FALSE;
				mSprite->PlayState(1);
			}
		}
		mCapsuleController->Move(lDir * 20 * sys::Time::GetDeltaSec());


		if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerShoot) 
			&& mNextShoot < sys::Time::GetCurrentSec())
		{
			mSprite->PlayState(4);
			if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerUp))
			{
				lDir.mY = 1.0f;
			}
			else if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerDown))
			{
				lDir.mY = -1.0f;
			}
			if (lDir.Normalize().LengthSqrt() == 0.0f)
				lDir.mX = mSprite->GetFlipX() ? -1.0f : 1.0f;

			//@TODO: Pool
			PlatformerProjectile* lProjectile = new PlatformerProjectile();
			logic::World::Instance()->AddGameObject(lProjectile, TRUE);
			lProjectile->Init(mPosition + lDir * 3.0f, lDir, TRUE);
			mNextShoot = sys::Time::GetCurrentSec() + 2.0f;
		}


	}

	void PlatformerPlayer::PrepareToRender()
	{
		IGameObject::PrepareToRender();
		//mTextRenderer->RenderText("HOLA", 20, 20, 1.0f, Vector3D<float32>(1.0f,1.0f,1.0f));
	}

	void PlatformerPlayer::Release()
	{
		IGameObject::Release();
	}

} // namespace game

