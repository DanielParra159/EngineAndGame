#include "Player.h"
#include "Logic\World.h"

namespace game
{
	BOOL Player::Init()
	{
		logic::World *lWorld = logic::World::Instance();

		lWorld->SetCell(7, 7, (uint32)3);
		lWorld->SetCell(6, 7, 2.0f, 4);
		lWorld->SetCell(5, 7, 1.0f, 4);

		return TRUE;
	}
	void Player::Release()
	{

	}

	void Player::Update()
	{

	}
} // namespace game

