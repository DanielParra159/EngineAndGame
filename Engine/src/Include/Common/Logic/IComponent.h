#ifndef _ENGINE_LOGIC_ICOMPONENT_H_
#define _ENGINE_LOGIC_ICOMPONENT_H_

#include "Types.h"

#include "Support/Vector3D.h"

#include "Logic/ComponentFactory.h"

namespace logic
{
	static uint32 sCurrentId = 0;
	
	/**
	
	*/
	class IComponent {
	public:
		typedef void(*UpdateFunction)(IComponent*);
		typedef void(*RenderFunction)(IComponent*);
		friend class ComponentFactory;
		friend class IGameObject;

		static uint32 GetId() { return ++sCurrentId; }

	protected:
		BOOL											mActive;
	protected:
		IComponent() : mActive(FALSE) {}
		virtual ~IComponent() {}

		virtual void									SetCallbacks(UpdateFunction& aUpdateFunction, RenderFunction& aRenderFunction)
		{
			aUpdateFunction = NULL;
			aRenderFunction = NULL;
		}
		
		virtual void									Init(BOOL aActive);
		virtual void									Release() = 0;
		virtual void									Update() {}
		virtual void									Render() {}
		virtual void									SetPosition(const Vector3D<float32> aPosition) {};
		static void RenderCallbackFunction(IComponent* aComponent)
		{
			aComponent->Render();
		}
		static void UpdateCallbackFunction(IComponent* aComponent)
		{
			aComponent->Update();
		}
	public:
		virtual uint32									GetComponentId() = 0;
		virtual void									SetEnabled(BOOL aActive);
		virtual BOOL									GetEnabled() { return mActive; }

		
	}; // IComponent

	

#define REGISTER_COMPONENT_HEAD(Class) \
public: \
	static uint32 sId; \
	static BOOL sRegisteredFactory; \
    static IComponent* Create(); \
	static BOOL Register(); \
	virtual uint32 GetComponentId() { return Class::sId; }

#define REGISTER_COMPONENT_BODY(Class, Namespace) \
	uint32 Class::sId = IComponent::GetId(); \
	BOOL Class::sRegisteredFactory = Class::Register(); \
	logic::IComponent* Class::Create() \
	{ \
		logic::IComponent* lResult = new Namespace::Class(); \
		return lResult; \
	} \
	BOOL Class::Register() \
	{ \
		if (!logic::ComponentFactory::Instance()->HasComponent(Class::sId)) \
		{ \
			logic::ComponentFactory::Instance()->AddComponentFunction(Class::Create, Class::sId); \
		} \
		return TRUE; \
	}
} // namespace logic
#endif // _ENGINE_LOGIC_ICOMPONENT_H_
