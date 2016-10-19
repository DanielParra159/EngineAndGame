#include "Box.h"

#include "Core/Log.h"

#include "Physics/PhysicsManager.h"
#include "Physics/Collider.h"

#include "Graphics/RenderManager.h"
#include "Graphics/Mesh.h"

namespace game
{
	void Box::Init(BOOL aActive, const Vector3D<float> aPosition)
	{
		IGameObject::Init(aActive);
		physics::Collider* b = physics::PhysicsManager::Instance()->CreateBoxCollider(aPosition, Vector3D<float32>(0, 0, 0), Vector3D<float32>(0.5f, 0.5f, 0.5f), FALSE, (1 << 0), (1 << 1) | (1 << 0), physics::Collider::eDynamic, 0.1f);
		AddComponent(b);

		mMesh = graphics::RenderManager::Instance()->LoadMeshFromFile("Prueba");
	}

	void Box::Update()
	{
		IGameObject::Update();
	}

	void Box::Render()
	{
		IGameObject::Render();

		mMesh->Render(&mPosition, &Vector3D<float32>(1,1,1), &mRotation);
	}

	void Box::Release()
	{
		IGameObject::Release();

		graphics::RenderManager::Instance()->UnloadMesh(mMesh);
	}
	
} // namespace game
