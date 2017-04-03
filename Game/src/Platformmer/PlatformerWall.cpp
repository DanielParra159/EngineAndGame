#include "PlatformerWall.h"
#include "PlatformerGrass.h"

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

#include "Support/Math.h"

namespace game
{
	void PlatformerWall::LuaInit(float32 aX, float32 aY, float32 aSizeX, float32 aSizeY, int32 aType)
	{
		if (aType == 2)
		{
			Init(TRUE, Vector3D<float32>(aX, aY, -1.0f), Vector3D<float32>(aSizeX, aSizeY, 2.0f), aType);
		}
		else {
			Init(TRUE, Vector3D<float32>(aX, aY, -4.0f), Vector3D<float32>(aSizeX, aSizeY, 8.0f), aType);
		}
	}
	void PlatformerWall::Init(BOOL aActive, const Vector3D<float32> aPosition, const Vector3D<float32> aSize, int32 aType)
	{
		IGameObject::Init(aActive);

		physics::Collider* lBoxCollider;
		graphics::MeshComponent* lMesh;

		Vector3D<float32> lSize = aSize * 0.5f;
		const float32 baseSize = 1.0f;
		Vector2D<float32> lFrontUV (lSize.mX / baseSize, lSize.mY / baseSize);
		/*if (aType == 0)
		{

		}
		else */if (aType == 1)
		{
			lFrontUV.mY = 1.0f;
		}

		const float32 lWallVertexData[] = {
			// X      Y     Z     Nx,    Ny,     Nz,      U     V
			//Back
			-lSize.mX, -lSize.mY, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.28f,
			lSize.mX, -lSize.mY, 0.0f, 0.0f,  0.0f, -1.0f, 1.0f, 0.28f,
			lSize.mX,  lSize.mY, 0.0f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			lSize.mX,  lSize.mY, 0.0f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			-lSize.mX,  lSize.mY, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
			-lSize.mX, -lSize.mY, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.28f,

			//Front
			-lSize.mX, -lSize.mY,  aSize.mZ, 0.0f,  0.0f,  1.0f, 0.0f, lFrontUV.mY,
			lSize.mX, -lSize.mY,  aSize.mZ, 0.0f,  0.0f,  1.0f, lFrontUV.mX, lFrontUV.mY,
			lSize.mX,  lSize.mY,  aSize.mZ, 0.0f,  0.0f,  1.0f, lFrontUV.mX, 0.0f,
			lSize.mX,  lSize.mY,  aSize.mZ, 0.0f,  0.0f,  1.0f, lFrontUV.mX, 0.0f,
			-lSize.mX,  lSize.mY,  aSize.mZ, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
			-lSize.mX, -lSize.mY,  aSize.mZ, 0.0f,  0.0f,  1.0f, 0.0f, lFrontUV.mY,

			//Left
			-lSize.mX,  lSize.mY,  aSize.mZ, -1.0f,  0.0f,  0.0f, lFrontUV.mX, 0.0f,
			-lSize.mX,  lSize.mY, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			-lSize.mX, -lSize.mY, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, lFrontUV.mY,
			-lSize.mX, -lSize.mY, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, lFrontUV.mY,
			-lSize.mX, -lSize.mY,  aSize.mZ, -1.0f,  0.0f,  0.0f, lFrontUV.mX, lFrontUV.mY,
			-lSize.mX,  lSize.mY,  aSize.mZ, -1.0f,  0.0f,  0.0f, lFrontUV.mX, 0.0f,

			// Right
			lSize.mX, -lSize.mY, 0.0f, 1.0f,  0.0f,  0.0f, lFrontUV.mX, lFrontUV.mY,
			lSize.mX,  lSize.mY, 0.0f, 1.0f,  0.0f,  0.0f, lFrontUV.mX, 0.0f,
			lSize.mX,  lSize.mY,  aSize.mZ, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			lSize.mX,  lSize.mY,  aSize.mZ, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			lSize.mX, -lSize.mY,  aSize.mZ, 1.0f,  0.0f,  0.0f, 0.0f, lFrontUV.mY,
			lSize.mX, -lSize.mY, 0.0f, 1.0f,  0.0f,  0.0f, lFrontUV.mX, lFrontUV.mY,

			//Bottom
			-lSize.mX,  -lSize.mY, 0.0f, 0.0f,  -1.0f,  0.0f, 0.0f, 1.0f,
			lSize.mX,  -lSize.mY, 0.0f, 0.0f,  -1.0f,  0.0f, 1.0f, 1.0f,
			lSize.mX,  -lSize.mY,  aSize.mZ, 0.0f,  -1.0f,  0.0f, 1.0f, 0.32f,
			lSize.mX,  -lSize.mY,  aSize.mZ, 0.0f,  -1.0f,  0.0f, 1.0f, 0.32f,
			-lSize.mX,  -lSize.mY,  aSize.mZ, 0.0f,  -1.0f,  0.0f, 0.0f, 0.32f,
			-lSize.mX,  -lSize.mY, 0.0f, 0.0f,  -1.0f,  0.0f, 0.0f, 1.0f,

			//Up
			lSize.mX, lSize.mY,  aSize.mZ, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
			lSize.mX, lSize.mY, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.2f,
			-lSize.mX, lSize.mY, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.2f,
			-lSize.mX, lSize.mY, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.2f,
			-lSize.mX, lSize.mY,  aSize.mZ, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f,
			lSize.mX, lSize.mY,  aSize.mZ, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f
		};

		static int32 lIndex = 0;
		++lIndex;

		io::FileSystem::Instance()->ChangeDirectory(".\\materials");
		lBoxCollider = physics::PhysicsManager::Instance()->CreateBoxCollider(aPosition, Vector3D<float32>(0, 0, 0), lSize, FALSE, (1 << 0), (1 << 1) | (1 << 0), physics::Collider::eStatic, 0.1f);
		std::string lName = "Wall_" + std::to_string(lIndex);
		lMesh = graphics::RenderManager::Instance()->LoadMeshComponentFromVertexArray(lName, lWallVertexData, sizeof(lWallVertexData), 36);
		graphics::Material* lMaterial = graphics::RenderManager::Instance()->LoadMaterial("Test02");
		lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture(aType == 0 ? "Ground01.jpg" : "Ground02.jpg", graphics::eRGB));
		lMesh->SetMaterial(lMaterial);

		AddComponent(lBoxCollider);
		AddComponent(lMesh);
		if (aType == 1) {
			float32 lXOffset = 1.0f;
			float32 lXPosition = mPosition.mX - lSize.mX + lXOffset;
			uint32 i = 0;
			while (lXPosition + 2.3f < mPosition.mX + lSize.mX)
			{
				lXPosition = mPosition.mX - lSize.mX + lXOffset;
				game::PlatformerGrass::Instance->AddElement(lXPosition, mPosition.mY + 2.3f, mPosition.mZ + aSize.mZ + (i % 2 == 0 ? 0.0f : -0.2f), 0);
				game::PlatformerGrass::Instance->AddElement(lXPosition, mPosition.mY + 2.1f, mPosition.mZ + (i % 2 == 1 ? 0.2f : 0.4f), 0);
				if (Math::Random(0, 100) < 5)
					game::PlatformerGrass::Instance->AddElement(lXPosition, mPosition.mY + 2.1f, -1.2, 2);
				lXOffset += 1.2f;
				++i;
			}

			if (lSize.mX > 10 /*&& Math::Random(0, 100) < 100*/)
				game::PlatformerGrass::Instance->AddElement(mPosition.mX, mPosition.mY + 2.1f, -4.0, 3);
		}
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
