#include "GameState.h"
#include "Player.h"

#include "Types.h"
#include "Types\Vector2D.h"
#include "Core\Log.h"

#include "Logic\World.h"

#include "Input\InputManager.h"
#include "Input\IController.h"
#include "Input\KeyboardController.h"
#include "Input\MouseController.h"
#include "Input\InputAction.h"

#include "Graphics\RenderManager.h"

#include "UI\MenuManager.h"

#include "Defs.h"

namespace game
{
	BOOL GameState::Init()
	{
		GET_INPUT_MANAGER;
		input::IController* lController;
		if ((lController = lInputManager->CreateController(input::ETypeControls::eKeyboard)) == 0)
			return FALSE;

		input::InputAction* lInputAction = new input::InputAction();
		lInputAction->Init(eExit, input::KeyboardController::eEscape);
		lController->RegisterInputAction(lInputAction);
		lInputAction->Init(eUp, input::KeyboardController::eUp);
		lController->RegisterInputAction(lInputAction);
		lInputAction->Init(eDown, input::KeyboardController::eDown);
		lController->RegisterInputAction(lInputAction);
		lInputAction->Init(eLeft, input::KeyboardController::eLeft);
		lController->RegisterInputAction(lInputAction);
		lInputAction->Init(eRight, input::KeyboardController::eRight);
		lController->RegisterInputAction(lInputAction);

		if ((lController = lInputManager->CreateController(input::ETypeControls::eMouse)) == 0)
			return FALSE;
		lInputAction->Init(eRight, input::MouseController::eLeftButton);
		lController->RegisterInputAction(lInputAction);

		GET_WORLD;

		lWorld->Init(18, 18);

		for (uint32 i = 0; i < 18; ++i)
		{
			lWorld->SetCell(i, 1, (uint32)ETypeEntities::eWall1);  //up2
		}

		for (uint32 i = 0; i < 18; ++i)
		{
			lWorld->SetCell(i, 0, (uint32)ETypeEntities::eWall0); //up1
			lWorld->SetCell(17, i, (uint32)ETypeEntities::eWall0); //left

			lWorld->SetCell(0, i, (uint32)ETypeEntities::eWall0); //right

		}

		for (uint32 i = 0; i < 18; ++i)
		{
			lWorld->SetCell(i, 16, (uint32)ETypeEntities::eWall0);
			lWorld->SetCell(i, 17, (uint32)ETypeEntities::eWall1);
		}

		mPlayer = new Player();

		lWorld->SetCell(4, 6, 5.0f, ETypeEntities::ePoint);

		mPlayer->Init(7,7,3);

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

		int32 lAction = input::InputManager::Instance()->GetLastActionId();

		switch (lAction)
		{
			case eExit:
				return FALSE;
		}

		return TRUE;
	}

	void GameState::Render()
	{
		graphics::RenderManager::Instance()->BeginRender();
		logic::World::Instance()->Render();
		ui::MenuManager::Instance()->Render();
		graphics::RenderManager::Instance()->EndRender();
	}


} // namespace game
