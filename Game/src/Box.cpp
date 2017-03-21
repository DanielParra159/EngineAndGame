#include "Box.h"

#include "Player.h"
#include "Map.h"
#include "GameState.h"
#include "GameOverState.h"
#include "MenuState.h"

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
	void Box::Init(eBoxType aBoxType, BOOL aActive, const Vector3D<float32> aPosition, const Vector3D<float32> aBoxSize, const Vector3D<float32> aRotationOffset, const float32 aWallVertexData[], uint32 aSize)
	{
		IGameObject::Init(aActive);
		mBoxType = aBoxType;
		physics::Collider* b;
		graphics::MeshComponent* lMesh;

		if (aBoxType == eCoin)
		{
			b = physics::PhysicsManager::Instance()->CreateBoxCollider(aPosition, Vector3D<float32>(0, 0, 0), aBoxSize, TRUE, (1 << 0), (1 << 1) | (1 << 0), physics::Collider::eStatic, 0.1f);
			lMesh = graphics::RenderManager::Instance()->LoadMeshComponentFromFile("Box.obj");
		}
		else {
			b = physics::PhysicsManager::Instance()->CreateBoxCollider(aPosition, Vector3D<float32>(0, 0, 0), aBoxSize, TRUE, (1 << 0), (1 << 1) | (1 << 0), physics::Collider::eStatic, 0.1f);
			lMesh = graphics::RenderManager::Instance()->LoadMeshComponentFromVertexArray("Box", aWallVertexData, aSize, 36);
			lMesh->GetMaterial()->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("T_Bricks.png", graphics::eRGB));
		}
		b->SetOnTriggerEnterCallback(physics::Collider::eTriggerEnter);
		AddComponent(b);
		lMesh->SetRotationOffset(aRotationOffset);
		AddComponent(lMesh);
	}

	void Box::Update()
	{
		IGameObject::Update();
	}

	void Box::Render()
	{
		IGameObject::Render();
	}

	void Box::Release()
	{
		IGameObject::Release();
	}

	void Box::OnTriggerEnter(physics::Collider* other)
	{
		if (mBoxType == eCoin)
		{
			((Player*)other->GetParent())->AddCoin();
			io::FileSystem::Instance()->ChangeDirectory(".\\audio");
			audio::AudioManager::Instance()->CreateSound2D("Coin.wav")->Play(audio::eAudioGroups::eEffects);
			logic::World::Instance()->RemoveGameObject(this);
		}
		else {
			//HACK
			game::MenuState *lGameState = new game::MenuState();

			core::Game::Instance()->ChangeGameState(lGameState);

			io::FileSystem::Instance()->ChangeDirectory(".\\audio");
			audio::AudioManager::Instance()->CreateSound2D("Die.wav")->Play(audio::eAudioGroups::eEffects);
		}
	}
	
} // namespace game
