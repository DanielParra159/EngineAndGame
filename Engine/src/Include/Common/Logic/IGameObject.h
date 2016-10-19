#ifndef _ENGINE_LOGIC_IGAMEOBJECT_H_
#define _ENGINE_LOGIC_IGAMEOBJECT_H_

#include "Types.h"

#include "Support/Vector3D.h"
#include "Logic/IComponent.h"

#include <map>

namespace physics
{
	class Collider;
}

namespace logic
{
	/**
	
	*/
	class IGameObject {
		friend class World;

		struct TComponent
		{
			IComponent*									mComponent;
			logic::IComponent::UpdateFunction			mUpdateFunction;
			logic::IComponent::FixedUpdateFunction		mFixedUpdateFunction;
			logic::IComponent::RenderFunction			mRenderFunction;
			TComponent() : mComponent(NULL), mUpdateFunction(NULL), mRenderFunction(NULL) {}
		};
		typedef std::map<uint32, TComponent*>			TComponents;
	protected:
		Vector3D<float32>								mPosition;
		Vector3D<float32>								mScale;
		Vector3D<float32>								mRotation; //@TODO: Quaternion
		BOOL											mActive;
		TComponents										mComponents;
	protected:
		virtual void									Init(BOOL aActive);
		virtual void									Release();
		virtual void									Update();
		virtual void									FixedUpdate();
		virtual void									Render();
	public:
		IGameObject() : mPosition(), mScale(1,1,1), mRotation(), mActive(FALSE), mComponents(){}
		virtual ~IGameObject() {}

		virtual void									SetEnabled(BOOL aActive);
		virtual BOOL									GetEnabled() { return mActive;	}

		
		virtual void									OnTriggerEnter(physics::Collider* other) {}
		virtual void									OnTriggerExit(physics::Collider* other) {}
		virtual void									OnTriggerStay(physics::Collider* other) {}

		virtual void									OnCollisionEnter(physics::Collider* other) {}
		virtual void									OnCollisionExit(physics::Collider* other) {}
		virtual void									OnCollisionStay(physics::Collider* other) {}

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

		IComponent*										GetComponent(uint32 aComponentId);
		void											AddComponent(IComponent* aComponent);
		void											DeleteComponent(IComponent* aComponent);
		void											DeleteComponent(uint32 aComponentId);
	}; // IGameObject
} // namespace logic
#endif // _ENGINE_LOGIC_IGAMEOBJECT_H_
