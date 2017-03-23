#include "Graphics/SpriteComponent.h"

#include "Logic/IGameObject.h"

namespace graphics {
	REGISTER_COMPONENT_BODY(SpriteComponent, graphics)

	void SpriteComponent::SetMesh(Mesh* aMesh)
	{
		mSprite = (Sprite*)aMesh;
		MeshComponent::SetMesh(aMesh);
	}
} // namespace graphics
