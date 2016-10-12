#ifndef _ENGINE_GRAPHICS_IRENDERABLE_H_
#define _ENGINE_GRAPHICS_IRENDERABLE_H_

#include "Types.h"
#include "Support\Vector3D.h"

namespace graphics
{
	class RenderManager;

	class IRenderable {
	public:
		virtual void									Render(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale = &Vector3D<float32>::one, const Vector3D<float32>* aRotation = &Vector3D<float32>::zero) = 0;
		virtual void									Render(float32 aX, float32 aY, float32 aZ) = 0;

	}; // IRenderable
} // namespace graphics
#endif // _ENGINE_GRAPHICS_IRENDERABLE_H_
