#include "Logic\World.h"
#include "Logic\WorldCell.h"

#include "Defs.h"

#include "Graphics\Sprite.h"
#include "Graphics\RenderManager.h"

#include "System\Time.h"
#include "Core\Log.h"

namespace logic
{

	World* World::sInstance = 0;

	World* World::Instance()
	{
		if (World::sInstance == 0)
		{
			World::sInstance = new World();
			return World::sInstance;
		}
		return World::sInstance;
	}

	void World::Init(uint32 aWidth, uint32 aHeight)
	{
		mWidth = aWidth;
		mHeight = aHeight;

		mWorldCells = new WorldCell*[aWidth *aHeight];
		uint32 lNumCells = mWidth * mHeight;
		//@TODO create here the cells only to test
		for (uint32 i = 0; i < lNumCells; ++i)
		{
			mWorldCells[i] = new WorldCell();
			mWorldCells[i]->mType = 2;
		}

		mSpriteCells = new graphics::Sprite*[mSpriteCellTypes];

		mSpriteCells[0] = graphics::RenderManager::Instance()->CreateSprite("assets/Tiles.png");
		mSpriteCells[0]->SetTextureSize(0, 32 * 2, 32, 32);
		mSpriteCells[1] = graphics::RenderManager::Instance()->CreateSprite("assets/Tiles.png");
		mSpriteCells[1]->SetTextureSize(0, 32 * 3, 32, 32);
		mSpriteCells[2] = graphics::RenderManager::Instance()->CreateSprite("assets/Tiles.png");
		mSpriteCells[2]->SetTextureSize(32 * 8, 32 * 2, 32, 32);
		mSpriteCells[3] = graphics::RenderManager::Instance()->CreateSprite("assets/snake-graphics.png");
		mSpriteCells[3]->SetTextureSize(32 * 4, 32 * 0, 32, 32);
		mSpriteCells[4] = graphics::RenderManager::Instance()->CreateSprite("assets/snake-graphics.png");
		mSpriteCells[4]->SetTextureSize(32 * 4, 32 * 2, 32, 32);
		mSpriteCells[5] = graphics::RenderManager::Instance()->CreateSprite("assets/snake-graphics.png");
		mSpriteCells[5]->SetTextureSize(32 * 0, 32 * 3, 32, 32);
	}

	void World::Release()
	{
		if (mWorldCells)
		{
			delete[](mWorldCells);
			mWorldCells = 0;
		}
		if (mSpriteCells)
		{
			for (uint32 i = 0; i < mSpriteCellTypes; ++i)
			{
				graphics::RenderManager::Instance()->DeleteSprite(mSpriteCells[i]);
			}
			delete[](mSpriteCells);
			mSpriteCells = 0;
		}
	}

	void World::Update()
	{
		uint32 lNumCells = mWidth * mHeight;
		for (uint32 i = 0; i<lNumCells; ++i)
		{
			WorldCell* lCell = mWorldCells[i];
			if (lCell->mLife > 0.0f)
			{
				lCell->mLife -= sys::Time::GetDeltaSec();
				if (lCell->mLife <= 0.0f)
				{
					lCell->mLife = 0;
					lCell->mType = 2;
				}
			}
		}
	}

	void World::Render()
	{
		uint32 lNumCells = mWidth * mHeight;
		for (uint32 i = 0; i < lNumCells; ++i)
		{
			WorldCell* lCell = mWorldCells[i];

			mSpriteCells[lCell->mType]->SetAngle(lCell->mAngle);
			mSpriteCells[lCell->mType]->Render((i % mWidth)*32, (i/ mWidth)*32);

		}
	}

	void World::SetCell(uint32 aX, uint32 aY, float32 aLife) 
	{ 
		mWorldCells[(aY*mWidth) + aX]->mLife = aLife;
	}
	void World::SetCell(uint32 aX, uint32 aY, uint32 aType) 
	{ 
		mWorldCells[(aY*mWidth) + aX]->mType = aType;
	}
	void World::SetCell(uint32 aX, uint32 aY, float32 aLife, uint32 aType) 
	{ 
		mWorldCells[(aY*mWidth) + aX]->mType = aType;
		mWorldCells[(aY*mWidth) + aX]->mLife = aLife;
	}
	void World::SetCellAngle(uint32 aX, uint32 aY, float64 aAngle)
	{
		mWorldCells[(aY*mWidth) + aX]->mAngle = aAngle;
	}
} // namespace logic