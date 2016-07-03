#include "Graphics\Sprite.h"

#include <SDL.h>

namespace graphics
{
	Sprite::Sprite(const Vector2D<int32>& aSize, Texture* aTexture) : mSize(aSize), mTexture(aTexture)
	{
		
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::Render(SDL_Renderer* aRenderer, const Vector2D<>* aPosition)
	{
		SDL_Rect srcRect;
		SDL_Rect destRect;
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = destRect.w = mSize.GetX();

		srcRect.h = destRect.h = mSize.GetY();
		destRect.x = aPosition->GetX();
		destRect.y = aPosition->GetY();
		SDL_RenderCopyEx(aRenderer, mTexture->GetTextureData(), &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
	}
} // namespace graphics