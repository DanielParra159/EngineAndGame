#include "Graphics\MatrixScene.h"

#include "Defs.h"

#include "Graphics\SceneCell.h"
#include "Graphics\AnimateSprite.h"
#include "Graphics\TextureManager.h"

namespace graphics
{

	MatrixScene::MatrixScene(int32 aId) : IScene(aId)
	{

	}

	void MatrixScene::Init(uint32 aWidth, uint32 aHeight)
	{
		mWidth = aWidth;
		mHeight = aHeight;

		mSceneCells = new SceneCell*[aWidth *aHeight];
		mSpriteCells = new AnimateSprite*[mSpriteCellTypes];

		//mSpriteCells[0] = new AnimateSprite();
	}

	void MatrixScene::Release()
	{

	}

	void MatrixScene::Update()
	{

	}

	void MatrixScene::Render()
	{

	}

	uint32 MatrixScene::GetWith() 
	{
		return mWidth;
	}

	uint32 MatrixScene::GetHeight() 
	{
		return mHeight; 
	}
}