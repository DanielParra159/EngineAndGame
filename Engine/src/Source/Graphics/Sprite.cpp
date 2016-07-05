#include "Graphics\Sprite.h"
#include "Graphics\RenderManager.h"

#include <SDL.h>

namespace graphics
{
	void Sprite::Init(int32 aTextureId)
	{
		mTextureId = aTextureId;
	}

	void Sprite::Release()
	{
		//RenderManager::Instance()->UnloadTexture(mTextureId);
	}

	void Sprite::Render(const Vector2D<>* aPosition)
	{
		Render(aPosition->mX, aPosition->mY);
	}

	void Sprite::Render(int32 aX, int32 aY)
	{
		RenderManager::Instance()->RenderTexture(mTextureId, mSize, aX, aY, mAngle);
	}


	void Sprite::SetSize(const Rect<int32>& aSize)
	{
		mSize = aSize;
	}
	void Sprite::SetSize(uint32 aX, uint32 aY, uint32 aW, uint32 aH)
	{
		mSize.mX = aX;
		mSize.mY = aY;
		mSize.mW = aW;
		mSize.mH = aH;
	}

	void Sprite::SetAngle(float64 aAngle)
	{
		mAngle = aAngle;
	}
} // namespace graphics