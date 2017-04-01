#include "PlatformerProjectile.h"

#include "Core/Game.h"
#include "Core/Log.h"

#include "Logic/World.h"

#include "System/Time.h"

#include "Physics/PhysicsManager.h"
#include "Physics/Collider.h"

#include "Graphics/RenderManager.h"
#include "Graphics/SpriteComponent.h"
#include "Graphics/Material.h"

#include "Audio/AudioManager.h"
#include "Audio/Sound2D.h"

#include "IO/FileSystem.h"

#include "Support/Math.h"

#include "Core/Log.h"

namespace game
{
	void PlatformerProjectile::Init(const Vector3D<float32> aPosition, const Vector3D<float32> aDirection, BOOL aPlayerProjectile)
	{
		IGameObject::Init(TRUE);

		physics::Collider* lCollider;
		graphics::SpriteComponent* lSprite;

		static uint32 lIndex = 0;
		++lIndex;

		io::FileSystem::Instance()->ChangeDirectory(".\\materials");
		uint32 lCollisionLayerMask = aPlayerProjectile ? (1 << 0) : (1 << 1) | (1 << 0);
		lCollider = physics::PhysicsManager::Instance()->CreateBoxCollider(aPosition, Vector3D<float32>(0, 0, 0), Vector3D<float32>(0.5f, 0.5f, 0.5f), FALSE, (1 << 0), lCollisionLayerMask, physics::Collider::eDynamic, 0.1f);
		lSprite = graphics::RenderManager::Instance()->CreateSpriteComponent("Kunai.png", graphics::eRGBA);
		//lSprite->GetMaterial()->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("T_BrickTiled.png", graphics::eRGB));
		lCollider->SetOnTriggerEnterCallback(physics::Collider::eCollisionEnter);
		
		lSprite->SetRotationOffset(Vector3D<float32>(0.0f, 0.0f, Math::Degrees(Math::Atan2f(aDirection.mY, aDirection.mX)) -90.0f));

		mScale.mY = 5.0f * 0.5f;
		mScale.mX = 1.0f * 0.5f;
		AddComponent(lCollider);
		lCollider->AddForce(aDirection * 3000.0f);
		AddComponent(lSprite);

		mLifeTime = sys::Time::GetCurrentSec() + 1.0f;
	}

	void PlatformerProjectile::Update()
	{
		IGameObject::Update();
		if (mLifeTime < sys::Time::GetCurrentSec())
			logic::World::Instance()->RemoveGameObject(this);
	}

	void PlatformerProjectile::PrepareToRender()
	{
		IGameObject::PrepareToRender();
	}

	void PlatformerProjectile::Release()
	{
		IGameObject::Release();
	}

	void PlatformerProjectile::OnCollisionEnter(physics::Collider* other)
	{
		//@TODO: Pool
		logic::World::Instance()->RemoveGameObject(this);
	}
} // namespace game
