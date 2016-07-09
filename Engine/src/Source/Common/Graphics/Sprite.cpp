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
		RenderManager::Instance()->UnloadTexture(mTextureId);
	}

	void Sprite::Render(const Vector2D<>* aPosition)
	{
		Render(aPosition->mX, aPosition->mY);
	}
	void Sprite::Render(const Vector2D<>* aPosition, const Vector2D<>* aSize)
	{
		Render(aPosition->mX, aPosition->mY, aSize->mX, aSize->mY);
	}
	
	void Sprite::Render(int32 aX, int32 aY)
	{
		RenderManager::Instance()->RenderTexture(mTextureId, mTextureSize, aX, aY, mTextureSize.mW, mTextureSize.mH, mAngle);
	}
	void Sprite::Render(int32 aX, int32 aY, int32 aW, int32 aH)
	{
		RenderManager::Instance()->RenderTexture(mTextureId, mTextureSize, aX, aY, aW, aH, mAngle);
	}

	void Sprite::SetTextureSize(const Rect<int32>& aTextureSize)
	{
		mTextureSize = aTextureSize;
	}
	void Sprite::SetTextureSize(uint32 aX, uint32 aY, uint32 aW, uint32 aH)
	{
		mTextureSize.mX = aX;
		mTextureSize.mY = aY;
		mTextureSize.mW = aW;
		mTextureSize.mH = aH;
	}

	void Sprite::SetAngle(float64 aAngle)
	{
		mAngle = aAngle;
	}
} // namespace graphics