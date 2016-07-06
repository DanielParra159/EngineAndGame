#include "GameState.h"
#include "Player.h"

#include "Types.h"
#include "Logic\World.h"

#include "Input\InputManager.h"
#include "Input\IController.h"
#include "Input\InputAction.h"

#include "Defs.h"

namespace game
{
	BOOL GameState::Init()
	{
		GET_INPUT_MANAGER;
		input::IController* lController;
		if ((lController = lInputManager->CreateController(input::eTypeControls::Keyboard)) == 0)
			return FALSE;

		input::InputAction* lInputAction = new input::InputAction();
		lInputAction->Init(0, 0);
		lController->RegisterInputAction(lInputAction);
		lInputAction->Init(1, 2);
		lController->RegisterInputAction(lInputAction);

		GET_WORLD;

		lWorld->Init(18, 18);

		for (uint32 i = 0; i < 18; ++i)
		{
			lWorld->SetCell(i, 1, (uint32)1);  //up2
		}

		for (uint32 i = 0; i < 18; ++i)
		{
			lWorld->SetCell(i, 0, (uint32)0); //up1
			lWorld->SetCell(17, i, (uint32)0); //left

			lWorld->SetCell(0, i, (uint32)0); //right

		}

		for (uint32 i = 0; i < 18; ++i)
		{
			lWorld->SetCell(i, 16, (uint32)0);
			lWorld->SetCell(i, 17, (uint32)1);
		}

		mPlayer = new Player();

		mPlayer->Init();

		return TRUE;
	}

	void GameState::Release()
	{
		mPlayer->Release();

		logic::World::Instance()->Release();
	}

	BOOL GameState::Update()
	{
		logic::World::Instance()->Update();
		mPlayer->Update();

		return TRUE;
	}


	void GameState::OnPause()
	{

	}
	void GameState::OnResume()
	{

	}
} // namespace game
