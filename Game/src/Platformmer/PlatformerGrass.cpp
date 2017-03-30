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
	void PlatformerGrass::Init(BOOL aActive, float32 aX, float32 aY)
	{
		IGameObject::Init(aActive);

		io::FileSystem::Instance()->ChangeDirectory(".\\materials");

		graphics::Sprite* lSprite = graphics::RenderManager::Instance()->CreateSprite("Grass.png", graphics::eRGBA);
		graphics::Material* lMaterial = graphics::RenderManager::Instance()->LoadMaterial("WindDiffuse");
		lSprite->SetMaterial(lMaterial);
		lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("Tree.png", graphics::eRGBA));
		lMaterial->SetFloat("windForce", 0.01f);

		TSpriteData* lSpriteData = new TSpriteData(); 
		lSpriteData->mSprite = lSprite;
		lSpriteData->mPosition = Vector3D<float32>(11.0f, 10.0f, 1.5f);
		lSpriteData->mScale = Vector3D<float32>(10.0f, 10.0f, 1.0f);

		mSprites.push_back(lSpriteData);

		
		lSprite = graphics::RenderManager::Instance()->CreateSprite("Grass.png", graphics::eRGBA);
		lMaterial = graphics::RenderManager::Instance()->LoadMaterial("WindDiffuse");
		lSprite->SetMaterial(lMaterial);
		lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture("Tree.png", graphics::eRGBA));
		lMaterial->SetFloat("windForce", 0.01f);

		lSpriteData = new TSpriteData();
		lSpriteData->mSprite = lSprite;
		lSpriteData->mPosition = Vector3D<float32>(18.0f, 16.0f, -1.5f);
		lSpriteData->mScale = Vector3D<float32>(10.0f, 10.0f, 1.0f);

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

