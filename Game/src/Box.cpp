#include "Box.h"

#include "Player.h"
#include "Map.h"
#include "GameState.h"
#include "GameOverState.h"
#include "MenuState.h"

#include "Core/Game.h"
#include "Core/Log.h"

#include "Physics/PhysicsManager.h"
#include "Physics/Collider.h"

#include "Graphics/RenderManager.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"

#include "Audio/AudioManager.h"
#include "Audio/Sound2D.h"

#include "IO/FileSystem.h"

namespace game
{
	void Box::Init(eBoxType aBoxType, BOOL aActive, const Vector3D<float> aPosition, const Vector3D<float> aBoxSize, const Vector3D<float> aRotationOffset, const float32 aWallVertexData[], uint32 aSize)
	{
		IGameObject::Init(aActive);
		mBoxType = aBoxType;
		physics::Collider* b;
		mRotationOffset = aRotationOffset;

		if (aBoxType == eCoin)
		{
			b = physics::PhysicsManager::Instance()->CreateBoxCollider(aPosition, Vector3D<float32>(0, 0, 0), aBoxSize, TRUE, (1 << 0), (1 << 1) | (1 << 0), physics::Collider::eStatic, 0.1f);
			mMesh = graphics::RenderManager::Instance()->LoadMeshFromFile("Coin");
		}
		else {
			b = physics::PhysicsManager::Instance()->CreateBoxCollider(aPosition, Vector3D<float32>(0, 0, 0), aBoxSize, TRUE, (1 << 0), (1 << 1) | (1 << 0), physics::Collider::eStatic, 0.1f);
			mMesh = graphics::RenderManager::Instance()->LoadMeshFromVertexArray("Box", aWallVertexData, aSize, 36);
			mMesh->GetMaterial()->SetTextureId(graphics::RenderManager::Instance()->LoadTexture("T_Bricks.png"));
		}
		b->SetOnTriggerEnterCallback(physics::Collider::eTriggerEnter);
		AddComponent(b);
	}

	void Box::Update()
	{
		IGameObject::Update();
	}

	void Box::Render()
	{
		IGameObject::Render();

		mMesh->Render(&mPosition, &Vector3D<float32>(1,1,1), &(mRotation + mRotationOffset));
	}

	void Box::Release()
	{
		IGameObject::Release();

		graphics::RenderManager::Instance()->UnloadMesh(mMesh);
	}

	void Box::OnTriggerEnter(physics::Collider* other)
	{
		if (mBoxType == eCoin)
		{
			((Player*)other->GetParent())->AddCoin();
			this->SetEnabled(FALSE);
			io::FileSystem::Instance()->ChangeDirectory(".\\audio");
			audio::AudioManager::Instance()->CreateSound2D("Coin.wav")->Play(audio::eAudioGroups::eEffects);
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
