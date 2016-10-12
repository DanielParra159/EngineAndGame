#include "Player.h"
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

		mMesh = graphics::RenderManager::Instance()->LoadMesh("Prueba");

		mDirection = EDirections::eRight;

		mDelayBetweenMovements = 1.0f;
		mTimeNextMovement = sys::Time::GetCurrentSec() + mDelayBetweenMovements;
		mLastAction = -1;
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
				ChangePos(mPosition.mX, mPosition.mZ - 1);
				break;
			case game::Player::eDown:
				ChangePos(mPosition.mX, mPosition.mZ + 1);
				break;
			case game::Player::eLeft:
				ChangePos(mPosition.mX - 1, mPosition.mZ);
				break;
			case game::Player::eRight:
				ChangePos(mPosition.mX + 1, mPosition.mZ);
				break;
		}
	}

	void Player::Render()
	{
		mMesh->Render(&mPosition, &mScale, &mRotation);

		
	}

	void Player::Release()
	{

	}

	void Player::ChangePos(float32 aNextX, float32 aNextZ)
	{
		mPosition.mX = aNextX;
		mPosition.mZ = aNextZ;
	}
} // namespace game

