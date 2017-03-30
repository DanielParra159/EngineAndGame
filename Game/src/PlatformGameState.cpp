#include "PlatformGameState.h"
#include "MenuState.h"
#include "Platformmer/PlatformerWall.h"
#include "Platformmer/PlatformerPlayer.h"
#include "Platformmer/PlatformerGrass.h"

#include "Input/InputManager.h"
#include "Input/IController.h"
#include "Input/KeyboardController.h"
#include "Input/MouseController.h"
#include "Input/InputAction.h"

#include "Graphics/RenderManager.h"
#include "Graphics/Camera.h"

#include "UI/MenuManager.h"
#include "UI/Menu.h"

#include "Core/Log.h"
#include "Core/Game.h"

#include "Logic/World.h"

#include "Audio/AudioManager.h"
#include "Audio/Sound2D.h"

#include "IO/FileSystem.h"

#include "Script/ScriptManager.h"

#include "System/Time.h"

#include "Support/Math.h"

#include "Defs.h"


namespace
{
	void AddWall(game::PlatformerWall* aGameObject)
	{
		logic::World::Instance()->AddGameObject(aGameObject, TRUE);
	}
	void AddPlayer(game::PlatformerPlayer* aGameObject)
	{
		logic::World::Instance()->AddGameObject(aGameObject, TRUE);
	}
}

//HACK to register lua functions once
static BOOL firstTime = TRUE;

namespace game
{
	BOOL PlatformGameState::Init()
	{
		GET_INPUT_MANAGER;
		lInputManager->ClearAllActionInput();
		input::IController* lController;
		if ((lController = lInputManager->CreateController(input::ETypeControls::eKeyboard)) == 0)
			return FALSE;

		lController->RegisterInputAction(ePltatformmerExit, input::KeyboardController::eEscape);
		lController->RegisterInputAction(ePltatformmerUp, input::KeyboardController::eUp);
		lController->RegisterInputAction(ePltatformmerDown, input::KeyboardController::eDown);
		lController->RegisterInputAction(ePltatformmerLeft, input::KeyboardController::eLeft);
		lController->RegisterInputAction(ePltatformmerRight, input::KeyboardController::eRight);
		lController->RegisterInputAction(ePltatformmerJump, input::KeyboardController::eLeftControl);
		lController->RegisterInputAction(ePltatformmerShoot, input::KeyboardController::eSpace);

		/*if ((lController = lInputManager->CreateController(input::ETypeControls::eMouse)) == 0)
			return FALSE;*/


		GET_WORLD;

		lWorld->Init();

		
		graphics::Camera* lCamera =	graphics::RenderManager::Instance()->CreatePerspectiveCamera(Vector3D<float32>(2.0f, 10.2f, 12.0f),
																		Vector3D<float32>(2.0f, 7.0f, 0.0f),
																		Vector3D<float32>(0.0f, 0.0f, -1.0f),
																		75.0f, 800.0f / 600.0f, 1.0f, 1000.0f);
		
		graphics::RenderManager::Instance()->SetRenderCamera(lCamera);
		logic::IGameObject* lGameObject = new logic::IGameObject();
		lGameObject->AddComponent(lCamera);
		lWorld->AddGameObject(lGameObject, TRUE);

		graphics::RenderManager::Instance()->SetClearColor(Color(0.3f, 0.2f, 0.2f, 1.0f));

		io::FileSystem::Instance()->ChangeDirectory(".\\audio");
		mMusic = audio::AudioManager::Instance()->CreateSound2D("PlatformGame.wav");
		mMusic->Play(audio::eAudioGroups::eMusic, TRUE);

		if (firstTime)
		{
			firstTime = FALSE;

			luabind::module(script::ScriptManager::Instance()->GetNativeInterpreter())
				[
					luabind::def("AddWall", AddWall, luabind::adopt(_1)),
					luabind::def("AddPlayer", AddPlayer, luabind::adopt(_1))
				];

			luabind::module(script::ScriptManager::Instance()->GetNativeInterpreter())
				[
					luabind::class_<game::PlatformerWall>("PlatformmerWall")
					.def(luabind::constructor<>())
					.def("Init", (void(game::PlatformerWall::*)(float32, float32, float32, float32))&game::PlatformerWall::LuaInit)
				];
			luabind::module(script::ScriptManager::Instance()->GetNativeInterpreter())
				[
					luabind::class_<game::PlatformerPlayer>("PlatformmerPlayer")
					.def(luabind::constructor<>())
					.def("Init", (void(game::PlatformerPlayer::*)(float32, float32))&game::PlatformerPlayer::LuaInit)
				];
		}

		io::FileSystem::Instance()->ChangeDirectory(".\\Maps");
		script::ScriptManager::Instance()->LoadScript("MapParser.lua");

		std::string orden2 = "Test2(\""+ io::FileSystem::Instance()->GetCurrentDir() +"\\Map01.lua\")";

		std::string lDir = io::FileSystem::Instance()->GetCurrentDir();
		lDir.replace(lDir.find("\\"), 1, "/");
		lDir.replace(lDir.find("\\"), 1, "/");
		lDir += "/Map01.lua";

		std::string lAux = "ParseMap(\""+ lDir+"\",\"HOLA\")";

		script::ScriptManager::Instance()->ExecuteScript(lAux.c_str());


		PlatformerGrass* lPlatformerGrass = new PlatformerGrass();
		lWorld->AddGameObject(lPlatformerGrass, TRUE);
		lPlatformerGrass->Init(TRUE, 0, 0);
		

		return TRUE;
	}

	void PlatformGameState::Release()
	{
		mMusic->Stop();

		logic::World::Instance()->Release();
	}

	BOOL PlatformGameState::Update()
	{
		logic::World::Instance()->Update();

		if (input::InputManager::Instance()->IsActionDown(ePltatformmerExit))
		{
			game::MenuState *lGameState = new game::MenuState();

			core::Game::Instance()->ChangeGameState(lGameState);
		}

		return TRUE;
	}

	void PlatformGameState::FixedUpdate()
	{
		logic::World::Instance()->FixedUpdate();
	}

	void PlatformGameState::Render()
	{
		graphics::RenderManager::Instance()->BeginRender();
		logic::World::Instance()->Render();
		ui::MenuManager::Instance()->Render();
		graphics::RenderManager::Instance()->EndRender();
	}

} // namespace game
