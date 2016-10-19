#include "Logic/ComponentFactory.h"


namespace logic
{
	SINGLETON_BODY(ComponentFactory);
	void ComponentFactory::Init()
	{

	}

	void ComponentFactory::Release()
	{
		mCreateFunctions.clear();
	}

	BOOL ComponentFactory::HasComponent(uint32 aComponentId)
	{
		return mCreateFunctions.count(aComponentId) > 0;
	}

	void ComponentFactory::AddComponentFunction(CreateFunction aCreateFunction, uint32 aComponentId)
	{
		mCreateFunctions[aComponentId] = aCreateFunction;
	}

	IComponent* ComponentFactory::GetComponent(uint32 aComponentId)
	{
		//@TODO: Components pool
		IComponent* lResult = NULL;
		if (HasComponent(aComponentId))
		{
			return mCreateFunctions[aComponentId]();
		}
		return lResult;
	}

	void ComponentFactory::RecycleComponent(IComponent* aComponent)
	{
		//@TODO: Components pool
		aComponent->Release();
		delete aComponent;
	}

} // namespace logic
