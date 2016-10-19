#include "Logic/IGameObject.h"
#include "Logic/IComponent.h"

#include "Logic/ComponentFactory.h"

namespace logic
{

	void IGameObject::Init(BOOL aActive)
	{
		mActive = aActive;
	}

	void IGameObject::Release()
	{
		TComponents::const_iterator lComponentIterator = mComponents.begin();
		TComponents::const_iterator lComponentIteratorEnd = mComponents.end();
		for (; lComponentIterator != lComponentIteratorEnd; ++lComponentIterator)
		{
			ComponentFactory::Instance()->RecycleComponent((*lComponentIterator).second->mComponent);
			delete (*lComponentIterator).second;
		}
		mComponents.clear();
	}

	void IGameObject::Update()
	{
		TComponents::const_iterator lComponentIterator = mComponents.begin();
		TComponents::const_iterator lComponentIteratorEnd = mComponents.end();
		for (; lComponentIterator != lComponentIteratorEnd; ++lComponentIterator)
		{
			TComponent *lComponent = (*lComponentIterator).second;
			if (lComponent->mUpdateFunction && lComponent->mComponent->GetEnabled())
				lComponent->mUpdateFunction(lComponent->mComponent);
		}
	}

	void IGameObject::FixedUpdate()
	{
		TComponents::const_iterator lComponentIterator = mComponents.begin();
		TComponents::const_iterator lComponentIteratorEnd = mComponents.end();
		for (; lComponentIterator != lComponentIteratorEnd; ++lComponentIterator)
		{
			TComponent *lComponent = (*lComponentIterator).second;
			if (lComponent->mFixedUpdateFunction && lComponent->mComponent->GetEnabled())
				lComponent->mFixedUpdateFunction(lComponent->mComponent);
		}
	}

	void IGameObject::Render()
	{
		TComponents::const_iterator lComponentIterator = mComponents.begin();
		TComponents::const_iterator lComponentIteratorEnd = mComponents.end();
		for (; lComponentIterator != lComponentIteratorEnd; ++lComponentIterator)
		{
			TComponent *lComponent = (*lComponentIterator).second;
			if (lComponent->mRenderFunction && lComponent->mComponent->GetEnabled())
				lComponent->mRenderFunction(lComponent->mComponent);
		}
	}

	

	void IGameObject::SetEnabled(BOOL aActive)
	{
		mActive = aActive;
		//@TODO: Notify to world
	}

	//POSITION FUNCTIONS
	void IGameObject::SetPosition(const Vector3D<float32>& aPosition)
	{
		mPosition.mX = aPosition.mX;
		mPosition.mY = aPosition.mY;
		mPosition.mZ = aPosition.mZ;
	}
	void IGameObject::SetPosition(float32 aX, float32 aY, float32 aZ)
	{
		mPosition.mX = aX;
		mPosition.mY = aY;
		mPosition.mZ = aZ;
	}
	//const Vector3D<float32>&					GetPosition() const { return mPosition; }
	void IGameObject::GetPosition(Vector3D<float32>& aPosition) const {
		aPosition.mX = mPosition.mX;
		aPosition.mY = mPosition.mY;
		aPosition.mZ = mPosition.mZ;
	}
	void IGameObject::Translate(const Vector3D<float32>& aPosition)
	{
		mPosition += aPosition;
	}
	void IGameObject::Translate(float32 aX, float32 aY, float32 aZ)
	{
		mPosition.mX += aX;
		mPosition.mY += aY;
		mPosition.mZ += aZ;
	}
	//SCALE FUNCTIONS
	void IGameObject::SetScale(const Vector3D<float32>& aScale)
	{
		mScale.mX = aScale.mX;
		mScale.mY = aScale.mY;
		mScale.mZ = aScale.mZ;
	}
	void IGameObject::SetScale(float32 aX, float32 aY, float32 aZ)
	{
		mScale.mX = aX;
		mScale.mY = aY;
		mScale.mZ = aZ;
	}
	void IGameObject::SetScale(float32 aScale)
	{
		mScale.mX = aScale;
		mScale.mY = aScale;
		mScale.mZ = aScale;
	}
	//const Vector3D<float32>&					GetScale() const { return mScale; }
	void IGameObject::GetScale(Vector3D<float32>& aScale) const
	{
		aScale.mX = mScale.mX;
		aScale.mY = mScale.mY;
		aScale.mZ = mScale.mZ;
	}
	void IGameObject::Scale(const Vector3D<float32>& aScale)
	{
		mScale *= aScale;
	}
	void IGameObject::Scale(float32 aX, float32 aY, float32 aZ)
	{
		mScale.mX *= aX;
		mScale.mY *= aY;
		mScale.mZ *= aZ;
	}
	//ROTATION FUNCTIONS
	void IGameObject::SetRotation(const Vector3D<float32>& aRotation)
	{
		mRotation.mX = aRotation.mX;
		mRotation.mY = aRotation.mY;
		mRotation.mZ = aRotation.mZ;
	}
	void IGameObject::SetRotation(float32 aX, float32 aY, float32 aZ)
	{
		mRotation.mX = aX;
		mRotation.mY = aY;
		mRotation.mZ = aZ;
	}
	//const Vector3D<float32>&					GetRotation() const { return mRotation; }
	void IGameObject::GetRotation(Vector3D<float32>& aRotation) const
	{
		aRotation.mX = mRotation.mX;
		aRotation.mY = mRotation.mY;
		aRotation.mZ = mRotation.mZ;
	}
	void IGameObject::Rotate(const Vector3D<float32>& aRotation)
	{
		mRotation += aRotation;
	}
	void IGameObject::Rotate(float32 aX, float32 aY, float32 aZ)
	{
		mRotation.mX += aX;
		mRotation.mY += aY;
		mRotation.mZ += aZ;
	}
	void IGameObject::Rotate(float32 aAngle, const Vector3D<float32>& aAxis)
	{
		mRotation += aAxis*aAngle;
	}
	
	void IGameObject::AddComponent( IComponent* aComponent)
	{
		// @TODO check if component already exists
		TComponent* lComponent = new TComponent();
		lComponent->mComponent = aComponent;
		mComponents[aComponent->GetComponentId()] = lComponent;
		aComponent->SetCallbacks(this, lComponent->mUpdateFunction, lComponent->mFixedUpdateFunction, lComponent->mRenderFunction);
	}

	IComponent* IGameObject::GetComponent(uint32 aComponentId)
	{
		if (mComponents.count(aComponentId) > 0)
			return mComponents[aComponentId]->mComponent;
		return NULL;
	}

	void IGameObject::DeleteComponent(IComponent* aComponent)
	{
		TComponents::iterator lIterator = mComponents.find(aComponent->GetComponentId());
		if (lIterator != mComponents.end())
		{
			mComponents.erase(aComponent->GetComponentId());
			ComponentFactory::Instance()->RecycleComponent(aComponent);
			delete (*lIterator).second;
		}
	}

	void IGameObject::DeleteComponent(uint32 aComponentId)
	{
		TComponents::iterator lIterator = mComponents.find(aComponentId);
		if (lIterator != mComponents.end())
		{
			mComponents.erase(aComponentId);
			ComponentFactory::Instance()->RecycleComponent((*lIterator).second->mComponent);
			delete (*lIterator).second;
		}
	}

	

} // namespace logic
