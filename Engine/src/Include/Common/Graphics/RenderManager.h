#ifndef _ENGINE_GRAPHICS_RENDERER_H_
#define _ENGINE_GRAPHICS_RENDERER_H_

#include "Types.h"
#include "Support\Rect.h"
#include "Support\Vector2D.h"
#include "Support\IdReferences.h"

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


	typedef std::unordered_map<std::string, IdReferences*>		TTexturesIds;
	typedef std::vector<SDL_Texture*>							TLoadedTextures;
	/**
	This manager is responsible for painting in screen.
	*/
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

		void											BeginRender();
		void											EndRender();

		/**
		Allow to render a texture on screen
		@param aId, texture ID
		@param aSrcRect, the rect in source texture to render
		@param aPosition, position on screen
		@param aSize, size on screen
		@param aAgnel, rotation on screen
		*/
		void											RenderTexture(uint32 aId, const Rect<int32> &aSrcRect, const Vector2D<int32> &aPosition, const Vector2D<int32> &aSize, float64 aAngle);
		/**
		Allow to render a texture on screen
		@param aId, texture ID
		@param aSrcRect, the rect in source texture to render
		@param aX, aY, position on screen
		@param aW, aH, size on screen
		@param aAgnel, rotation on screen
		*/
		void											RenderTexture(uint32 aId, const Rect<int32> &aSrcRect, int32 aX, int32 aY, int32 aW, int32 aH, float64 aAngle);
		
		/**
		Create a sprite from file
		@param aFileName, file name
		@return the sprite created or null
		*/
		Sprite*											CreateSprite(const std::string& aFileName);
		/**
		Delete a sprite previously created
		@param aSprite, the sprite to delete
		*/
		void											DeleteSprite(Sprite* aSprite);
		/**
		Unload a texture
		@param aId, id of the texture
		*/
		void											UnloadTexture(int32 aId);
		/**
		Load a texture from file
		@param aFileName, file name
		@return aId, id of the texture loaded
		*/
		int32											LoadTexture(const std::string& aFileName);
	private:
		RenderManager() : mTexturesIds(50), mLoadedTextures(50), mNumLoadedTextures(0), mRenderer(0), mWindow(0){}
		~RenderManager(){}

	}; // Renderer
} // namespace graphics
#endif // _ENGINE_GRAPHICS_RENDERER_H_
