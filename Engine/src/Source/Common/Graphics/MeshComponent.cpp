#include "Graphics/MeshComponent.h"

#include "Logic/IGameObject.h"

#include "Graphics/RenderManager.h"

namespace graphics {
	REGISTER_COMPONENT_BODY(MeshComponent, graphics)
		
	void MeshComponent::Release()
	{
		graphics::RenderManager::Instance()->UnloadMesh(mMesh, FALSE);
		mMesh = NULL;
	}
		
	void MeshComponent::Render()
	{
		mMesh->Render(&(*mParent->GetPosition() + mPositionOffset), mParent->GetScale(), &(*mParent->GetRotation() + mRotationOffset));
	}

	void MeshComponent::SetCallbacks(logic::IGameObject* aGameObject, UpdateFunction& aUpdateFunction, FixedUpdateFunction& aFixedUpdateFunction, RenderFunction& aRenderFunction)
	{
		IComponent::SetCallbacks(aGameObject, aUpdateFunction, aFixedUpdateFunction, aRenderFunction);
		aUpdateFunction = NULL;
		aFixedUpdateFunction = NULL;
		aRenderFunction = IComponent::RenderCallbackFunction;
	}
	void MeshComponent::SetMesh(Mesh* aMesh)
	{
		mMesh = aMesh;
	}

} // namespace graphics
