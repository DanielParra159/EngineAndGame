#include "Map.h"

#include "Graphics\RenderManager.h"
#include "Graphics\Mesh.h"
#include "Graphics\Material.h"
#include "Graphics\Camera.h"

#include "Support\Vector3D.h"

#include "IO\FileSystem.h"

namespace game
{
	void Map::Init(BOOL aActive)
	{
		IGameObject::Init(aActive);

		io::FileSystem::Instance()->ChangeDirectory("materials");
		mGround = graphics::RenderManager::Instance()->LoadMesh("Prueba");
		mWall = graphics::RenderManager::Instance()->LoadMesh("Prueba2");
		mWall->GetMaterial()->SetColor(&Color(1.0f, 0, 0, 1.0f));
		mWall->GetMaterial()->SetTextureId(graphics::RenderManager::Instance()->LoadTexture("sample2.png"));

	}

	void Map::Update()
	{

	}

	void Map::Render()
	{
		mGround->Render(&Vector3D<float32>(0, -1, 0), &Vector3D<float32>(18, 1, 18), &Vector3D<float32>(0, 0, 0));

		mWall->Render(&Vector3D<float32>(-8.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(-7.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(-6.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(-5.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(-4.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(-3.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(-2.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(-1.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(-0.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(0.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(1.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(2.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(3.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(4.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(5.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(6.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(7.5f, 0, -8.5f));
		mWall->Render(&Vector3D<float32>(8.5f, 0, -8.5f));
	}

	void Map::Release()
	{

	}
} // namespace game

