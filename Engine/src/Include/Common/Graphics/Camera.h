#ifndef _ENGINE_GRAPHICS_CAMERA_H_
#define _ENGINE_GRAPHICS_CAMERA_H_

#include "Types.h"
#include "Support/Vector3D.h"
#include "Support/Matrix4.h"

#include "Logic/IComponent.h"

namespace graphics
{
	/**
	Type of cameras
	*/
	enum eTypeCameras
	{
		ePerspective,
		eOrthographic
	};


	class Camera : public logic::IComponent
	{
	friend class RenderManager;
	REGISTER_COMPONENT_HEAD(Camera)
	protected:
		Matrix4											mViewMatrix;
		Matrix4											mProjMatrix;
		eTypeCameras									mType;
		Vector3D<float32>								mCameraPosition;
		Vector3D<float32>								mCameraLookAt;
		Vector3D<float32>								mUp;
		const logic::IGameObject*						mTarget;
		Vector3D<float32>								mPositionOffset;
		Vector3D<float32>								mLookAtOffset;
	public:
		virtual void									LookAt(const Vector3D<float32>& aCameraPosition, const Vector3D<float32>& aCameraLookAt, const Vector3D<float32>& aUp);

		const Matrix4*									GetView() const { return &mViewMatrix; }
		const Matrix4*									GetProj() const { return &mProjMatrix; }
		eTypeCameras									GetType() const { return mType; }
		void											SetPosition(const Vector3D<float32>& aCameraPosition);
		void											SetLookAt(const Vector3D<float32>& aCameraLookAt);
		void											SetUp(const Vector3D<float32>& aUp);
		void											FollowTarget(const logic::IGameObject* aTarget, const Vector3D<float32>& aPositionOffset, const Vector3D<float32>& aLookAtOffset);
		const Vector3D<float32>&						GetCameraPosition() const { return mCameraPosition; }
	protected:
		Camera() {}
		virtual ~Camera() {}
		virtual void									Init(BOOL aActive, eTypeCameras aType);
		virtual void									Release();
		virtual void									Update();
		virtual void									SetCallbacks(logic::IGameObject* aGameObject, UpdateFunction& aUpdateFunction, FixedUpdateFunction& aFixedUpdateFunction, RenderFunction& aRenderFunction);
		virtual void									Perspective(float32 aFov, float32 aAspect, float32 aNear, float32 aFar);
		virtual void									Orthographic(float32 aLeft, float32 aRight, float32 aBottom, float32 aUp, float32 aZNear, float32 aZFar);

	}; // Camera
} // namespace graphics
#endif // _ENGINE_GRAPHICS_CAMERA_H_
