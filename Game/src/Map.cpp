#include "Map.h"

#include "Graphics\RenderManager.h"
#include "Graphics\Mesh.h"
#include "Graphics\Material.h"
#include "Graphics\Camera.h"

#include "Support\Vector3D.h"

#include "IO\FileSystem.h"

#include "Physics/PhysicsManager.h"
#include "Physics/Collider.h"

namespace game
{
	void Map::Init(BOOL aActive)
	{
		IGameObject::Init(aActive);

		io::FileSystem::Instance()->ChangeDirectory(".\\materials");

		const float32 lGroundVertexData[] = {
			// X      Y     Z     Nx,    Ny,     Nz,      U     V
			//Back
			-9.0f, -0.5f, -9.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			9.0f, -0.5f, -9.0f, 0.0f,  0.0f, -1.0f, 9.0f, 0.0f,
			9.0f,  0.5f, -9.0f, 0.0f,  0.0f, -1.0f, 9.0f, 0.5f,
			9.0f,  0.5f, -9.0f, 0.0f,  0.0f, -1.0f, 9.0f, 0.5f,
			-9.0f,  0.5f, -9.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.5f,
			-9.0f, -0.5f, -9.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

			//Front
			-9.0f, -0.5f,  9.0f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
			9.0f, -0.5f,  9.0f, 0.0f,  0.0f,  1.0f, 9.0f, 0.0f,
			9.0f,  0.5f,  9.0f, 0.0f,  0.0f,  1.0f, 9.0f, 0.5f,
			9.0f,  0.5f,  9.0f, 0.0f,  0.0f,  1.0f, 9.0f, 0.5f,
			-9.0f,  0.5f,  9.0f, 0.0f,  0.0f,  1.0f, 0.0f, 0.5f,
			-9.0f, -0.5f,  9.0f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

			//Left
			-9.0f,  0.5f,  9.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			-9.0f,  0.5f, -9.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			-9.0f, -0.5f, -9.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			-9.0f, -0.5f, -9.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			-9.0f, -0.5f,  9.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			-9.0f,  0.5f,  9.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

			// Right
			9.0f, -0.5f, -9.0f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			9.0f,  0.5f, -9.0f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			9.0f,  0.5f,  9.0f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			9.0f,  0.5f,  9.0f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			9.0f, -0.5f,  9.0f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			9.0f, -0.5f, -9.0f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

			//Bottom
			-9.0f,  -0.5f, -9.0f, 0.0f,  -1.0f,  0.0f, 0.0f, 9.0f,
			9.0f,  -0.5f, -9.0f, 0.0f,  -1.0f,  0.0f, 9.0f, 9.0f,
			9.0f,  -0.5f,  9.0f, 0.0f,  -1.0f,  0.0f, 9.0f, 0.0f,
			9.0f,  -0.5f,  9.0f, 0.0f,  -1.0f,  0.0f, 9.0f, 0.0f,
			-9.0f,  -0.5f,  9.0f, 0.0f,  -1.0f,  0.0f, 0.0f, 0.0f,
			-9.0f,  -0.5f, -9.0f, 0.0f,  -1.0f,  0.0f, 0.0f, 9.0f,

			//Up
			9.0f, 0.5f,  9.0f, 0.0f, 1.0f,  0.0f, 9.0f, 0.0f,
			9.0f, 0.5f, -9.0f, 0.0f, 1.0f,  0.0f, 9.0f, 9.0f,
			-9.0f, 0.5f, -9.0f, 0.0f, 1.0f,  0.0f, 0.0f, 9.0f,
			-9.0f, 0.5f, -9.0f, 0.0f, 1.0f,  0.0f, 0.0f, 9.0f,
			-9.0f, 0.5f,  9.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f,
			9.0f, 0.5f,  9.0f, 0.0f, 1.0f,  0.0f, 9.0f, 0.0f
		};

		
		
		mGround = graphics::RenderManager::Instance()->LoadMeshFromVertexArray("Ground", lGroundVertexData, sizeof(lGroundVertexData), 36);
		//mGround = graphics::RenderManager::Instance()->LoadMeshFromFile("Prueba");
		mGround->GetMaterial()->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("T_Grass.jpg", graphics::eRGB));
		//mWall = graphics::RenderManager::Instance()->LoadMeshFromFile("Prueba2");
		//mWall = graphics::RenderManager::Instance()->LoadMeshFromVertexArray("Wall", lWallVertexData, sizeof(lWallVertexData), 36);
		//mWall->GetMaterial()->SetTextureId(graphics::RenderManager::Instance()->LoadTexture("T_Bricks.png"));

		physics::Collider* c = physics::PhysicsManager::Instance()->CreatePlaneCollider(Vector3D<float32>(0, 0, 0), Vector3D<float32>(0, 1, 0), (1 << 1), (1 << 0)); 
		AddComponent(c);
	}

	void Map::Update()
	{

	}

	void Map::PrepareToRender()
	{
		mGround->PrepareToRender(&Vector3D<float32>(0, -1, 0));

		
		/*mWall->Render(&Vector3D<float32>(0.0f, 0, -9.0f));
		mWall->Render(&Vector3D<float32>(9.0f, 0, 0.0f), &Vector3D<float32>::one, &Vector3D<float32>(0.0f, 90.0f, 0.0f));
		mWall->Render(&Vector3D<float32>(-9.0f, 0, 0.0f), &Vector3D<float32>::one, &Vector3D<float32>(0.0f, -90.0f, 0.0f));
		mWall->Render(&Vector3D<float32>(0.0f, 0, 9.0f));*/
		
	}

	void Map::Release()
	{
		IGameObject::Release();
		graphics::RenderManager::Instance()->UnloadMesh(mGround, FALSE);
		//graphics::RenderManager::Instance()->UnloadMesh(mWall);
	}
} // namespace game

