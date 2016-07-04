#include "Graphics\Sprite.h"
#include "Graphics\TextureManager.h"

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

	void Sprite::Render(SDL_Renderer* aRenderer, const Vector2D<>* aPosition)
	{
		Render(aRenderer, aPosition->GetX(), aPosition->GetY());
	}

	void Sprite::Render(SDL_Renderer* aRenderer, int32 aX, int32 aY)
	{
		SDL_Rect srcRect;
		SDL_Rect destRect;
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = destRect.w = mSize.GetX();

		srcRect.h = destRect.h = mSize.GetY();
		destRect.x = aX;
		destRect.y = aY;
		SDL_RenderCopyEx(aRenderer, mTexture->GetTextureData(), &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
	}

	void Sprite::SetSize(const Vector2D<int32>& aSize)
	{
		mSize = aSize;
	}
	void Sprite::SetSize(uint32 aX, uint32 aY)
	{
		mSize.SetX(aX);
		mSize.SetY(aY);
	}
} // namespace graphics