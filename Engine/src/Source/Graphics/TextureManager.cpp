#include "Graphics\TextureManager.h"
#include "Graphics\Texture.h"
#include "Graphics\Sprite.h"

#include "System\Game.h"
#include "Core\Log.h"

#include <SDL.h>
#include <SDL_image.h>

namespace graphics
{
	TextureManager* TextureManager::sInstance = 0;

	TextureManager* TextureManager::Instance()
	{
		if (TextureManager::sInstance == 0)
		{
			TextureManager::sInstance = new TextureManager();
			return TextureManager::sInstance;
		}
		return TextureManager::sInstance;
	}

	void TextureManager::Init()
	{
		TLoadedTextures::const_iterator lIterator;
		TLoadedTextures::const_iterator lEndElement = mLoadedTextures.end();
		for (lIterator = mLoadedTextures.begin(); lIterator != lEndElement; ++lIterator)
		{

		}
	}

	void TextureManager::Release()
	{

	}

	void TextureManager::UnloadTexture(int32 aId)
	{
		//@TODO: Contar y mantener referencias?
		Texture *lTexture = mLoadedTextures[aId];
		mLoadedTextures.erase(aId);
		delete lTexture;
	}

	Texture* TextureManager::LoadTexture(std::string aFileName)
	{
		Texture *lResult = 0;
		std::hash<std::string> lHash;
		int32 lId = lHash(aFileName);
		TLoadedTextures::const_iterator lTextureIterator = mLoadedTextures.find(lId);

		if (lTextureIterator != mLoadedTextures.end())
		{
			return lTextureIterator->second;
		}

		SDL_Surface* lTempSurface = IMG_Load(aFileName.c_str());
		if (lTempSurface != 0)
		{
			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(sys::Game::Instance()->GetRenderer(), lTempSurface);
			SDL_FreeSurface(lTempSurface);

			if (pTexture != 0)
			{
				//@TODO: Contar y mantener referencias?
				lResult = new Texture(lId, pTexture);
				mLoadedTextures[lHash(aFileName)] = lResult;
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

	Sprite* TextureManager::CreateSprite(std::string aFileName)
	{
		Sprite *result = 0;
		Texture *lTexture = LoadTexture(aFileName);
		if (lTexture)
		{
			result = new Sprite();
			result->Init(lTexture);
		}

		return result;
	}

} // namespace graphics