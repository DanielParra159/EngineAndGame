#include "PlatformerWall.h"

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
	void PlatformerWall::LuaInit(float32 aX, float32 aY, float32 aSizeX, float32 aSizeY)
	{
		Init(TRUE, Vector3D<float32>(aX, aY, 0.0f), Vector3D<float32>(aSizeX, aSizeY, 8.0f));
	}
	void PlatformerWall::Init(BOOL aActive, const Vector3D<float32> aPosition, const Vector3D<float32> aSize)
	{
		IGameObject::Init(aActive);

		physics::Collider* b;
		graphics::MeshComponent* lMesh;

		Vector3D<float32> lSize = aSize * 0.5f;

		const float32 lWallVertexData[] = {
			// X      Y     Z     Nx,    Ny,     Nz,      U     V
			//Back
			-lSize.mX, -lSize.mY, -lSize.mZ, 0.0f,  0.0f, -1.0f, 0.0f, 0.28f,
			lSize.mX, -lSize.mY, -lSize.mZ, 0.0f,  0.0f, -1.0f, 1.0f, 0.28f,
			lSize.mX,  lSize.mY, -lSize.mZ, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			lSize.mX,  lSize.mY, -lSize.mZ, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			-lSize.mX,  lSize.mY, -lSize.mZ, 0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
			-lSize.mX, -lSize.mY, -lSize.mZ, 0.0f,  0.0f, -1.0f, 0.0f, 0.28f,

			//Front
			-lSize.mX, -lSize.mY,  lSize.mZ, 0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
			lSize.mX, -lSize.mY,  lSize.mZ, 0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
			lSize.mX,  lSize.mY,  lSize.mZ, 0.0f,  0.0f,  1.0f, 1.0f, 0.24f,
			lSize.mX,  lSize.mY,  lSize.mZ, 0.0f,  0.0f,  1.0f, 1.0f, 0.24f,
			-lSize.mX,  lSize.mY,  lSize.mZ, 0.0f,  0.0f,  1.0f, 0.0f, 0.24f,
			-lSize.mX, -lSize.mY,  lSize.mZ, 0.0f,  0.0f,  1.0f, 0.0f, 1.0f,

			//Left
			-lSize.mX,  lSize.mY,  lSize.mZ, -1.0f,  0.0f,  0.0f, 1.0f, 0.24f,
			-lSize.mX,  lSize.mY, -lSize.mZ, -1.0f,  0.0f,  0.0f, 0.0f, 0.24f,
			-lSize.mX, -lSize.mY, -lSize.mZ, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			-lSize.mX, -lSize.mY, -lSize.mZ, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			-lSize.mX, -lSize.mY,  lSize.mZ, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			-lSize.mX,  lSize.mY,  lSize.mZ, -1.0f,  0.0f,  0.0f, 1.0f, 0.24f,

			// Right
			lSize.mX, -lSize.mY, -lSize.mZ, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			lSize.mX,  lSize.mY, -lSize.mZ, 1.0f,  0.0f,  0.0f, 1.0f, 0.24f,
			lSize.mX,  lSize.mY,  lSize.mZ, 1.0f,  0.0f,  0.0f, 0.0f, 0.24f,
			lSize.mX,  lSize.mY,  lSize.mZ, 1.0f,  0.0f,  0.0f, 0.0f, 0.24f,
			lSize.mX, -lSize.mY,  lSize.mZ, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			lSize.mX, -lSize.mY, -lSize.mZ, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f,

			//Bottom
			-lSize.mX,  -lSize.mY, -lSize.mZ, 0.0f,  -1.0f,  0.0f, 0.0f, 1.0f,
			lSize.mX,  -lSize.mY, -lSize.mZ, 0.0f,  -1.0f,  0.0f, 1.0f, 1.0f,
			lSize.mX,  -lSize.mY,  lSize.mZ, 0.0f,  -1.0f,  0.0f, 1.0f, 0.32f,
			lSize.mX,  -lSize.mY,  lSize.mZ, 0.0f,  -1.0f,  0.0f, 1.0f, 0.32f,
			-lSize.mX,  -lSize.mY,  lSize.mZ, 0.0f,  -1.0f,  0.0f, 0.0f, 0.32f,
			-lSize.mX,  -lSize.mY, -lSize.mZ, 0.0f,  -1.0f,  0.0f, 0.0f, 1.0f,

			//Up
			lSize.mX, lSize.mY,  lSize.mZ, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
			lSize.mX, lSize.mY, -lSize.mZ, 0.0f, 1.0f,  0.0f, 1.0f, 0.2f,
			-lSize.mX, lSize.mY, -lSize.mZ, 0.0f, 1.0f,  0.0f, 0.0f, 0.2f,
			-lSize.mX, lSize.mY, -lSize.mZ, 0.0f, 1.0f,  0.0f, 0.0f, 0.2f,
			-lSize.mX, lSize.mY,  lSize.mZ, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f,
			lSize.mX, lSize.mY,  lSize.mZ, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f
		};

		static int32 lIndex = 0;
		++lIndex;

		io::FileSystem::Instance()->ChangeDirectory(".\\materials");
		b = physics::PhysicsManager::Instance()->CreateBoxCollider(aPosition, Vector3D<float32>(0, 0, 0), lSize, FALSE, (1 << 0), (1 << 1) | (1 << 0), physics::Collider::eStatic, 0.1f);
		std::string lName = "Wall_" + std::to_string(lIndex);
		lMesh = graphics::RenderManager::Instance()->LoadMeshComponentFromVertexArray(lName, lWallVertexData, sizeof(lWallVertexData), 36);
		graphics::Material* lMaterial = graphics::RenderManager::Instance()->LoadMaterial("Test02");
		lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("Ground.jpg", graphics::eRGB));
		lMesh->SetMaterial(lMaterial);

		AddComponent(b);
		AddComponent(lMesh);
	}

	void PlatformerWall::Update()
	{
		IGameObject::Update();
	}

	void PlatformerWall::PrepareToRender()
	{
		IGameObject::PrepareToRender();
	}

	void PlatformerWall::Release()
	{
		IGameObject::Release();
	}

} // namespace game
