#ifndef _ENGINE_GRAPHICS_TEXTUREMANAGER_H_
#define _ENGINE_GRAPHICS_TEXTUREMANAGER_H_

#include "Types.h"

#include <unordered_map>

namespace graphics
{
	class Texture;
	class Sprite;

	class TextureManager
	{
		typedef std::unordered_map<int32, Texture*> TLoadedTextures;
	private:
		static TextureManager*							sInstance;
		TLoadedTextures									mLoadedTextures;
	public:
		static TextureManager*							Instance();
		void											Init();
		void											Release();

		void											UnloadTexture(int32 aId);
		Texture*										LoadTexture(std::string aFileName);
		
		Sprite*											CreateSprite(std::string aFileName);

	private:
		TextureManager() : mLoadedTextures() {}
		~TextureManager() {}

	}; // TextureManager
} // namespace graphics
#endif // _ENGINE_GRAPHICS_TEXTUREMANAGER_H_
