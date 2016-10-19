#ifndef _ENGINE_LOGIC_COMPONENTFACTORY_H_
#define _ENGINE_LOGIC_COMPONENTFACTORY_H_

#include "Defs.h"
#include "Types.h"

#include "Logic/IComponent.h"

#include <map>

namespace core
{
	class Game;
}

namespace logic
{
	class IComponent;

	/**
	@TODO: Components pool
	*/
	class ComponentFactory
	{
		SINGLETON_HEAD(ComponentFactory)
		friend class core::Game;
		typedef IComponent*(*CreateFunction)();
		typedef std::map<uint32, CreateFunction>		TCreateFunctionMap;
	private:
		TCreateFunctionMap								mCreateFunctions;
	private:
		void											Init();
		void											Release();
	
	public:
		BOOL											HasComponent(uint32 aComponentId);
		void											AddComponentFunction(CreateFunction aCreateFunction, uint32 aComponentId);
		IComponent*										GetComponent(uint32 aComponentId);
		void											RecycleComponent(IComponent* aComponent);
	public:
		ComponentFactory() {}
		virtual ~ComponentFactory() {}
	}; // ComponentFactory
} // namespace logic
#endif // _ENGINE_LOGIC_COMPONENTFACTORY_H_
