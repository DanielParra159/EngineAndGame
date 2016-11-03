#include "MenuState.h"
#include "GameState.h"
#include "PlatformGameState.h"
#include "NormalMap/NormalMapState.h"
#include "UI/BoxButton.h"

#include "Input/InputManager.h"
#include "Input/IController.h"
#include "Input/KeyboardController.h"
#include "Input/MouseController.h"
#include "Input/InputAction.h"

#include "Graphics/RenderManager.h"
#include "Graphics/Camera.h"

#include "Logic/World.h"
#include "Logic/IGameObject.h"

#include "UI/MenuManager.h"
#include "UI/Menu.h"

#include "Core/Log.h"
#include "Core/Game.h"

#include "Audio/AudioManager.h"
#include "Audio/Sound2D.h"

#include "IO/FileSystem.h"

#include "Defs.h"

namespace game
{
	BOOL MenuState::Init()
	{
		GET_INPUT_MANAGER;
		input::IController* lController;
		lInputManager->ClearAllActionInput();

		if ((lController = lInputManager->CreateController(input::ETypeControls::eKeyboard)) == 0)
			return FALSE;
		lController->RegisterInputAction(eExit, input::KeyboardController::eEscape);
		lController->RegisterInputAction(eNum1, input::KeyboardController::e1);
		lController->RegisterInputAction(eNum2, input::KeyboardController::e2);
		lController->RegisterInputAction(eNum3, input::KeyboardController::e3);

		GET_WORLD;

		lWorld->Init();

		/*graphics::Camera* lCamera = graphics::RenderManager::Instance()->CreatePerspectiveCamera(Vector3D<float32>(0.0f, 0.0f, 4.0f),
		Vector3D<float32>(0.0f, 0.0f, 0.0f),
		Vector3D<float32>(0.0f, 1.0f, 0.0f),
		75.0f, 800.0f / 600.0f, 1.0f, 1000.0f);*/
		graphics::Camera* lCamera = graphics::RenderManager::Instance()->CreateOrthographicCamera(-5.0f, 5.0f, -5.0f, 5.0f, -100.0f, 100.0f);
		
		graphics::RenderManager::Instance()->SetRenderCamera(lCamera);
		logic::IGameObject* lGameObject = new logic::IGameObject();
		lGameObject->AddComponent(lCamera);
		lWorld->AddGameObject(lGameObject, TRUE);

		BoxButton* lBoxButton = new BoxButton();
		lWorld->AddGameObject(lBoxButton, TRUE);
		lBoxButton->Init(Vector3D<float32>(0, -1.5f, 0), -1);

		lBoxButton = new BoxButton();
		lWorld->AddGameObject(lBoxButton, TRUE);
		lBoxButton->Init(Vector3D<float32>(-2, 1.5f, 0), 0);

		lBoxButton = new BoxButton();
		lWorld->AddGameObject(lBoxButton, TRUE);
		lBoxButton->Init(Vector3D<float32>(2, 1.5f, 0), 1);


		mMenu = ui::MenuManager::Instance()->CreateMenu();

		mMenu->AddButton(Rect<>(0, 0, 800, 600), Rect<>(0, 0, 200, 100), &StartGame);

		graphics::RenderManager::Instance()->SetClearColor(Color(0.25f, 0.5f, 0.6f, 1.0f));

		core::LogString("Press 1 on the Game Screen to play snake game");
		core::LogString("Press 2 on the Game Screen to play platform game");
		core::LogString("Press ESC to exit");

		io::FileSystem::Instance()->ChangeDirectory(".\\audio");
		mMusic = audio::AudioManager::Instance()->CreateSound2D("Menu.mp3");
		mMusic->Play(audio::eAudioGroups::eMusic, TRUE);
		return TRUE;
	}

	void MenuState::Release()
	{
		mMusic->Stop();
		ui::MenuManager::Instance()->RemoveMenu(mMenu);
		logic::World::Instance()->Release();
		mMenu = 0;
	}

	BOOL MenuState::Update()
	{

		if (input::InputManager::Instance()->IsActionDown(eExit))
			return FALSE;
		else if (input::InputManager::Instance()->IsActionDown(eNum1))
		{
			io::FileSystem::Instance()->ChangeDirectory(".\\audio");
			audio::AudioManager::Instance()->CreateSound2D("Button.wav")->Play(audio::eAudioGroups::eEffects);

			game::GameState *lGameState = new game::GameState();

			core::Game::Instance()->ChangeGameState(lGameState);
		}
		else if (input::InputManager::Instance()->IsActionDown(eNum2))
		{
			io::FileSystem::Instance()->ChangeDirectory(".\\audio");
			audio::AudioManager::Instance()->CreateSound2D("Button.wav")->Play(audio::eAudioGroups::eEffects);

			game::PlatformGameState *lGameState = new game::PlatformGameState();

			core::Game::Instance()->ChangeGameState(lGameState);
		}
		else if (input::InputManager::Instance()->IsActionDown(eNum3))
		{
			io::FileSystem::Instance()->ChangeDirectory(".\\audio");
			audio::AudioManager::Instance()->CreateSound2D("Button.wav")->Play(audio::eAudioGroups::eEffects);

			game::NormalMapState *lGameState = new game::NormalMapState();

			core::Game::Instance()->ChangeGameState(lGameState);
		}

		return TRUE;
	}

	void MenuState::Render()
	{
		graphics::RenderManager::Instance()->BeginRender();
		ui::MenuManager::Instance()->Render();

		logic::World::Instance()->Render();
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
