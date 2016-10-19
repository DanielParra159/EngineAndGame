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

#include "Audio\AudioManager.h"
#include "Audio\Sound2D.h"

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
		lInputAction->Init(eLeftButton, input::MouseController::eLeftButton);
		lController->RegisterInputAction(lInputAction);

		if ((lController = lInputManager->CreateController(input::ETypeControls::eKeyboard)) == 0)
			return FALSE;
		lInputAction = new input::InputAction();
		lInputAction->Init(eExit, input::KeyboardController::eEscape);
		lController->RegisterInputAction(lInputAction);
		lInputAction = new input::InputAction();
		lInputAction->Init(eNum1, input::KeyboardController::e1);
		lController->RegisterInputAction(lInputAction);

		mMenu = ui::MenuManager::Instance()->CreateMenu();

		mMenu->AddButton(Rect<>(0, 0, 800, 600), Rect<>(0, 0, 200, 100), &StartGame);

		graphics::RenderManager::Instance()->SetClearColor(Color(0.25f, 0.5f, 0.6, 1.0f));

		core::LogString("Press 1 on the Game Screen to play Snake Game");
		return TRUE;
	}

	void MenuState::Release()
	{
		ui::MenuManager::Instance()->RemoveMenu(mMenu);
		mMenu = 0;
	}

	BOOL MenuState::Update()
	{
		int32 lAction = input::InputManager::Instance()->GetLastActionId();

		switch (lAction)
		{
			case eExit:
				return FALSE;
			case eNum1:
				audio::AudioManager::Instance()->CreateSound2D("audio/Button.wav")->Play(audio::eAudioGroups::eEffects);

				game::GameState *lGameState = new game::GameState();

				core::Game::Instance()->ChangeGameState(lGameState);
				break;
		}

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
		/*core::LogString("START GAME");

		audio::AudioManager::Instance()->CreateSound2D("audio/button.mp3")->Play(audio::eAudioGroups::eEffects);
		
		game::GameState *lGameState = new game::GameState();

		core::Game::Instance()->ChangeGameState(lGameState);*/
	}

} // namespace game
