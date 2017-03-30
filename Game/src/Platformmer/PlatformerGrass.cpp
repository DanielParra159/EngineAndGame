#include "PlatformerGrass.h"
#include "PlatformGameState.h"

#include "Input/InputManager.h"

#include "Logic/World.h"

#include "System/Time.h"

#include "IO/FileSystem.h"

#include "Core/Game.h"
#include "Core/Log.h"

#include "Graphics/RenderManager.h"
#include "Graphics/MeshComponent.h"
#include "Graphics/SpriteComponent.h"
#include "Graphics/SpriteAnimatorComponent.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"
//#include "Graphics/TextRenderer.h"

#include "Support/Vector3D.h"

#include "Physics/PhysicsManager.h"
#include "Physics/Collider.h"
#include "Physics/CapsuleController.h"
namespace game
{
	void PlatformerGrass::Init(BOOL aActive, float32 aX, float32 aY)
	{
		IGameObject::Init(aActive);

		mSprite = graphics::RenderManager::Instance()->CreateSpriteComponent("Grass.png", graphics::eRGBA);
		mSprite->SetMaterial(graphics::RenderManager::Instance()->LoadMaterial("WindDiffuse"));
		mSprite->SetPositionOffset(Vector3D<float32>(11.0f, 6.0f, 0.0f));
		//mSprite->GetMaterial()->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("Grass.png", graphics::eRGBA));
		mSprite->SetFlipX(FALSE);
		AddComponent(mSprite);

		mPosition.mZ = 0.8f;

		mScale.mX = 1.0f * 2.0f;
		mScale.mY = 1.77f * 2.0f;

	}

	void PlatformerGrass::Update()
	{
		IGameObject::Update();
	}

	void PlatformerGrass::Render()
	{
		IGameObject::Render();
	}

	void PlatformerGrass::Release()
	{
		IGameObject::Release();
	}

} // namespace game

