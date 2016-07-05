#ifndef _ENGINE_GRAPHICS_RENDERER_H_
#define _ENGINE_GRAPHICS_RENDERER_H_

#include "Types.h"
#include "Types\Rect.h"
#include "Types\Vector2D.h"

#include <string>
#include <unordered_map>
#include <vector>

struct  SDL_Renderer;
struct  SDL_Window;
struct  SDL_Texture;
struct  SDL_Surface;
class Color;

namespace graphics
{
	class Texture;
	class Sprite;

	typedef std::unordered_map<std::string, int32>		TTexturesIds;
	typedef std::vector<SDL_Texture*>					TLoadedTextures;
	class RenderManager
	{
	private:
		static RenderManager*							sInstance;
		TTexturesIds									mTexturesIds;
		TLoadedTextures									mLoadedTextures;
		uint32											mNumLoadedTextures;
		SDL_Renderer*									mRenderer;
		SDL_Window*										mWindow;
	public:
		static RenderManager*							Instance();
		BOOL											Init(const int8* aWindowsTitle, const Vector2D<uint32> &aWindowsSize, 
															 const Vector2D<uint32> &aWindowsPosition, const Color& aRenderDrawColor,  
															 BOOL aFullscreen);
		void											Release();

		void											Render();

		void											RenderTexture(uint32 aId, const Rect<int32> &aSrcRect, const Vector2D<int32> &aPosition, float64 aAngle);
		void											RenderTexture(uint32 aId, const Rect<int32> &aSrcRect, int32 aX, int32 aY, float64 aAngle);
		
		Sprite*											CreateSprite(std::string aFileName);
	private:
		RenderManager() : mTexturesIds(50), mLoadedTextures(50), mNumLoadedTextures(0), mRenderer(0), mWindow(0){}
		~RenderManager(){}
		void											UnloadTexture(int32 aId);
		int32											LoadTexture(std::string aFileName);

	}; // Renderer
} // namespace graphics
#endif // _ENGINE_GRAPHICS_RENDERER_H_
