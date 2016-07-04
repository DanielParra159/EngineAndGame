#include "Graphics\RenderManager.h"
#include "Graphics\Texture.h"

#include <SDL.h>
namespace graphics
{
	RenderManager* RenderManager::sInstance = 0;

	RenderManager* RenderManager::Instance()
	{
		if (RenderManager::sInstance == 0)
		{
			RenderManager::sInstance = new RenderManager();
			return RenderManager::sInstance;
		}
		return RenderManager::sInstance;
	}

	void RenderManager::Init(SDL_Renderer *aRenderer)
	{
		mRenderer = aRenderer;
	}

	void RenderManager::Release()
	{

	}

	void RenderManager::RenderTexture(const Texture* aTexture, const Rect<int32> &aSrcRect, const Vector2D<int32> &aPosition, float64 aAngle)
	{
		RenderTexture(aTexture, aSrcRect, aPosition.GetX(), aPosition.GetY(), aAngle);
	}
	void RenderManager::RenderTexture(const Texture* aTexture, const Rect<int32> &aSrcRect, int32 aX, int32 aY, float64 aAngle)
	{
		SDL_Rect srcRect;
		SDL_Rect destRect;
		srcRect.x = aSrcRect.GetX();
		srcRect.y = aSrcRect.GetY();
		srcRect.w = destRect.w = aSrcRect.GetW();

		srcRect.h = destRect.h = aSrcRect.GetH();
		destRect.x = aX;
		destRect.y = aY;
		SDL_RenderCopyEx(mRenderer, aTexture->GetTextureData(), &srcRect, &destRect, aAngle, 0, SDL_FLIP_NONE);
	}

} // namespace graphics

