#ifndef _ENGINE_GRAPHICS_SPRITECOMPONENT_H_
#define _ENGINE_GRAPHICS_SPRITECOMPONENT_H_

#include "Defs.h"
#include "Types.h"

#include "Graphics/MeshComponent.h"


namespace graphics
{
	/**
	
	*/
	class SpriteComponent : public MeshComponent {
		friend class RenderManager;
		REGISTER_COMPONENT_HEAD(SpriteComponent)
	protected:
		Mesh*											mMesh;
		Vector3D<float32>								mRotationOffset;
	protected:
		SpriteComponent() : MeshComponent(){}
		virtual ~SpriteComponent() {}
		
	}; // SpriteComponent
} // namespace graphics
#endif // _ENGINE_GRAPHICS_SPRITECOMPONENT_H_
