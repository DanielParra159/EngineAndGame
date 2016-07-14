#ifndef _ENGINE_GRAPHICS_IRENDERABLE_H_
#define _ENGINE_GRAPHICS_IRENDERABLE_H_

#include "Types.h"
#include "Support\Vector2D.h"

namespace graphics
{
	class RenderManager;

	class IRenderable {
	public:
		virtual void									Render(const Vector2D<>* aPosition) = 0;
		virtual void									Render(int32 aX, int32 aY) = 0;

	}; // IRenderable
} // namespace graphics
#endif // _ENGINE_GRAPHICS_IRENDERABLE_H_
