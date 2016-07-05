#include "Logic\World.h"
#include "Logic\WorldCell.h"

#include "Defs.h"

#include "Graphics\Sprite.h"
#include "Graphics\RenderManager.h"

#include "System\Time.h"

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
		for (uint32 i = 0; i < lNumCells; ++i)
		{
			mWorldCells[i] = new WorldCell();
		}
		mWorldCells[12]->mType = 1;

		mSpriteCells = new graphics::Sprite*[mSpriteCellTypes];

		mSpriteCells[0] = graphics::RenderManager::Instance()->CreateSprite("assets/prueba.png");
		mSpriteCells[0]->SetSize(0, 0, 400, 400);
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
				mSpriteCells[i]->Release();
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
					lCell->mType = 0;
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
			if (lCell->mType == 1)
			{
				mSpriteCells[0]->Render(10, 10);
			}
		}
	}
} // namespace logic