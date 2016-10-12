#ifndef _ENGINE_GRAPHICS_CAMERA_H_
#define _ENGINE_GRAPHICS_CAMERA_H_

#include "Types.h"
#include "Support\Vector3D.h"
#include "Support\Matrix4.h"

namespace graphics
{
	/**
	Type of cameras
	*/
	enum eTypeCameras
	{
		ePerspective
	};

	class		Camera
	{
	friend class RenderManager;
	protected:
		Matrix4											mViewMatrix;
		Matrix4											mProjMatrix;
		eTypeCameras									mType;
	public:
		virtual void									LookAt(const Vector3D<float32>* aCameraPosition, const Vector3D<float32>* aCameraLookAt, const Vector3D<float32>* aUp);

		const Matrix4*									GetView() const { return &mViewMatrix; }
		eTypeCameras									GetType() const { return mType; }
	protected:
		Camera() {}
		virtual ~Camera() {}
		virtual void									Init(eTypeCameras aType);
		virtual void									Release();
		virtual void									Perspective(float32 aFov, float32 aAspect, float32 aNear, float32 aFar);

	}; // Camera
} // namespace graphics
#endif // _ENGINE_GRAPHICS_CAMERA_H_
