#include "Graphics\Texture.h"
#include "Graphics\TextureManager.h"

#include <SDL.h>

namespace graphics
{
	Texture::Texture(int32 aId, SDL_Texture* aTexture) : mId(aId), mTextureData(aTexture)
	{

	}

	void Texture::Release()
	{
		TextureManager::Instance()->UnloadTexture(mId);
		delete mTextureData;
	}

	SDL_Texture* Texture::GetTextureData() const
	{
		return mTextureData;
	}

} // namespace graphics