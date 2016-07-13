#ifndef _ENGINE_GRAPHICS_IRENDERABLE_H_
#define _ENGINE_GRAPHICS_IRENDERABLE_H_

#include "Types.h"
#include "Types\Vector3D.h"

namespace graphics
{
	class RenderManager;

	class IRenderable {
	public:
		virtual void									Render(const Vector3D<float32>* aPosition) = 0;
		virtual void									Render(float32 aX, float32 aY, float32 aZ) = 0;

	}; // IRenderable
} // namespace graphics
#endif // _ENGINE_GRAPHICS_IRENDERABLE_H_
