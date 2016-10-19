#include "GameState.h"
#include "Map.h"
#include "Player.h"

#include "Input\InputManager.h"
#include "Input\IController.h"
#include "Input\KeyboardController.h"
#include "Input\MouseController.h"
#include "Input\InputAction.h"

#include "Graphics\RenderManager.h"
#include "Graphics\Camera.h"

#include "UI\MenuManager.h"
#include "UI\Menu.h"

#include "Core\Log.h"
#include "Core\Game.h"

#include "Logic\World.h"



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

		lWorld->Init();

		graphics::RenderManager::Instance()->SetRenderCamera(
		graphics::RenderManager::Instance()->CreatePerspectiveCamera(&Vector3D<float32>(0.0f, 11.2f, 4.0f),
																	 &Vector3D<float32>(0.0f, 0.0f, 1.5f), 
																	 &Vector3D<float32>(0.0f, 0.0f, -1.0f),
																	 75.0f, 800.0f / 600.0f, 1.0f, 1000.0f));

		Map* lMap = new Map();
		lWorld->AddGameObject(lMap, TRUE);

		Player* lPlayer = new Player();
		lWorld->AddGameObject(lPlayer, TRUE);

		return TRUE;
	}

	void GameState::Release()
	{
		ui::MenuManager::Instance()->RemoveMenu(mMenu);
		mMenu = 0;

		logic::World::Instance()->Release();
	}

	BOOL GameState::Update()
	{
		logic::World::Instance()->Update();

		int32 lAction = input::InputManager::Instance()->GetLastActionId();

		switch (lAction)
		{
			case eExit:
				return FALSE;
		}

		return TRUE;
	}

	void GameState::FixedUpdate()
	{
		logic::World::Instance()->FixedUpdate();
	}

	void GameState::Render()
	{
		graphics::RenderManager::Instance()->BeginRender();
		logic::World::Instance()->Render();
		ui::MenuManager::Instance()->Render();
		graphics::RenderManager::Instance()->EndRender();
	}

} // namespace game
