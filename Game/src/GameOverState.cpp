#include "GameOverState.h"
#include "GameState.h"

#include "Input\InputManager.h"
#include "Input\IController.h"
#include "Input\KeyboardController.h"
#include "Input\MouseController.h"
#include "Input\InputAction.h"

#include "Graphics\RenderManager.h"

#include "UI\MenuManager.h"
#include "UI\Menu.h"

#include "Core\Log.h"
#include "Core\Game.h"

#include "Defs.h"

namespace game
{
	BOOL GameOverState::Init()
	{
		GET_INPUT_MANAGER;
		input::IController* lController;
		if ((lController = lInputManager->CreateController(input::ETypeControls::eMouse)) == 0)
			return FALSE;

		lController->RegisterInputAction(5, input::MouseController::eLeftButton);

		mMenu = ui::MenuManager::Instance()->CreateMenu();

//		mMenu->AddButton(Rect<>(0, 0, 576, 576), Rect<>(0, 0, 480, 480), &StartGame);
//		mMenu->AddButton(Rect<>(0, 0, 800, 600), Rect<>(0, 0, 200, 100), &StartGame);

		return TRUE;
	}

	void GameOverState::Release()
	{
		ui::MenuManager::Instance()->RemoveMenu(mMenu);
		mMenu = 0;
	}

	BOOL GameOverState::Update()
	{
		return TRUE;
	}

	void GameOverState::Render()
	{
		graphics::RenderManager::Instance()->BeginRender();
		ui::MenuManager::Instance()->Render();
		graphics::RenderManager::Instance()->EndRender();
	}

	void GameOverState::StartGame()
	{
		core::LogString("START GAME");

		
		game::GameState *lGameState = new game::GameState();

		core::Game::Instance()->ChangeGameState(lGameState);
	}

} // namespace game
