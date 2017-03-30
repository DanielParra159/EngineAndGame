#include "Graphics/Light.h"

namespace graphics
{
	void Light::Init(const Vector3D<float32>& aPosition, const Color32& aColor)
	{
		mPosition = aPosition;
		mColor = aColor;
	}

	void Light::Release()
	{
		
	}
} // namespace graphics
