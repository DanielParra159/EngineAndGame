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
		Init(TRUE, Vector3D<float32>(aX, aY, 0.0f), Vector3D<float32>(aSizeX, aSizeY, 2.0f));
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
			-lSize.mX, -lSize.mY, -lSize.mZ, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			lSize.mX, -lSize.mY, -lSize.mZ, 0.0f,  0.0f, -1.0f, lSize.mX, 0.0f,
			lSize.mX,  lSize.mY, -lSize.mZ, 0.0f,  0.0f, -1.0f, lSize.mX, lSize.mY,
			lSize.mX,  lSize.mY, -lSize.mZ, 0.0f,  0.0f, -1.0f, lSize.mX, lSize.mY,
			-lSize.mX,  lSize.mY, -lSize.mZ, 0.0f,  0.0f, -1.0f, 0.0f, lSize.mY,
			-lSize.mX, -lSize.mY, -lSize.mZ, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

			//Front
			-lSize.mX, -lSize.mY,  lSize.mZ, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
			lSize.mX, -lSize.mY,  lSize.mZ, 0.0f,  0.0f,  1.0f, lSize.mX, 0.0f,
			lSize.mX,  lSize.mY,  lSize.mZ, 0.0f,  0.0f,  1.0f, lSize.mX, lSize.mY,
			lSize.mX,  lSize.mY,  lSize.mZ, 0.0f,  0.0f,  1.0f, lSize.mX, lSize.mY,
			-lSize.mX,  lSize.mY,  lSize.mZ, 0.0f,  0.0f,  1.0f, 0.0f, lSize.mY,
			-lSize.mX, -lSize.mY,  lSize.mZ, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

			//Left
			-lSize.mX,  lSize.mY,  lSize.mZ, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			-lSize.mX,  lSize.mY, -lSize.mZ, -1.0f,  0.0f,  0.0f, 1.0f, aSize.mY / 2.5f,
			-lSize.mX, -lSize.mY, -lSize.mZ, -1.0f,  0.0f,  0.0f, 0.0f, aSize.mY / 2.5f,
			-lSize.mX, -lSize.mY, -lSize.mZ, -1.0f,  0.0f,  0.0f, 0.0f, aSize.mY / 2.5f,
			-lSize.mX, -lSize.mY,  lSize.mZ, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			-lSize.mX,  lSize.mY,  lSize.mZ, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

			// Right
			lSize.mX,  lSize.mY,  lSize.mZ, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			lSize.mX,  lSize.mY, -lSize.mZ, 1.0f,  0.0f,  0.0f, 1.0f, aSize.mY / 2.5f,
			lSize.mX, -lSize.mY, -lSize.mZ, 1.0f,  0.0f,  0.0f, 0.0f, aSize.mY / 2.5f,
			lSize.mX, -lSize.mY, -lSize.mZ, 1.0f,  0.0f,  0.0f, 0.0f, aSize.mY / 2.5f,
			lSize.mX, -lSize.mY,  lSize.mZ, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			lSize.mX,  lSize.mY,  lSize.mZ, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

			//Bottom
			-lSize.mX, -lSize.mY, -lSize.mZ, 0.0f, -1.0f,  0.0f, 0.0f, lSize.mZ,
			lSize.mX, -lSize.mY, -lSize.mZ, 0.0f, -1.0f,  0.0f, lSize.mX, lSize.mZ,
			lSize.mX, -lSize.mY,  lSize.mZ, 0.0f, -1.0f,  0.0f, lSize.mX, 0.0f,
			lSize.mX, -lSize.mY,  lSize.mZ, 0.0f, -1.0f,  0.0f, lSize.mX, 0.0f,
			-lSize.mX, -lSize.mY,  lSize.mZ, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
			-lSize.mX, -lSize.mY, -lSize.mZ, 0.0f, -1.0f,  0.0f, 0.0f, lSize.mZ,

			//Up
			-lSize.mX,  lSize.mY, -lSize.mZ, 0.0f,  1.0f,  0.0f, 0.0f, lSize.mZ,
			lSize.mX,  lSize.mY, -lSize.mZ, 0.0f,  1.0f,  0.0f, lSize.mX, lSize.mZ,
			lSize.mX,  lSize.mY,  lSize.mZ, 0.0f,  1.0f,  0.0f, lSize.mX, 0.0f,
			lSize.mX,  lSize.mY,  lSize.mZ, 0.0f,  1.0f,  0.0f, lSize.mX, 0.0f,
			-lSize.mX,  lSize.mY,  lSize.mZ, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
			-lSize.mX,  lSize.mY, -lSize.mZ, 0.0f,  1.0f,  0.0f, 0.0f, lSize.mZ
		};

		static int32 lIndex = 0;
		++lIndex;

		io::FileSystem::Instance()->ChangeDirectory(".\\materials");
		b = physics::PhysicsManager::Instance()->CreateBoxCollider(aPosition, Vector3D<float32>(0, 0, 0), lSize, FALSE, (1 << 0), (1 << 1) | (1 << 0), physics::Collider::eStatic, 0.1f);
		std::string lName = "Wall_" + std::to_string(lIndex);
		lMesh = graphics::RenderManager::Instance()->LoadMeshComponentFromVertexArray(lName, lWallVertexData, sizeof(lWallVertexData), 36);
		graphics::Material* lMaterial = graphics::RenderManager::Instance()->LoadMaterial("Test02");
		lMaterial->SetTextureId(graphics::RenderManager::Instance()->LoadTexture("T_BrickTiled.png"));
		lMesh->SetMaterial(lMaterial);

		AddComponent(b);
		AddComponent(lMesh);
	}

	void PlatformerWall::Update()
	{
		IGameObject::Update();
	}

	void PlatformerWall::Render()
	{
		IGameObject::Render();
	}

	void PlatformerWall::Release()
	{
		IGameObject::Release();
	}

} // namespace game
