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
		mDelayBetweenKunais = 0.5f;
		mDelayBetweenMelee = 1.0f;

		mCapsuleController = physics::PhysicsManager::Instance()->CreateCapsuleController(Vector3D<float32>(aX, aY+1.0f, 0), 1.0f, 1.5f, 0.7f, physics::CapsuleController::eClimbingMode::eEASY, (1 << 1), (1 << 1) | (1 << 0));
		//physics::Collider* lCapsule = physics::PhysicsManager::Instance()->CreateBoxCollider(Vector3D<float32>(aX, aY, 0), Vector3D<float32>(0, 0, 0), Vector3D<float32>(0.5f, 0.5f, 0.5f), FALSE, (1 << 1), (1 << 1) | (1 << 0), physics::Collider::eKinematic, 0.1f);
		AddComponent(mCapsuleController);

		mSprite = graphics::RenderManager::Instance()->CreateSpriteAnimatorComponent("NinjaSprites.png", graphics::eRGBA, 7, 10);
		mSprite->AddState(eMelee, 1, 10, 2.5f, FALSE);
		mSprite->AddState(eRun, 11, 10, 2.5f, TRUE);
		mSprite->AddState(eStartJump, 21, 6, 2.5f, FALSE);
		mSprite->AddState(eEndJump, 27, 4, 1.0f, FALSE);
		mSprite->AddState(eKunai, 31, 10, 2.0f, FALSE);
		mSprite->AddState(eIdle, 41, 2, 2.0f, TRUE);
		mSprite->AddState(eJumpKunai, 51, 10, 2.0f, FALSE);
		mSprite->AddState(eJumpMelee, 61, 10, 2.5f, FALSE);
		mSprite->AddTransition(eRun, eStartJump, graphics::eConditionType::eTrueBool, "Jump");
		mSprite->AddTransition(eIdle, eStartJump, graphics::eConditionType::eTrueBool, "Jump");
		mSprite->AddTransition(eStartJump, eEndJump, graphics::eConditionType::eFalseBool, "Jump");
		mSprite->AddTransition(eEndJump, eIdle, graphics::eConditionType::eEnd, "");
		mSprite->AddTransition(eKunai, eIdle, graphics::eConditionType::eEnd, "");
		mSprite->AddTransition(eRun, eKunai, graphics::eConditionType::eTrigger, "Kunai");
		mSprite->AddTransition(eKunai, eKunai, graphics::eConditionType::eTrigger, "Kunai");
		mSprite->AddTransition(eIdle, eKunai, graphics::eConditionType::eTrigger, "Kunai");
		mSprite->AddTransition(eStartJump, eJumpKunai, graphics::eConditionType::eTrigger, "Kunai");
		mSprite->AddTransition(eJumpKunai, eJumpKunai, graphics::eConditionType::eTrigger, "Kunai");
		mSprite->AddTransition(eJumpKunai, eIdle, graphics::eConditionType::eEnd, "");
		mSprite->AddTransition(eMelee, eIdle, graphics::eConditionType::eEnd, "");
		mSprite->AddTransition(eRun, eMelee, graphics::eConditionType::eTrigger, "Melee");
		mSprite->AddTransition(eIdle, eMelee, graphics::eConditionType::eTrigger, "Melee");
		mSprite->AddTransition(eStartJump, eJumpMelee, graphics::eConditionType::eTrigger, "Melee");
		mSprite->AddTransition(eJumpMelee, eJumpMelee, graphics::eConditionType::eTrigger, "Melee");
		mSprite->AddTransition(eMelee, eMelee, graphics::eConditionType::eTrigger, "Melee");
		mSprite->AddTransition(eJumpMelee, eIdle, graphics::eConditionType::eEnd, "");
		mSprite->AddTransition(eIdle, eRun, graphics::eConditionType::eTrueBool, "Run");
		mSprite->AddTransition(eRun, eIdle, graphics::eConditionType::eFalseBool, "Run");
		mSprite->PlayState(eIdle);
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

		mNextTimeKunaiAllowed = 0.0f;
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
				mSprite->SetBoolParameter("Jump", TRUE);
			}
		}
		if (mJumping)
		{
			if (mTimeEndJump > sys::Time::GetCurrentSec()) {
				mCapsuleController->AddForce(Vector3D<float32>::up * 30 * sys::Time::GetDeltaSec());
			} else if (mCapsuleController->GetGround()) {
				mJumping = FALSE;
				mSprite->SetBoolParameter("Jump", FALSE);
			}
		}
		mSprite->SetBoolParameter("Run", lDir.mX != 0 ? TRUE : FALSE);
		mCapsuleController->Move(lDir * 20 * sys::Time::GetDeltaSec());


		if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerKunai) 
			&& mNextTimeKunaiAllowed < sys::Time::GetCurrentSec())
		{
			mSprite->SetTriggerParameter("Kunai");
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
			mNextTimeKunaiAllowed = sys::Time::GetCurrentSec() + mDelayBetweenKunais;
		}
		else if (input::InputManager::Instance()->IsActionDown(EPltatformmerInputActions::ePltatformmerMelee)
			&& mNextTimeMeleeAllowed < sys::Time::GetCurrentSec())
		{
			mNextTimeMeleeAllowed = sys::Time::GetCurrentSec() + mDelayBetweenMelee;
			mSprite->SetTriggerParameter("Melee");
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

