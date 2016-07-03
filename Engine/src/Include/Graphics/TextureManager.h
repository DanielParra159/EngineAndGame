#ifndef _ENGINE_GRAPHICS_TEXTUREMANAGER_H_
#define _ENGINE_GRAPHICS_TEXTUREMANAGER_H_

#include "Types.h"

#include "Texture.h"

#include <unordered_map>

struct SDL_Texture;

namespace graphics
{
	class TextureManager
	{
		typedef std::unordered_map<int32, Texture*> TLoadedTextures;
	private:
		static TextureManager*							sInstance;
		TLoadedTextures									mLoadedTextures;
	public:
		static TextureManager*							Instance();

		Texture*										LoadTexture(std::string fileName);

	private:
		TextureManager();
		~TextureManager();

	}; // TextureManager
} // namespace graphics
#endif // _ENGINE_GRAPHICS_TEXTUREMANAGER_H_
