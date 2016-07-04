#ifndef _ENGINE_GRAPHICS_RENDERER_H_
#define _ENGINE_GRAPHICS_RENDERER_H_

#include "Types.h"
#include "Types\Rect.h"
#include "Types\Vector2D.h"

struct  SDL_Renderer;


namespace graphics
{
	class Texture;

	class RenderManager
	{
	private:
		static RenderManager*							sInstance;
		SDL_Renderer* mRenderer;
	public:
		static RenderManager*							Instance();
		void											Init(SDL_Renderer *aRenderer);
		void											Release();

		void											RenderTexture(const Texture* aTexture, const Rect<int32> &aSrcRect, const Vector2D<int32> &aPosition, float64 aAngle);
		void											RenderTexture(const Texture* aTexture, const Rect<int32> &aSrcRect, int32 aX, int32 aY, float64 aAngle);
		

	}; // Renderer
} // namespace graphics
#endif // _ENGINE_GRAPHICS_RENDERER_H_
