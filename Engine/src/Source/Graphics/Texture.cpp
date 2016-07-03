#include "Graphics\Texture.h"

#include <SDL.h>

namespace graphics
{
	Texture::Texture(SDL_Texture* aTexture) : mTextureData(aTexture)
	{

	}

	Texture::~Texture()
	{
		
	}

	SDL_Texture* Texture::GetTextureData()
	{
		return mTextureData;
	}

} // namespace graphics