#ifndef _ENGINE_GRAPHICS_SPRITECOMPONENT_H_
#define _ENGINE_GRAPHICS_SPRITECOMPONENT_H_

#include "Defs.h"
#include "Types.h"

#include "Graphics/MeshComponent.h"
#include "Graphics/Sprite.h"


namespace graphics
{
	/**
	
	*/
	class SpriteComponent : public MeshComponent {
		friend class RenderManager;
		REGISTER_COMPONENT_HEAD(SpriteComponent)
	protected:
		Sprite*											mSprite;
	public:
		void											SetFlipXY(BOOL aFlipX, BOOL aFlipY) { mSprite->SetFlipX(aFlipX); mSprite->SetFlipY(aFlipY); }
		void											SetFlipX(BOOL aFlipX) { mSprite->SetFlipX(aFlipX); }
		BOOL											GetFlipX() const { return mSprite->GetFlipX(); }
		void											SetFlipY(BOOL aFlipY) { mSprite->SetFlipY(aFlipY); }
		BOOL											GetFlipY() const { return mSprite->GetFlipY(); }
		void											SetUseUICamera(BOOL aUseUICamera) { mSprite->SetUseUICamera(aUseUICamera); }
		BOOL											GetUseUICamera() const { return mSprite->GetUseUICamera(); }
	protected:
		SpriteComponent() : MeshComponent(){}
		virtual ~SpriteComponent() {}
		
		virtual void									SetMesh(Mesh* aMesh);
		
	}; // SpriteComponent
} // namespace graphics
#endif // _ENGINE_GRAPHICS_SPRITECOMPONENT_H_
