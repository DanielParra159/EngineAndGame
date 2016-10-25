#include "PlatformerProjectile.h"

#include "Core/Game.h"
#include "Core/Log.h"

#include "Logic/World.h"

#include "System/Time.h"

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
	void PlatformerProjectile::Init(const Vector3D<float32> aPosition, const Vector3D<float32> aDirection, BOOL aPlayerProjectile)
	{
		IGameObject::Init(TRUE);

		physics::Collider* lCollider;
		graphics::MeshComponent* lMesh;

		static uint32 lIndex = 0;
		++lIndex;

		io::FileSystem::Instance()->ChangeDirectory(".\\materials");
		uint32 lCollisionLayerMask = aPlayerProjectile ? (1 << 0) : (1 << 1) | (1 << 0);
		lCollider = physics::PhysicsManager::Instance()->CreateBoxCollider(aPosition, Vector3D<float32>(0, 0, 0), Vector3D<float32>(0.5f, 0.5f, 0.5f), FALSE, (1 << 0), lCollisionLayerMask, physics::Collider::eDynamic, 0.1f);
		lMesh = graphics::RenderManager::Instance()->LoadMeshComponentFromFile("Sphere.obj");
		lMesh->GetMaterial()->SetTextureId(graphics::RenderManager::Instance()->LoadTexture("T_BrickTiled.png"));
		lCollider->SetOnTriggerEnterCallback(physics::Collider::eCollisionEnter);

		AddComponent(lCollider);
		lCollider->AddForce(aDirection * 3000.0f);
		AddComponent(lMesh);

		mLifeTime = sys::Time::GetCurrentSec() + 1.0f;
	}

	void PlatformerProjectile::Update()
	{
		IGameObject::Update();
		if (mLifeTime < sys::Time::GetCurrentSec())
			logic::World::Instance()->RemoveGameObject(this);
	}

	void PlatformerProjectile::Render()
	{
		IGameObject::Render();
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
