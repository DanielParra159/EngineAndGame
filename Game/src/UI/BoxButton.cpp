#include "BoxButton.h"

#include "Core/Game.h"
#include "Core/Log.h"

#include "Logic/World.h"

#include "Physics/PhysicsManager.h"
#include "Physics/Collider.h"

#include "Graphics/RenderManager.h"
#include "Graphics/MeshComponent.h"
#include "Graphics/Material.h"

#include "Audio/AudioManager.h"
#include "Audio/Sound2D.h"

#include "IO/FileSystem.h"

namespace game
{
	void BoxButton::Init(const Vector3D<float32> aPosition, int32 aId)
	{
		IGameObject::Init(TRUE);

		graphics::MeshComponent* lMesh;

		const float32 lVertexData[] = {
			// X      Y     Z     U     V
			//Front
			-1.5f, -1.5f,  0.0f, 0.0f, 1.0f,
			1.5f, -1.5f,  0.0f, 1.0f, 1.0f,
			1.5f,  1.5f,  0.0f, 1.0f, 0.0f,
			1.5f,  1.5f,  0.0f, 1.0f, 0.0f,
			-1.5f,  1.5f,  0.0f, 0.0f, 0.0f,
			-1.5f, -1.5f,  0.0f, 0.0f, 1.0f,
		};

		io::FileSystem::Instance()->ChangeDirectory(".\\materials");
		lMesh = graphics::RenderManager::Instance()->LoadMeshComponentFromVertexArray("BoxMenu", lVertexData, sizeof(lVertexData), 6);
		if (aId == 0)
		{
			lMesh->GetMaterial()->SetTextureId(graphics::RenderManager::Instance()->LoadTexture("Menu1.png"));
		}
		else if (aId == 1)
		{
			lMesh->GetMaterial()->SetTextureId(graphics::RenderManager::Instance()->LoadTexture("Menu2.png"));
		}
		else
		{
			lMesh->GetMaterial()->SetTextureId(graphics::RenderManager::Instance()->LoadTexture("Menu3.png"));
		}
		AddComponent(lMesh);
		mPosition = aPosition;
	}

	void BoxButton::Update()
	{
		IGameObject::Update();
	}

	void BoxButton::Render()
	{
		IGameObject::Render();
	}

	void BoxButton::Release()
	{
		IGameObject::Release();
	}

} // namespace game
