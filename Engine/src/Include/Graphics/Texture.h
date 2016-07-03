#ifndef _ENGINE_GRAPHICS_TEXTURE_H_
#define _ENGINE_GRAPHICS_TEXTURE_H_

#include "Types.h"

struct SDL_Texture;

namespace graphics
{
	class Texture
	{
	public:

		Texture(SDL_Texture* aTexture);
		virtual ~Texture();

		SDL_Texture*									GetTextureData();

	private:
		int32 mID;
		SDL_Texture* mTextureData;

	}; // Texture
} // namespace graphics
#endif // _ENGINE_GRAPHICS_TEXTURE_H_
