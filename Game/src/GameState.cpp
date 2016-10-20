#include "GameState.h"
#include "Map.h"
#include "Player.h"
#include "Box.h"

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

#include "System/Time.h"

#include "Support/Math.h"

#include "Defs.h"

namespace game
{

	const Vector2D<float32> GameState::sMapSize = Vector2D<float32>(18.0f, 18.0f);

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
		graphics::RenderManager::Instance()->CreatePerspectiveCamera(&Vector3D<float32>(0.0f, 16.2f, 4.0f),
																	 &Vector3D<float32>(0.0f, 0.0f, 1.5f), 
																	 &Vector3D<float32>(0.0f, 0.0f, -1.0f),
																	 75.0f, 800.0f / 600.0f, 1.0f, 1000.0f));

		Map* lMap = new Map();
		lWorld->AddGameObject(lMap, TRUE);

		Player* lPlayer = new Player();
		lWorld->AddGameObject(lPlayer, TRUE);

		const float32 lWallVertexData[] = {
			// X      Y     Z     U     V
			-9.0f, -0.5f, -0.5f, 0.0f, 0.0f,
			9.0f, -0.5f, -0.5f, 9.0f, 0.0f,
			9.0f,  0.5f, -0.5f, 9.0f, 1.0f,
			9.0f,  0.5f, -0.5f, 9.0f, 1.0f,
			-9.0f,  0.5f, -0.5f, 0.0f, 1.0f,
			-9.0f, -0.5f, -0.5f, 0.0f, 0.0f,

			-9.0f, -0.5f,  0.5f, 0.0f, 0.0f,
			9.0f, -0.5f,  0.5f, 9.0f, 0.0f,
			9.0f,  0.5f,  0.5f, 9.0f, 1.0f,
			9.0f,  0.5f,  0.5f, 9.0f, 1.0f,
			-9.0f,  0.5f,  0.5f, 0.0f, 1.0f,
			-9.0f, -0.5f,  0.5f, 0.0f, 0.0f,

			-9.0f,  0.5f,  0.5f, 9.0f, 0.0f,
			-9.0f,  0.5f, -0.5f, 9.0f, 1.0f,
			-9.0f, -0.5f, -0.5f, 0.0f, 1.0f,
			-9.0f, -0.5f, -0.5f, 0.0f, 1.0f,
			-9.0f, -0.5f,  0.5f, 0.0f, 0.0f,
			-9.0f,  0.5f,  0.5f, 9.0f, 0.0f,

			9.0f,  0.5f,  0.5f, 9.0f, 0.0f,
			9.0f,  0.5f, -0.5f, 9.0f, 1.0f,
			9.0f, -0.5f, -0.5f, 0.0f, 1.0f,
			9.0f, -0.5f, -0.5f, 0.0f, 1.0f,
			9.0f, -0.5f,  0.5f, 0.0f, 0.0f,
			9.0f,  0.5f,  0.5f, 9.0f, 0.0f,

			-9.0f, -0.5f, -0.5f, 0.0f, 1.0f,
			9.0f, -0.5f, -0.5f, 9.0f, 1.0f,
			9.0f, -0.5f,  0.5f, 9.0f, 0.0f,
			9.0f, -0.5f,  0.5f, 9.0f, 0.0f,
			-9.0f, -0.5f,  0.5f, 0.0f, 0.0f,
			-9.0f, -0.5f, -0.5f, 0.0f, 1.0f,

			-9.0f,  0.5f, -0.5f, 0.0f, 1.0f,
			9.0f,  0.5f, -0.5f, 9.0f, 1.0f,
			9.0f,  0.5f,  0.5f, 9.0f, 0.0f,
			9.0f,  0.5f,  0.5f, 9.0f, 0.0f,
			-9.0f,  0.5f,  0.5f, 0.0f, 0.0f,
			-9.0f,  0.5f, -0.5f, 0.0f, 1.0f
		};
		Box* lBox = new Box();
		lWorld->AddGameObject(lBox, TRUE);
		lBox->Init(Box::eWall, TRUE, Vector3D<float32>(0.0f, 0.0f, -9.0f), Vector3D<float32>(9.0f, 0.4, 0.4f), Vector3D<float32>(0.0f, 0.0f, 0.0f), lWallVertexData, sizeof(lWallVertexData));
		lBox = new Box();
		lWorld->AddGameObject(lBox, TRUE);
		lBox->Init(Box::eWall, TRUE, Vector3D<float32>(0.0f, 0.0f, 9.0f), Vector3D<float32>(9.0f, 0.4f, 0.4f), Vector3D<float32>(0.0f, 180.0f, 0.0f), lWallVertexData, sizeof(lWallVertexData));
		lBox = new Box();
		lWorld->AddGameObject(lBox, TRUE);
		lBox->Init(Box::eWall, TRUE, Vector3D<float32>(9.0f, 0.0f, 0.0f), Vector3D<float32>(0.4f, 0.4f, 9.0f), Vector3D<float32>(0.0f, 90.0f, 0.0f), lWallVertexData, sizeof(lWallVertexData));
		lBox = new Box();
		lWorld->AddGameObject(lBox, TRUE);
		lBox->Init(Box::eWall, TRUE, Vector3D<float32>(-9.0f, 0.0f, 0.0f), Vector3D<float32>(0.4f, 0.4f, 9.0f), Vector3D<float32>(0.0f, 270.0f, 0.0f), lWallVertexData, sizeof(lWallVertexData));

		mNextCoinSpawnTime = sys::Time::GetCurrentSec() + Math::Random(1.0f, 3.0f);
		
		graphics::RenderManager::Instance()->SetClearColor(Color(0.2f, 0.2f, 0.2f, 1.0f));

		io::FileSystem::Instance()->ChangeDirectory(".\\audio");
		mMusic = audio::AudioManager::Instance()->CreateSound2D("Game.wav");
		mMusic->Play(audio::eAudioGroups::eMusic, TRUE);
		
		return TRUE;
	}

	void GameState::Release()
	{
		mMusic->Stop();

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

		if (mNextCoinSpawnTime < sys::Time::GetCurrentSec())
		{
			//HACK
			io::FileSystem::Instance()->ChangeDirectory(".\\materials");
			mNextCoinSpawnTime = sys::Time::GetCurrentSec() + Math::Random(3.0f, 7.0f);
			Box* lBox = new Box();
			logic::World::Instance()->AddGameObject(lBox, TRUE);
			lBox->Init(Box::eCoin, TRUE, Vector3D<float32>((Math::Random(1, (int)(sMapSize.mX - 1)) - sMapSize.mX *0.5f), 0.0f, (Math::Random(1, (int)(sMapSize.mY - 1)) - sMapSize.mY*0.5f)), Vector3D<float32>(0.4f, 0.4f, 0.4f), Vector3D<float32>(0.0f, 0.0f, 0.0f), 0, 0);

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
