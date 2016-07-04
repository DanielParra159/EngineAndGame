#include "Graphics\Sprite.h"
#include "Graphics\TextureManager.h"
#include "Graphics\RenderManager.h"

#include <SDL.h>

namespace graphics
{
	void Sprite::Init(Texture *aTexture)
	{
		mTexture = aTexture;
	}

	void Sprite::Release()
	{
		mTexture->Release();
	}

	void Sprite::Render(const Vector2D<>* aPosition)
	{
		Render(aPosition->GetX(), aPosition->GetY());
	}

	void Sprite::Render(int32 aX, int32 aY)
	{
		RenderManager::Instance()->RenderTexture(mTexture, mSize, aX, aY, mAngle);
	}


	void Sprite::SetSize(const Rect<int32>& aSize)
	{
		mSize = aSize;
	}
	void Sprite::SetSize(uint32 aX, uint32 aY, uint32 aW, uint32 aH)
	{
		mSize.SetX(aX);
		mSize.SetY(aY);
		mSize.SetW(aW);
		mSize.SetH(aH);
	}
	const Rect<int32>* Sprite::GetSize()
	{
		return &mSize;
	}


	void Sprite::SetAngle(float64 aAngle)
	{
		mAngle = aAngle;
	}
	float64 Sprite::GetAngle()
	{
		return mAngle;
	}
} // namespace graphics