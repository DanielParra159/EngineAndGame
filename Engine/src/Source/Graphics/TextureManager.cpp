#include "Graphics\TextureManager.h"
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

	TextureManager::TextureManager() : mLoadedTextures()
	{

	}

	TextureManager::~TextureManager()
	{
		TLoadedTextures::const_iterator lIterator;
		TLoadedTextures::const_iterator lEndElement = mLoadedTextures.end();
		for (lIterator = mLoadedTextures.begin(); lIterator != lEndElement; ++lIterator)
		{
			
		}
	}

	Texture* TextureManager::LoadTexture(std::string fileName)
	{
		Texture *result = 0;

		SDL_Surface* lTempSurface = IMG_Load(fileName.c_str());
		if (lTempSurface != 0)
		{
			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(sys::Game::Instance()->GetRenderer(), lTempSurface);
			SDL_FreeSurface(lTempSurface);

			if (pTexture != 0)
			{
				result = new Texture(pTexture);
				std::hash<std::string> lHash;
				mLoadedTextures[lHash(fileName)] = result;
			}
			else
			{
				core::LogFormatString("Can't create texture %s", fileName.c_str());
			}
		}
		else 
		{
			core::LogFormatString("Can't load image %s", fileName.c_str());
		}

		return result;
	}

} // namespace graphics