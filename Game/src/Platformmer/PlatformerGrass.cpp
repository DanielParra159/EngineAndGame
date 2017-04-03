#include "PlatformerGrass.h"
#include "PlatformGameState.h"

#include "Input/InputManager.h"

#include "Logic/World.h"

#include "System/Time.h"

#include "IO/FileSystem.h"

#include "Core/Game.h"
#include "Core/Log.h"

#include "Graphics/RenderManager.h"
#include "Graphics/Material.h"
#include "Graphics/Sprite.h"

#include "Support/Vector3D.h"
#include "Support/Math.h"

namespace game
{
	PlatformerGrass* PlatformerGrass::Instance;

	void PlatformerGrass::Init(BOOL aActive, float32 aX, float32 aY)
	{
		IGameObject::Init(aActive);

		//AddElement(7, 13, -1, 2);
		//AddElement(15, 13, -4, 3);
	}

	void PlatformerGrass::AddElement(float32 aX, float32 aY, float32 aZ, int32 aType)
	{
		io::FileSystem::Instance()->ChangeDirectory(".\\materials");

		graphics::Sprite* lSprite = graphics::RenderManager::Instance()->CreateSprite("Grass.png", graphics::eRGBA);

		TSpriteData* lSpriteData = new TSpriteData();
		lSpriteData->mSprite = lSprite;
		if (aType == 0)
		{
			graphics::Material* lMaterial = graphics::RenderManager::Instance()->LoadMaterial("WindDiffuse");
			lSprite->SetMaterial(lMaterial);
			lMaterial->SetFloat("initialTime", Math::Random(0.0f, 100.0f));
			lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("Grass.png", graphics::eRGBA));
			lMaterial->SetFloat("windForce", 0.05f);
			lSpriteData->mPosition = Vector3D<float32>(aX, aY, aZ);
			lSpriteData->mScale = Vector3D<float32>(2.5f, 2.5f, 1.0f);
		}
		else if (aType == 1) {
			graphics::Material* lMaterial = graphics::RenderManager::Instance()->LoadMaterial("WindDiffuse");
			lSprite->SetMaterial(lMaterial);
			lMaterial->SetFloat("initialTime", Math::Random(0.0f, 100.0f));
			lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("Tree.png", graphics::eRGBA));
			lMaterial->SetFloat("windForce", 0.01f);
			lSpriteData->mPosition = Vector3D<float32>(aX, aY, aZ);
			lSpriteData->mScale = Vector3D<float32>(10.0f, 10.0f, 1.0f);
		}
		else if (aType == 2) {
			lSprite->GetMaterial()->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("Rock.png", graphics::eRGBA));
			lSpriteData->mPosition = Vector3D<float32>(aX, aY, aZ);
			lSpriteData->mScale = Vector3D<float32>(2.0f, 2.0f, 1.0f);
		}
		else if (aType == 3) {
			lSprite->GetMaterial()->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("Tree02.png", graphics::eRGBA));
			lSpriteData->mPosition = Vector3D<float32>(aX, aY, aZ);
			lSpriteData->mScale = Vector3D<float32>(26.0f, 10.0f, 1.0f);
		}
		lSpriteData->mRotation = Vector3D<float32>(0.0f, 180.0f, 180.0f);

		mSprites.push_back(lSpriteData);
	}

	void PlatformerGrass::Update()
	{
		IGameObject::Update();
	}

	void PlatformerGrass::PrepareToRender()
	{
		IGameObject::PrepareToRender();
		LOOP_ITERATOR(std::vector<TSpriteData*>::const_iterator, mSprites, lIterator, lEndElement)
		{
			(*lIterator)->mSprite->PrepareToRender(&(*lIterator)->mPosition, &(*lIterator)->mScale, &(*lIterator)->mRotation);
		}
	}

	void PlatformerGrass::Release()
	{
		IGameObject::Release();
	}

} // namespace game

