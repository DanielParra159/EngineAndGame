#include "Player.h"
#include "Map.h"
#include "GameState.h"
#include "GameOverState.h"

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
	physics::Collider* capsule;
	void Player::Init(BOOL aActive)
	{
		IGameObject::Init(aActive);

		/*physics::PhysicsManager::Instance()->CreateBoxCollider(Vector3D<float32>(0.3f, 34, 0), Vector3D<float32>(0, 0, 0), Vector3D<float32>(1, 1, 1), FALSE, (1 << 0), (1 << 1) | (1 << 0), physics::Collider::eDynamic, 10.0f);
		physics::PhysicsManager::Instance()->CreateBoxCollider(Vector3D<float32>(0.1f, 30, 0), Vector3D<float32>(0, 0, 0), Vector3D<float32>(1, 1, 1), FALSE, (1 << 0), (1 << 1) | (1 << 0), physics::Collider::eDynamic, 10.0f);
		physics::Collider* a = physics::PhysicsManager::Instance()->CreateBoxCollider(Vector3D<float32>(0, 20, 0), Vector3D<float32>(0, 0, 0), Vector3D<float32>(1, 1, 1), FALSE, (1 << 1), (1 << 1) | (1 << 0), physics::Collider::eDynamic, 10.0f);
		physics::Collider* b = physics::PhysicsManager::Instance()->CreateBoxCollider(Vector3D<float32>(0.5, 1, 0), Vector3D<float32>(0, 0, 0), Vector3D<float32>(1, 1, 1), FALSE, (1 << 0), (1 << 1) | (1 << 0), physics::Collider::eDynamic, 0.1f);
		physics::Collider* c = physics::PhysicsManager::Instance()->CreatePlaneCollider(Vector3D<float32>(0, 0, 0), Vector3D<float32>(0, 1, 0), (1 << 1), (1 << 0));*/
		capsule = physics::PhysicsManager::Instance()->CreateBoxCollider(Vector3D<float32>(0, 0, 0), Vector3D<float32>(0, 0, 0), Vector3D<float32>(0.5f, 0.5f, 0.5f), FALSE, (1 << 1), (1 << 1) | (1 << 0), physics::Collider::eKinematic, 0.1f);
		AddComponent(capsule);

		graphics::MeshComponent* lHead = graphics::RenderManager::Instance()->LoadMeshComponentFromFile("Box.obj");
		lHead->GetMaterial()->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("T_SnakeHead.png", graphics::eRGB));
		lHead->GetMaterial()->SetColor(&Color(0.5f, 1.0f, 0.5f, 1.0f));
		AddComponent(lHead);
		mTail = graphics::RenderManager::Instance()->LoadMeshFromFile("Box.obj");
		mTail->GetMaterial()->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("T_Snake.png", graphics::eRGB));

		mDirection = EDirections::eRight;

		mDelayBetweenMovements = 0.6f;
		mTimeNextMovement = sys::Time::GetCurrentSec() + mDelayBetweenMovements;


		mSnakeLenght = 1;
		for (int32 i = 0; i < mMaxTailLength; ++i)
		{
			mTailStates[i] = new Player::TTailState();
		}
		mTailStates[0]->mLife = 1;
		mTailStates[0]->mPosition = mPosition + Vector3D<float32>(-1, 0, 0);
	}

	void Player::Update()
	{
		IGameObject::Update();

		if (sys::Time::GetCurrentSec() < mTimeNextMovement)
			return;
		mTimeNextMovement = sys::Time::GetCurrentSec() + mDelayBetweenMovements;


		switch (mDirection)
		{
			case Player::eUp:
			case Player::eDown:
				if (input::InputManager::Instance()->IsActionDown(EInputActions::eLeft))
					mDirection = game::Player::eLeft;
				if (input::InputManager::Instance()->IsActionDown(EInputActions::eRight))
					mDirection = game::Player::eRight;
			case Player::eLeft:
			case Player::eRight:
				if (input::InputManager::Instance()->IsActionDown(EInputActions::eUp))
					mDirection = game::Player::eUp;
				if (input::InputManager::Instance()->IsActionDown(EInputActions::eDown))
					mDirection = game::Player::eDown;
		}


		switch (mDirection)
		{
			case game::Player::eUp:
				//capsule->Move(Vector3D<float32>(0, 0, -1));
				ChangePos(mPosition.mX, mPosition.mZ - 1);
				mRotation.mY = 90;
				break;
			case game::Player::eDown:
				//capsule->Move(Vector3D<float32>(0, 0, 1));
				ChangePos(mPosition.mX, mPosition.mZ + 1);
				mRotation.mY = 270;
				break;
			case game::Player::eLeft:
				//capsule->Move(Vector3D<float32>(-1, 0, 0));
				ChangePos(mPosition.mX - 1, mPosition.mZ);
				mRotation.mY = 180;
				break;
			case game::Player::eRight:
				//capsule->Move(Vector3D<float32>(1,0,0));
				ChangePos(mPosition.mX + 1, mPosition.mZ);
				mRotation.mY = 0;
				break;
		}

	}

	void Player::PrepareToRender()
	{
		IGameObject::PrepareToRender();

		for (int32 i = 0; i < mMaxTailLength; ++i)
		{
			//@TODO Can be optimized
			if (mTailStates[i]->mLife > 0)
				mTail->PrepareToRender(&mTailStates[i]->mPosition, &Vector3D<float32>::one, &mTailStates[i]->mRotation);
		}

	}

	void Player::Release()
	{
		IGameObject::Release();
		for (int32 i = 0; i < mMaxTailLength; ++i)
		{
			delete mTailStates[i];
			mTailStates[i] = 0;
		}
		graphics::RenderManager::Instance()->UnloadMesh(mTail, FALSE);
	}

	void Player::ChangePos(float32 aNextX, float32 aNextZ)
	{
		int32 i = 0;
		while (mTailStates[i]->mLife > 0)
		{
			++i;
		}

		mTailStates[i]->mLife = mSnakeLenght + 1;
		mTailStates[i]->mPosition = mPosition;
		mTailStates[i]->mRotation = mRotation;

		mPosition.mX = aNextX;
		mPosition.mZ = aNextZ;
		capsule->SetPosition(mPosition);

		for (i = 0; i < mMaxTailLength; ++i)
		{
			if (mTailStates[i]->mLife > 0)
				--mTailStates[i]->mLife;
		}
	}

	void Player::OnCollisionEnter(physics::Collider* other)
	{
		core::LogString("ONCOL");
		//HACK
		game::GameOverState *lGameState = new game::GameOverState();

		core::Game::Instance()->ChangeGameState(lGameState);
		return;
	}

	void Player::AddCoin()
	{
		if ((mSnakeLenght + 1) == mMaxTailLength)
			return;
		++mSnakeLenght;

		int32 i = 0;
		while (mTailStates[i]->mLife > 0)
		{
			++i;
		}

		mTailStates[i]->mLife = mSnakeLenght + 1;
		mTailStates[i]->mPosition = mPosition;
		mTailStates[i]->mRotation = mRotation;

		++mCoins;

		if (mDelayBetweenMovements > 0.15f)
			mDelayBetweenMovements -= 0.1f;
	}
} // namespace game

