#include "Player.h"
#include "GameState.h"
#include "GameOverState.h"

#include "Logic\World.h"
#include "Logic\WorldCell.h"

#include "Input\InputManager.h"

#include "System\Time.h"

#include "Core\Game.h"

namespace game
{
	BOOL Player::Init(uint32 aX, uint32 aY, uint32 aSnakeLenght)
	{
		logic::World *lWorld = logic::World::Instance();

		mPosition.mX = aX;
		mPosition.mY = aY;

		mSnakeLenght = aSnakeLenght;
		mDelayBetweenMovements = 0.2f;

		uint32 lTailLenght = mSnakeLenght-1;
		uint32 lX = 7;

		lWorld->SetCell(lX, 7, mSnakeLenght*mDelayBetweenMovements, ETypeEntities::eSnakeHead);
		for (uint32 i = 0; i < lTailLenght; ++i)
		{
			lWorld->SetCell(--lX, 7, (lTailLenght*mDelayBetweenMovements) -(i*mDelayBetweenMovements), ETypeEntities::eSnakeTail);
		}

		mDirection = EDirections::eRight;

		mTimeNextMovement = sys::Time::GetCurrentSec() + mDelayBetweenMovements;
		mLastAction = -1;

		return TRUE;
	}
	void Player::Release()
	{

	}

	void Player::Update()
	{
		int32 lAction = input::InputManager::Instance()->GetActionId();
		if (mLastAction < 0 && lAction > -1)
			mLastAction = lAction;

		if (sys::Time::GetCurrentSec() < mTimeNextMovement) 
			return;
		mTimeNextMovement = sys::Time::GetCurrentSec() + mDelayBetweenMovements;


		uint32 l[] = { game::Player::eUp, game::Player::eDown, game::Player::eLeft, game::Player::eRight };

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
				ChangePos(mPosition.mX, mPosition.mY - 1);
				break;
			case game::Player::eDown:
				ChangePos(mPosition.mX, mPosition.mY + 1);
				break;
			case game::Player::eLeft:
				ChangePos(mPosition.mX - 1, mPosition.mY);
				break;
			case game::Player::eRight:
				ChangePos(mPosition.mX + 1, mPosition.mY);
				break;
		}
	}

	void Player::ChangePos(uint32 aNextX, uint32 aNextY)
	{
		logic::World *lWorld = logic::World::Instance();
		const logic::WorldCell* lWorldCell = lWorld->GetCell(aNextX, aNextY);

		if (lWorldCell->GetType() == ETypeEntities::eWall0 || lWorldCell->GetType() == ETypeEntities::eWall1)
		{
			//HACK
			game::GameOverState *lGameState = new game::GameOverState();

			core::Game::Instance()->ChangeGameState(lGameState);
		}
		else {
			if (lWorldCell->GetType() == ETypeEntities::ePoint)
			{
				++mSnakeLenght;
			}
			lWorld->SetCell(mPosition.mX, mPosition.mY, (uint32)ETypeEntities::eSnakeTail);
			mPosition.mX = aNextX;
			mPosition.mY = aNextY;
			//eUp, eDown, eLeft, eRight
			float64 lAngle[] = { 270.0, 90.0, 180.0, 0.0 };
			lWorld->SetCellAngle(mPosition.mX, mPosition.mY, lAngle[mDirection]);
			lWorld->SetCell(mPosition.mX, mPosition.mY, mSnakeLenght*mDelayBetweenMovements, ETypeEntities::eSnakeHead);
		}

	}
} // namespace game

