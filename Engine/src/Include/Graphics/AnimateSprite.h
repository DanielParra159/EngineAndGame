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

		virtual void									Render(SDL_Renderer* aRenderer);

	}; // AnimateSprite
} // namespace graphics
#endif // _ENGINE_GRAPHICS_ANIMATESPRITE_H_
