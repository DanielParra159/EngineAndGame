#include "MenuState.h"
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
	BOOL MenuState::Init()
	{
		GET_INPUT_MANAGER;
		input::IController* lController;
		if ((lController = lInputManager->CreateController(input::ETypeControls::eMouse)) == 0)
			return FALSE;

		input::InputAction* lInputAction = new input::InputAction();
		lInputAction->Init(5, input::MouseController::eLeftButton);
		lController->RegisterInputAction(lInputAction);

		mMenu = ui::MenuManager::Instance()->CreateMenu();

		mMenu->AddButton(Rect<>(188, 200, 200, 100), Rect<>(0, 0, 200, 100), &StartGame, "assets/StartButton.png");

		return TRUE;
	}

	void MenuState::Release()
	{
		ui::MenuManager::Instance()->RemoveMenu(mMenu);
		mMenu = 0;
	}

	BOOL MenuState::Update()
	{
		return TRUE;
	}

	void MenuState::Render()
	{
		graphics::RenderManager::Instance()->BeginRender();
		ui::MenuManager::Instance()->Render();
		graphics::RenderManager::Instance()->EndRender();
	}

	void MenuState::StartGame()
	{
		core::LogString("START GAME");

		
		game::GameState *lGameState = new game::GameState();

		core::Game::Instance()->ChangeGameState(lGameState);
	}

} // namespace game