#ifndef _ENGINE_GRAPHICS_TEXTURE_H_
#define _ENGINE_GRAPHICS_TEXTURE_H_

#include "Types.h"

struct SDL_Texture;

namespace graphics
{
	class Texture
	{
	public:

		Texture(int32 aId, SDL_Texture* aTexture);
		
		virtual void									Release();

		SDL_Texture*									GetTextureData();

	private:
		int32 mId;
		SDL_Texture* mTextureData;

	}; // Texture
} // namespace graphics
#endif // _ENGINE_GRAPHICS_TEXTURE_H_
