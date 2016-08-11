#ifndef _ENGINE_GRAPHICS_CAMERA_H_
#define _ENGINE_GRAPHICS_CAMERA_H_

#include "Types.h"
#include "Support\Vector3D.h"

namespace graphics
{

	class Camera
	{
	friend class RenderManager;
	protected:
		Vector3D<float32>								mPosition;
		Vector3D<float32>								mLookAt;
		Vector3D<float32>								mUp;
	public:
		virtual void									LookAt(const Vector3D<float32>* aEye, const Vector3D<float32>* aPosition, const Vector3D<float32>* aUp);
		virtual void									LookAt(const Vector3D<float32>* aEye, const Vector3D<float32>* aUp);
		void											SetPosition(const Vector3D<float32>& aPosition);
		void											SetPosition(float32 aX, float32 aY, float32 aZ);
	protected:
		Camera() {}
		virtual ~Camera() {}
		virtual void									Init(const Vector3D<float32>* aEye, const Vector3D<float32>* aCenter, const Vector3D<float32>* aUp);
		virtual void									Release();

	}; // Camera
} // namespace graphics
#endif // _ENGINE_GRAPHICS_CAMERA_H_
