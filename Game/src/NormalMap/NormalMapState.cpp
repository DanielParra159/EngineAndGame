#include "NormalMapState.h"
#include "MenuState.h"

#include "Input/InputManager.h"
#include "Input/IController.h"
#include "Input/KeyboardController.h"
#include "Input/MouseController.h"
#include "Input/InputAction.h"

#include "Graphics/RenderManager.h"
#include "Graphics/Camera.h"
#include "Graphics/Material.h"
#include "Graphics/Mesh.h"

#include "UI/MenuManager.h"
#include "UI/Menu.h"

#include "Core/Log.h"
#include "Core/Game.h"

#include "Logic/World.h"
#include "Logic/IGameObject.h"

#include "Audio/AudioManager.h"
#include "Audio/Sound2D.h"

#include "IO/FileSystem.h"

#include "Script/ScriptManager.h"

#include "System/Time.h"

#include "Support/Math.h"
#include "Support/Vector3D.h"

#include "Defs.h"


namespace game
{
	BOOL NormalMapState::Init()
	{
		GET_INPUT_MANAGER;
		lInputManager->ClearAllActionInput();
		input::IController* lController;
		if ((lController = lInputManager->CreateController(input::ETypeControls::eKeyboard)) == 0)
			return FALSE;

		lController->RegisterInputAction(eNormalMapExit, input::KeyboardController::eEscape);

		GET_WORLD;

		lWorld->Init();

		
		graphics::Camera* lCamera = graphics::RenderManager::Instance()->CreateOrthographicCamera(-10.0f, 10.0f, -10.0f, 10.0f, -100.0f, 100.0f);
		graphics::RenderManager::Instance()->SetRenderCamera(lCamera);
		logic::IGameObject* lGameObject = new logic::IGameObject();
		lGameObject->AddComponent(lCamera);
		lWorld->AddGameObject(lGameObject, TRUE);

		graphics::RenderManager::Instance()->SetClearColor(Color(0.3f, 0.2f, 0.2f, 1.0f));

		io::FileSystem::Instance()->ChangeDirectory(".\\audio");
		mMusic = audio::AudioManager::Instance()->CreateSound2D("PlatformGame.wav");
		mMusic->Play(audio::eAudioGroups::eMusic, TRUE);

		io::FileSystem::Instance()->ChangeDirectory(".\\materials");
		mMesh = graphics::RenderManager::Instance()->LoadMeshFromFile("Box.obj");
		graphics::Material* lMaterial = graphics::RenderManager::Instance()->LoadMaterial("Test02");
		lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("brickwall.jpg", graphics::eRGB));
		mMesh->SetMaterial(lMaterial);

		mMeshNormal = graphics::RenderManager::Instance()->LoadMeshFromFile("Box.obj");
		lMaterial = graphics::RenderManager::Instance()->LoadMaterial("Test03");
		lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("brickwall.jpg", graphics::eRGB));
		lMaterial->SetNormalTexture(graphics::RenderManager::Instance()->LoadTexture("brickwall_normal.jpg", graphics::eRGB));
		mMeshNormal->SetMaterial(lMaterial);

		return TRUE;
	}

	void NormalMapState::Release()
	{
		mMusic->Stop();

		logic::World::Instance()->Release();
	}

	BOOL NormalMapState::Update()
	{
		logic::World::Instance()->Update();

		if (input::InputManager::Instance()->IsActionDown(eNormalMapExit))
		{
			game::MenuState *lGameState = new game::MenuState();

			core::Game::Instance()->ChangeGameState(lGameState);
		}

		return TRUE;
	}

	void NormalMapState::FixedUpdate()
	{
		logic::World::Instance()->FixedUpdate();
	}

	void NormalMapState::Render()
	{
		graphics::RenderManager::Instance()->BeginRender();
		logic::World::Instance()->Render();
		ui::MenuManager::Instance()->Render();

		mMesh->PrepareToRender(&Vector3D<float32>(6, 3, -3), &Vector3D<float32>(5, 5,5), &Vector3D<float32>(0, 0, 0));
		mMeshNormal->PrepareToRender(&Vector3D<float32>(0, 3, 0), &Vector3D<float32>(5, 5, 5), &Vector3D<float32>(0, 0, 0));
		graphics::RenderManager::Instance()->EndRender();
	}

} // namespace game
