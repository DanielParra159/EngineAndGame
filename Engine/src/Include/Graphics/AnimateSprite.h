#ifndef _ENGINE_GRAPHICS_ANIMATESPRITE_H_
#define _ENGINE_GRAPHICS_ANIMATESPRITE_H_

#include "Types.h"
#include "Graphics\Sprite.h"

namespace graphics
{
	class AnimateSprite : public Sprite
	{
	public:

		AnimateSprite();
		virtual ~AnimateSprite();

		virtual void									Render(SDL_Renderer* aRenderer, const Vector2D<>* aPosition);
		virtual void									Render(SDL_Renderer* aRenderer, int32 aX, int32 aY);

	}; // AnimateSprite
} // namespace graphics
#endif // _ENGINE_GRAPHICS_ANIMATESPRITE_H_
