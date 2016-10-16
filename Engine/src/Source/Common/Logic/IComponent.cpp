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
		//@TODO: Notify to gameobject
	}

} // namespace logic
