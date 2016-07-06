#include "Graphics\RenderManager.h"
#include "Graphics\Sprite.h"

#include "Types\Color.h"

#include "Core\Log.h"

#include "Logic\World.h"

#include <SDL.h>
#include <SDL_image.h>

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

	BOOL RenderManager::Init(const int8* aWindowsTitle, const Vector2D<uint32> &aWindowsSize, const Vector2D<uint32> &aWindowsPosition, const Color& aRenderDrawColor, BOOL aFullscreen)
	{
		mWindow = SDL_CreateWindow(aWindowsTitle,
								   aWindowsPosition.mX, aWindowsPosition.mY,
								   aWindowsSize.mX, aWindowsSize.mY,
								   aFullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);

		if (mWindow == 0)
			return FALSE;

		mRenderer = SDL_CreateRenderer(mWindow, -1, 0);

		if (mRenderer == 0)
			return FALSE;

		SDL_SetRenderDrawColor(mRenderer,
							   aRenderDrawColor.mR,
							   aRenderDrawColor.mG,
							   aRenderDrawColor.mB,
							   aRenderDrawColor.mA);

		return TRUE;
	}

	void RenderManager::Release()
	{
		TLoadedTextures::const_iterator lIterator;
		TLoadedTextures::const_iterator lEndElement = mLoadedTextures.end();
		for (lIterator = mLoadedTextures.begin(); lIterator != lEndElement; ++lIterator)
		{
			SDL_DestroyTexture(*lIterator);
		}
		mLoadedTextures.clear();
		mTexturesIds.clear();

		SDL_DestroyWindow(mWindow);
		SDL_DestroyRenderer(mRenderer);
	}

	void RenderManager::Render()
	{
		SDL_RenderClear(mRenderer);

		logic::World::Instance()->Render();

		SDL_RenderPresent(mRenderer);
	}

	void RenderManager::RenderTexture(uint32 aId, const Rect<int32> &aSrcRect, const Vector2D<int32> &aPosition, float64 aAngle)
	{
		RenderTexture(aId, aSrcRect, aPosition.mX, aPosition.mY, aAngle);
	}
	void RenderManager::RenderTexture(uint32 aId, const Rect<int32> &aSrcRect, int32 aX, int32 aY, float64 aAngle)
	{
		SDL_Rect srcRect;
		SDL_Rect destRect;
		srcRect.x = aSrcRect.mX;
		srcRect.y = aSrcRect.mY;
		srcRect.w = destRect.w = aSrcRect.mW;

		srcRect.h = destRect.h = aSrcRect.mH;
		destRect.x = aX;
		destRect.y = aY;
		
		SDL_RenderCopyEx(mRenderer, mLoadedTextures[aId], &srcRect, &destRect, aAngle, 0, SDL_FLIP_NONE);
	}

	void RenderManager::UnloadTexture(int32 aId)
	{
		TTexturesIds::const_iterator lIterator = mTexturesIds.begin();
		TTexturesIds::const_iterator lIteratorEnd = mTexturesIds.end();
		while (lIterator != lIteratorEnd && lIterator->second->mId != aId)
		{
			++lIterator;
		}
		if (--lIterator->second->mReferences == 0)
		{
			SDL_Texture *lTexture = mLoadedTextures[aId];
			mLoadedTextures[aId] = 0;
			SDL_DestroyTexture(lTexture);

			delete lIterator->second;

			mTexturesIds.erase(lIterator);
			--mNumLoadedTextures;

		}
	}

	int32 RenderManager::LoadTexture(std::string aFileName)
	{
		int32 lResult = -1;
		
		TTexturesIds::const_iterator lTextureIterator = mTexturesIds.find(aFileName);

		if (lTextureIterator != mTexturesIds.end())
		{
			++lTextureIterator->second->mReferences;
			return lTextureIterator->second->mId;
		}

		SDL_Surface* lTempSurface = IMG_Load(aFileName.c_str());
		if (lTempSurface != 0)
		{
			SDL_Texture* lTexture = SDL_CreateTextureFromSurface(mRenderer, lTempSurface);
			SDL_FreeSurface(lTempSurface);

			if (lTexture != 0)
			{
				uint32 lCapacity = mLoadedTextures.capacity();
				if (mNumLoadedTextures == lCapacity)
				{
					mLoadedTextures.push_back(lTexture);
					lResult = ++lCapacity;
				} 
				else 
				{
					uint32 lSize = mLoadedTextures.size();
					uint32 i = 0;
					while (i < lSize && mLoadedTextures[i] != 0)
					{
						++i;
					}
					lResult = i;
					
					if (i < lSize)
					{
						mLoadedTextures[lResult] = lTexture;
					}
					else
					{
						mLoadedTextures.push_back(lTexture);
					}
				}

				mTexturesIds[aFileName] = new TextureReferences(lResult, 1);
				++mNumLoadedTextures;
			}
			else
			{
				core::LogFormatString("Can't create texture %s", aFileName.c_str());
			}
		}
		else
		{
			core::LogFormatString("Can't load image %s", aFileName.c_str());
		}

		return lResult;
	}

	Sprite* RenderManager::CreateSprite(std::string aFileName)
	{
		Sprite *result = 0;

		int32 lTextureId = LoadTexture(aFileName);
		if (lTextureId > -1)
		{
			result = new Sprite();
			result->Init(lTextureId);
		}

		return result;
	}

} // namespace graphics

