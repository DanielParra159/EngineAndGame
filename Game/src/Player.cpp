#include "Player.h"
#include "Map.h"
#include "GameState.h"
#include "GameOverState.h"

#include "Input\InputManager.h"

#include "System\Time.h"

#include "Core\Game.h"

#include "Graphics\RenderManager.h"
#include "Graphics\Mesh.h"

#include "Support\Vector3D.h"
namespace game
{
	void Player::Init(BOOL aActive)
	{
		IGameObject::Init(aActive);

		mHead = graphics::RenderManager::Instance()->LoadMeshFromFile("Prueba");
		mTail = graphics::RenderManager::Instance()->LoadMeshFromFile("Prueba2");

		mDirection = EDirections::eRight;

		mDelayBetweenMovements = 1.0f;
		mTimeNextMovement = sys::Time::GetCurrentSec() + mDelayBetweenMovements;
		mLastAction = -1;
		mPosition.mX = 0.5f;
		mPosition.mZ = 0.5f;

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
		int32 lAction = input::InputManager::Instance()->GetLastActionId();
		if (mLastAction < 0 && lAction > -1)
			mLastAction = lAction;

		if (sys::Time::GetCurrentSec() < mTimeNextMovement)
			return;
		mTimeNextMovement = sys::Time::GetCurrentSec() + mDelayBetweenMovements;


		switch (mDirection)
		{
			case Player::eUp:
			case Player::eDown:
				switch (mLastAction)
				{
					case EInputActions::eLeft:
						mDirection = game::Player::eLeft;
						break;
					case EInputActions::eRight:
						mDirection = game::Player::eRight;
						break;
				};
				break;
			case Player::eLeft:
			case Player::eRight:
				switch (mLastAction)
				{
					case EInputActions::eUp:
						mDirection = game::Player::eUp;
						break;
					case EInputActions::eDown:
						mDirection = game::Player::eDown;
						break;
				};
				break;
		}
		mLastAction = -1;


		switch (mDirection)
		{
			case game::Player::eUp:
				mRotation.mY = 0;
				ChangePos(mPosition.mX, mPosition.mZ - 1);
				break;
			case game::Player::eDown:
				mRotation.mY = 180;
				ChangePos(mPosition.mX, mPosition.mZ + 1);
				break;
			case game::Player::eLeft:
				mRotation.mY = 270;
				ChangePos(mPosition.mX - 1, mPosition.mZ);
				break;
			case game::Player::eRight:
				mRotation.mY = 90;
				ChangePos(mPosition.mX + 1, mPosition.mZ);
				break;
		}
	}

	void Player::Render()
	{
		mHead->Render(&mPosition, &mScale, &mRotation);

		for (int32 i = 0; i < mMaxTailLength; ++i)
		{
			//@TODO Can be optimized
			if (mTailStates[i]->mLife > 0)
				mTail->Render(&mTailStates[i]->mPosition);
		}
		
	}

	void Player::Release()
	{
		for (int32 i = 0; i < mMaxTailLength; ++i)
		{
			delete mTailStates[i];
			mTailStates[i] = 0;
		}
		graphics::RenderManager::Instance()->UnloadMesh(mHead);
		graphics::RenderManager::Instance()->UnloadMesh(mTail);
	}

	void Player::ChangePos(float32 aNextX, float32 aNextZ)
	{
		if (aNextX >= Map::sMapSize.mX*0.5f - 1.0f || aNextX <= -(Map::sMapSize.mX*0.5f - 1.0f)
			|| aNextZ >= Map::sMapSize.mY*0.5f - 1.0f || aNextZ <= -(Map::sMapSize.mY*0.5f - 1.0f))
		{
			//HACK
			game::GameOverState *lGameState = new game::GameOverState();

			core::Game::Instance()->ChangeGameState(lGameState);
			return;
		}

		int32 i = 0;
		while (mTailStates[i]->mLife > 0)
		{
			++i;
		}

		mTailStates[i]->mLife = mSnakeLenght+1;
		mTailStates[i]->mPosition = mPosition;

		mPosition.mX = aNextX;
		mPosition.mZ = aNextZ;

		for (i = 0; i < mMaxTailLength && mTailStates[i]->mLife > 0; ++i)
		{
			--mTailStates[i]->mLife;
		}
	}
} // namespace game

