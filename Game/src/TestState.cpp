#include "TestState.h"

#include "Input/InputManager.h"
#include "Input/IController.h"
#include "Input/KeyboardController.h"
#include "Input/MouseController.h"
#include "Input/InputAction.h"

#include "Graphics/RenderManager.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"
#include "Graphics/Light.h"

#include "UI/MenuManager.h"
#include "UI/Menu.h"

#include "Core/Log.h"
#include "Core/Game.h"

#include "Audio/AudioManager.h"
#include "Audio/Sound2D.h"
#include "Support/Math.h"

#include "Support/Vector3D.h"

#include "IO/FileSystem.h"


#include "System/Time.h"

#include "Defs.h"

namespace game
{
	BOOL TestState::Init()
	{
		graphics::RenderManager::Instance()->SetRenderCamera(
		graphics::RenderManager::Instance()->CreatePerspectiveCamera(Vector3D<float32>(0.0f, 4.2f, 2.0f),
																	 Vector3D<float32>(0.0f, 0.0f, -2.0f), 
																	 Vector3D<float32>(0.0f, 0.0f, -1.0f),
																	 75.0f, 800.0f / 600.0f, 1.0f, 1000.0f));


		io::FileSystem::Instance()->ChangeDirectory("materials");
		mMesh = graphics::RenderManager::Instance()->LoadMeshFromFile("Prueba");
		mMesh2 = graphics::RenderManager::Instance()->LoadMeshFromFile("Prueba2");
		mMesh2->GetMaterial()->SetColor(&Color(1.0f, 0, 0, 1.0f));
		mMesh2->GetMaterial()->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("sample2.png", graphics::eRGB));

		graphics::RenderManager::Instance()->CreateMainLight(Vector3D<float32>(0.0f, 8.0f, 4.0f));
		return TRUE;
	}

	void TestState::Release()
	{
		ui::MenuManager::Instance()->RemoveMenu(mMenu);
		mMenu = 0;
		graphics::RenderManager::Instance()->RemoveMainLight();
	}

	BOOL TestState::Update()
	{
		graphics::Light* lMainLight = graphics::RenderManager::Instance()->GetMainLight();

		lMainLight->SetPosition(Vector3D<float32>(20.0f + 25.0f * Math::Cosf(sys::Time::GetCurrentSec() * 0.8f), 8.0f, 4.0f));

		return TRUE;
	}

	void TestState::Render()
	{
		graphics::RenderManager::Instance()->BeginRender();
		ui::MenuManager::Instance()->Render();
		mMesh->PrepareToRender(&Vector3D<float32>(0, 0, -1));
		mMesh->PrepareToRender(&Vector3D<float32>(0, -1, -1), &Vector3D<float32>(2, 2, 2), &Vector3D<float32>(0, 45, 0));

		mMesh2->PrepareToRender(&Vector3D<float32>(1,0,0));
		graphics::RenderManager::Instance()->EndRender();
	}

} // namespace game
