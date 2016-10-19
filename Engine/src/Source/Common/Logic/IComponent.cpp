#include "Logic\IComponent.h"

namespace logic
{

	void IComponent::Init(BOOL aActive)
	{
		mActive = aActive;
	}

	void IComponent::SetEnabled(BOOL aActive)
	{
		mActive = aActive;
	}

	void IComponent::SetCallbacks(IGameObject* aGameObject, UpdateFunction& aUpdateFunction, FixedUpdateFunction& aFixedUpdateFunction, RenderFunction& aRenderFunction)
	{
		mParent = aGameObject;
		aUpdateFunction = NULL;
		aFixedUpdateFunction = NULL;
		aRenderFunction = NULL;
	}

} // namespace logic
