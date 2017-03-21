#ifndef _ENGINE_GRAPHICS_MESHCOMPONENT_H_
#define _ENGINE_GRAPHICS_MESHCOMPONENT_H_

#include "Defs.h"
#include "Types.h"
#include "Logic/IComponent.h"

#include "Graphics/Mesh.h"

namespace logic{
	class IGameObject;
}


namespace graphics
{
	/**
	
	*/
	class MeshComponent : public logic::IComponent {
		friend class RenderManager;
		REGISTER_COMPONENT_HEAD(MeshComponent)
	protected:
		Mesh*											mMesh;
		Vector3D<float32>								mRotationOffset;
	protected:
		MeshComponent() : logic::IComponent(), mMesh(NULL), mRotationOffset(){}
		virtual ~MeshComponent() {}
		virtual void									Release();
		virtual void									Render();
		virtual void									SetCallbacks(logic::IGameObject* aGameObject, UpdateFunction& aUpdateFunction, FixedUpdateFunction& aFixedUpdateFunction, RenderFunction& aRenderFunction);
		void											SetMesh(Mesh* aMesh);
	public:
		const std::string&								GetName() const { return mMesh->GetName(); }
		Material*										GetMaterial() { return mMesh->GetMaterial(); }
		void											SetMaterial(Material *aMaterial) { mMesh->SetMaterial(aMaterial); };
		void											SetRotationOffset(const Vector3D<float32>& aRotationOffset) { mRotationOffset = aRotationOffset; }
		
	}; // MeshComponent
} // namespace graphics
#endif // _ENGINE_GRAPHICS_MESHCOMPONENT_H_
