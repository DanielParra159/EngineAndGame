#include "BoxButton.h"

#include "Core/Game.h"
#include "Core/Log.h"

#include "Logic/World.h"

#include "Physics/PhysicsManager.h"
#include "Physics/Collider.h"

#include "Graphics/RenderManager.h"
#include "Graphics/MeshComponent.h"
#include "Graphics/SpriteComponent.h"
#include "Graphics/Material.h"

#include "Audio/AudioManager.h"
#include "Audio/Sound2D.h"

#include "IO/FileSystem.h"

namespace game
{
	void BoxButton::Init(const Vector3D<float32> aPosition, int32 aId)
	{
		IGameObject::Init(TRUE);

		graphics::SpriteComponent* lSprite;

		/*const float32 lVertexData[] = {
			// X      Y     Z     Nx    Ny     Nz    U     V
			//Front
			-1.5f, -1.5f,  0.0f, 0.0f ,0.0f, 1.0f, 0.0f, 1.0f,
			1.5f, -1.5f,  0.0f, 0.0f ,0.0f, 1.0f, 1.0f, 1.0f,
			1.5f,  1.5f,  0.0f, 0.0f ,0.0f, 1.0f, 1.0f, 0.0f,
			1.5f,  1.5f,  0.0f, 0.0f ,0.0f, 1.0f, 1.0f, 0.0f,
			-1.5f,  1.5f,  0.0f, 0.0f ,0.0f, 1.0f, 0.0f, 0.0f,
			-1.5f, -1.5f,  0.0f, 0.0f ,0.0f, 1.0f, 0.0f, 1.0f
		};*/

		io::FileSystem::Instance()->ChangeDirectory(".\\materials");
		graphics::Material* lMaterial = graphics::RenderManager::Instance()->LoadMaterial("Test01");
		//lMesh = graphics::RenderManager::Instance()->CreateSpriteComponent("Menu1.png", graphics::eRGBA);
		//lMesh = graphics::RenderManager::Instance()->LoadMeshComponentFromVertexArray("BoxMenu", lVertexData, sizeof(lVertexData), 6);
		if (aId == 0)
		{
			lSprite = graphics::RenderManager::Instance()->CreateSpriteComponent("Menu1.png", graphics::eRGBA);
			lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("Menu1.png", graphics::eRGBA));
		}
		else if (aId == 1)
		{
			lSprite = graphics::RenderManager::Instance()->CreateSpriteComponent("Menu2.png", graphics::eRGBA);
			lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("Menu2.png", graphics::eRGBA));
		}
		else
		{
			lSprite = graphics::RenderManager::Instance()->CreateSpriteComponent("Menu3.png", graphics::eRGBA);
			lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("Menu3.png", graphics::eRGBA));
		}
		lSprite->SetMaterial(lMaterial);
		AddComponent((logic::IComponent*)lSprite);
		mPosition = aPosition;
		mScale.mX = 3.0f;
		mScale.mY = 3.0f;
	}

	void BoxButton::Update()
	{
		IGameObject::Update();
	}

	void BoxButton::PrepareToRender()
	{
		IGameObject::PrepareToRender();
	}

	void BoxButton::Release()
	{
		IGameObject::Release();
	}

} // namespace game
