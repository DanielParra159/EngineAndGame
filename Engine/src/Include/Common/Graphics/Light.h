#ifndef _ENGINE_GRAPHICS_LIGHT_H_
#define _ENGINE_GRAPHICS_LIGHT_H_

#include "Types.h"
#include "Support/Vector3D.h"
#include "Support/Color32.h"

namespace graphics
{
	/**
	
	*/
	class Light {
	friend class RenderManager;
	protected:
		Vector3D<float32>								mPosition;
		Color32											mColor;
	public:
		const Vector3D<float32>*						GetPosition() { return &mPosition; }
		void											SetPosition(const Vector3D<float32>& aPosition) { mPosition = aPosition; }
		const Color32*									GetColor() { return &mColor; }
		void											SetColor(const Color32& aColor) { mColor = aColor; }
	protected:
		Light() {}
		virtual ~Light() {}
		virtual void									Init(const Vector3D<float32>& aPosition, const Color32& aColor = Color32::white);
		virtual void									Release();

	}; // Light
} // namespace graphics
#endif // _ENGINE_GRAPHICS_LIGHT_H_
