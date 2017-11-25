#include "PlatformerCoin.h"

#include "Core/Game.h"
#include "Core/Log.h"

#include "Logic/World.h"

#include "Physics/PhysicsManager.h"
#include "Physics/Collider.h"

#include "Graphics/RenderManager.h"
#include "Graphics/SpriteComponent.h"
#include "Graphics/Material.h"

#include "Audio/AudioManager.h"
#include "Audio/Sound2D.h"

#include "IO/FileSystem.h"

namespace game
{
	void PlatformerCoin::LuaInit(float32 aX, float32 aY, int32 aType)
	{
		Init(TRUE, Vector3D<float32>(aX, aY, 0.0f), Vector3D<float32>(1.0f, 1.0f, 1.0f), aType);
	}
	void PlatformerCoin::Init(BOOL aActive, const Vector3D<float32> aPosition, const Vector3D<float32> aSize, int32 aType)
	{
		IGameObject::Init(aActive);

		io::FileSystem::Instance()->ChangeDirectory(".\\materials");

		physics::Collider* lCollider;
		lCollider = physics::PhysicsManager::Instance()->CreateBoxCollider(aPosition, Vector3D<float32>(0, 0, 0), aSize * 0.5f, TRUE, (1 << 0), (1 << 1) | (1 << 0), physics::Collider::eStatic, 0.1f);

		lCollider->BindPhysicsCallback(physics::Collider::eTriggerEnter, this, &PlatformerCoin::OnTriggerEnter);
		AddComponent(lCollider);

		graphics::SpriteComponent* lSprite = graphics::RenderManager::Instance()->CreateSpriteComponent("Coin.png", graphics::eRGBA);

		AddComponent(lSprite);
		lSprite->SetRotationOffset(Vector3D<float32>(0.0f, 180.0f, 180.0f));

		io::FileSystem::Instance()->ChangeDirectory(".\\audio");
		mSound = audio::AudioManager::Instance()->CreateSound2D("Coin.wav");
	}

	void PlatformerCoin::Update()
	{
		IGameObject::Update();
	}

	void PlatformerCoin::PrepareToRender()
	{
		IGameObject::PrepareToRender();
	}

	void PlatformerCoin::Release()
	{
		IGameObject::Release();
	}

	void PlatformerCoin::OnTriggerEnter(physics::Collider* other)
	{
		mSound->Play(audio::eAudioGroups::eEffects);
		//@TODO: Pool
		logic::World::Instance()->RemoveGameObject(this);
	}

} // namespace game
