#ifndef _LOGIC_IGAMEOBJECT_H_
#define _LOGIC_IGAMEOBJECT_H_

#include "Types.h"

#include "Types\Vector3D.h"

namespace logic
{
	/**
	
	*/
	class IGameObject {
	private:
		Vector3D<float32>							mPosition;
		Vector3D<float32>							mScale;
		Vector3D<float32>							mRotation; //@TODO: Quaternion
		BOOL										mEnabled;
	public:
		virtual ~IGameObject() {}

		virtual void								Init() = 0;
		virtual void								Update() = 0;
		virtual void								Render() = 0;
		virtual void								Release() = 0;

		void										SetEnabled(BOOL aEnabled);
		BOOL										GetEnabled() { return mEnabled;	}

		//POSITION FUNCTIONS
		void										SetPosition(const Vector3D<float32>& aPosition);
		void										SetPosition(float32 aX, float32 aY, float32 aZ);
		//const Vector3D<float32>&					GetPosition() const;
		void										GetPosition(Vector3D<float32>& aPosition) const;
		void										Translate(const Vector3D<float32>& aPosition);
		void										Translate(float32 aX, float32 aY, float32 aZ);
		
		//SCALE FUNCTIONS
		void										SetScale(const Vector3D<float32>& aScale);
		void										SetScale(float32 aX, float32 aY, float32 aZ);
		void										SetScale(float32 aScale);
		//const Vector3D<float32>&					GetScale() const;
		void										GetScale(Vector3D<float32>& aScale) const;
		void										Scale(const Vector3D<float32>& aScale);
		void										Scale(float32 aX, float32 aY, float32 aZ);
		
		//ROTATION FUNCTIONS
		void										SetRotation(const Vector3D<float32>& aRotation);
		void										SetRotation(float32 aX, float32 aY, float32 aZ);
		//const Vector3D<float32>&					GetRotation() const;
		void										GetRotation(Vector3D<float32>& aRotation) const;
		void										Rotate(const Vector3D<float32>& aRotation);
		void										Rotate(float32 aX, float32 aY, float32 aZ);
		void										Rotate(float32 aAngle, const Vector3D<float32>& aAxis);

	}; // IGameObject
} // namespace logic
#endif // _LOGIC_IGAMEOBJECT_H_
