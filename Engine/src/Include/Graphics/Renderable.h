#ifndef _ENGINE_GRAPHICS_IRENDERABLE_H_
#define _ENGINE_GRAPHICS_IRENDERABLE_H_

#include "Types.h"
#include "Types\Vector2D.h"

struct SDL_Renderer;

namespace graphics
{
	class IRenderable {
	public:
		virtual void									Render(SDL_Renderer* aRenderer, const Vector2D<>* aPosition) = 0;
		virtual void									Render(SDL_Renderer* aRenderer, int32 aX, int32 aY) = 0;

	}; // IRenderable
} // namespace graphics
#endif // _ENGINE_GRAPHICS_IRENDERABLE_H_
