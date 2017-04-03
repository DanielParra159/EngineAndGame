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

namespace game
{
	PlatformerGrass* PlatformerGrass::Instance;

	void PlatformerGrass::Init(BOOL aActive, float32 aX, float32 aY)
	{
		IGameObject::Init(aActive);

		//AddElement(8.0f, 16.9f, 3.0f, 1);
		//AddElement(1.0f, 5.3f, 2.0f, 0);
		//AddElement(2.0f, 5.3f, 1.8f, 0);

	}

	void PlatformerGrass::AddElement(float32 aX, float32 aY, float32 aZ, int32 aType)
	{
		io::FileSystem::Instance()->ChangeDirectory(".\\materials");

		graphics::Sprite* lSprite = graphics::RenderManager::Instance()->CreateSprite("Grass.png", graphics::eRGBA);
		graphics::Material* lMaterial = graphics::RenderManager::Instance()->LoadMaterial("WindDiffuse");
		lSprite->SetMaterial(lMaterial);
		lMaterial->SetFloat("initialTime", 1.0f);
		TSpriteData* lSpriteData = new TSpriteData();
		lSpriteData->mSprite = lSprite;
		if (aType == 0)
		{
			lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("Grass.png", graphics::eRGBA));
			lMaterial->SetFloat("windForce", 0.05f);
			lSpriteData->mPosition = Vector3D<float32>(aX, aY, aZ);
			lSpriteData->mScale = Vector3D<float32>(2.5f, 2.5f, 1.0f);
		}
		else if (aType == 1) {
			lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("Tree.png", graphics::eRGBA));
			lMaterial->SetFloat("windForce", 0.01f);
			lSpriteData->mPosition = Vector3D<float32>(aX, aY, aZ);
			lSpriteData->mScale = Vector3D<float32>(10.0f, 10.0f, 1.0f);
		}

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
			(*lIterator)->mSprite->PrepareToRender(&(*lIterator)->mPosition, &(*lIterator)->mScale);
		}
	}

	void PlatformerGrass::Release()
	{
		IGameObject::Release();
	}

} // namespace game

