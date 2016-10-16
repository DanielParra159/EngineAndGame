#ifndef _ENGINE_LOGIC_IGAMEOBJECT_H_
#define _ENGINE_LOGIC_IGAMEOBJECT_H_

#include "Types.h"

#include "Support\Vector3D.h"

namespace logic
{
	/**
	
	*/
	class IGameObject {
		friend class World;
	protected:
		Vector3D<float32>								mPosition;
		Vector3D<float32>								mScale;
		Vector3D<float32>								mRotation; //@TODO: Quaternion
		BOOL											mActive;
	protected:
		virtual void									Init(BOOL aActive);
		virtual void									Update() = 0;
		virtual void									Render() = 0;
		virtual void									Release() = 0;
	public:
		IGameObject() : mPosition(), mScale(1,1,1), mRotation(), mActive(FALSE) {}
		virtual ~IGameObject() {}

		virtual void									SetEnabled(BOOL aActive);
		virtual BOOL									GetEnabled() { return mActive;	}

		//POSITION FUNCTIONS
		virtual void									SetPosition(const Vector3D<float32>& aPosition);
		virtual void									SetPosition(float32 aX, float32 aY, float32 aZ);
		//virtual const Vector3D<float32>&				GetPosition() const;
		virtual void									GetPosition(Vector3D<float32>& aPosition) const;
		virtual void									Translate(const Vector3D<float32>& aPosition);
		virtual void									Translate(float32 aX, float32 aY, float32 aZ);
		
		//SCALE FUNCTIONS
		virtual void									SetScale(const Vector3D<float32>& aScale);
		virtual void									SetScale(float32 aX, float32 aY, float32 aZ);
		virtual void									SetScale(float32 aScale);
		//virtual const Vector3D<float32>&				GetScale() const;
		virtual void									GetScale(Vector3D<float32>& aScale) const;
		virtual void									Scale(const Vector3D<float32>& aScale);
		virtual void									Scale(float32 aX, float32 aY, float32 aZ);
		
		//ROTATION FUNCTIONS
		virtual void									SetRotation(const Vector3D<float32>& aRotation);
		virtual void									SetRotation(float32 aX, float32 aY, float32 aZ);
		//virtual const Vector3D<float32>&				GetRotation() const;
		virtual void									GetRotation(Vector3D<float32>& aRotation) const;
		virtual void									Rotate(const Vector3D<float32>& aRotation);
		virtual void									Rotate(float32 aX, float32 aY, float32 aZ);
		virtual void									Rotate(float32 aAngle, const Vector3D<float32>& aAxis);

	}; // IGameObject
} // namespace logic
#endif // _ENGINE_LOGIC_IGAMEOBJECT_H_
