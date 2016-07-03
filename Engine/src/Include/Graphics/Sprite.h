#ifndef _ENGINE_GRAPHICS_SPRITE_H_
#define _ENGINE_GRAPHICS_SPRITE_H_

#include "Types.h"
#include "Renderable.h"
#include "Graphics\Texture.h"

namespace graphics
{
	class Sprite : public IRenderable
	{
	public:

		Sprite(const Vector2D<int32>& aPosition, Texture* aTexture);
		virtual ~Sprite();

		virtual void									Render(SDL_Renderer* aRenderer, const Vector2D<>* aPosition);

	private:
		Vector2D<int32> mSize;
		Texture *mTexture;

	}; // Renderer
} // namespace graphics
#endif // _ENGINE_GRAPHICS_SPRITE_H_
