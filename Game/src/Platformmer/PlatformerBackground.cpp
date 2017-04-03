#include "PlatformerBackground.h"

#include "Core/Game.h"
#include "Core/Log.h"

#include "Logic/World.h"

#include "Graphics/RenderManager.h"
#include "Graphics/SpriteComponent.h"
#include "Graphics/Material.h"


#include "IO/FileSystem.h"

namespace game
{
	void PlatformerBackground::Init(BOOL aActive)
	{
		IGameObject::Init(aActive);

		io::FileSystem::Instance()->ChangeDirectory(".\\materials");


		graphics::SpriteComponent* lSprite = graphics::RenderManager::Instance()->CreateSpriteComponent("Background.jpg", graphics::eRGBA);

		AddComponent(lSprite);
		lSprite->SetRotationOffset(Vector3D<float32>(0.0f, 180.0f, 180.0f));

		mPosition.mY = 5.0f;
		mPosition.mZ = -5.0f;

		mScale *= 100.0f;

	}

	void PlatformerBackground::Update()
	{
		IGameObject::Update();
	}

	void PlatformerBackground::PrepareToRender()
	{
		IGameObject::PrepareToRender();
	}

	void PlatformerBackground::Release()
	{
		IGameObject::Release();
	}

} // namespace game
