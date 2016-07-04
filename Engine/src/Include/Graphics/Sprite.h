#ifndef _ENGINE_GRAPHICS_SPRITE_H_
#define _ENGINE_GRAPHICS_SPRITE_H_

#include "Types.h"
#include "Renderable.h"
#include "Graphics\Texture.h"

#include <string>

namespace graphics
{
	class Sprite : public IRenderable
	{
		friend class TextureManager;
	public:
		virtual void									Init(Texture *aTexture);
		virtual void									Release();

		virtual void									Render(SDL_Renderer* aRenderer, const Vector2D<>* aPosition);
		virtual void									Render(SDL_Renderer* aRenderer, int32 aX, int32 aY);

		void											SetSize(const Vector2D<int32>& aSize);
		void											SetSize(uint32 aX, uint32 aY);

	private:
		Sprite() : mSize(), mTexture(0) {}
		Vector2D<int32>									mSize;
		Texture*										mTexture;

	}; // Renderer
} // namespace graphics
#endif // _ENGINE_GRAPHICS_SPRITE_H_
