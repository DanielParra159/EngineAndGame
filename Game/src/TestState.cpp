#include "TestState.h"

#include "Input\InputManager.h"
#include "Input\IController.h"
#include "Input\KeyboardController.h"
#include "Input\MouseController.h"
#include "Input\InputAction.h"

#include "Graphics\RenderManager.h"
#include "Graphics\Mesh.h"
#include "Graphics\Material.h"
#include "Graphics\Camera.h"

#include "UI\MenuManager.h"
#include "UI\Menu.h"

#include "Core\Log.h"
#include "Core\Game.h"

#include "Audio\AudioManager.h"
#include "Audio\Sound2D.h"

#include "Support\Vector3D.h"

#include "Defs.h"

namespace game
{
	BOOL TestState::Init()
	{
		graphics::RenderManager::Instance()->SetRenderCamera(
		graphics::RenderManager::Instance()->CreatePerspectiveCamera(&Vector3D<float32>(2.5f, 0.5f, 2.0f),
																	 &Vector3D<float32>(), 
																	 &Vector3D<float32>(0.0f, 0.0f, 1.0f),
																	 45.0f, 800.0f / 600.0f, 1.0f, 10.0f));

		mMesh = graphics::RenderManager::Instance()->LoadMesh("Prueba");
		mMesh2 = graphics::RenderManager::Instance()->LoadMesh("Prueba2");
		mMesh2->GetMaterial()->SetColor(&Color(1.0f, 0, 0, 1.0f));
		mMesh2->GetMaterial()->SetTextureId(graphics::RenderManager::Instance()->LoadTexture("sample2.png"));

		return TRUE;
	}

	void TestState::Release()
	{
		ui::MenuManager::Instance()->RemoveMenu(mMenu);
		mMenu = 0;
	}

	BOOL TestState::Update()
	{
		return TRUE;
	}

	void TestState::Render()
	{
		graphics::RenderManager::Instance()->BeginRender();
		ui::MenuManager::Instance()->Render();
		mMesh->Render(&Vector3D<float32>());

		mMesh2->Render(&Vector3D<float32>(1,0,0));
		graphics::RenderManager::Instance()->EndRender();
	}

} // namespace game