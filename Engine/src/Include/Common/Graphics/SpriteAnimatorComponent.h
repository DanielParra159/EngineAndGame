#ifndef _ENGINE_GRAPHICS_SPRITEANIMATORCOMPONENT_H_
#define _ENGINE_GRAPHICS_SPRITEANIMATORCOMPONENT_H_

#include "Defs.h"
#include "Types.h"
#include "Logic/IComponent.h"

#include "Graphics/SpriteAnimator.h"

namespace logic{
	class IGameObject;
}


namespace graphics
{
	/**
	
	*/
	class SpriteAnimatorComponent : public logic::IComponent {
		friend class RenderManager;
		REGISTER_COMPONENT_HEAD(SpriteAnimatorComponent)
	protected:
		SpriteAnimator*									mSpriteAnimator;
		Vector3D<float32>								mRotationOffset;
	protected:
		SpriteAnimatorComponent() : logic::IComponent(), mSpriteAnimator(NULL){}
		virtual ~SpriteAnimatorComponent() {}
		virtual void									Release();
		virtual void									PrepareToRender();
		virtual void									Update();
		virtual void									SetCallbacks(logic::IGameObject* aGameObject, UpdateFunction& aUpdateFunction, FixedUpdateFunction& aFixedUpdateFunction, RenderFunction& aRenderFunction);
		void											SetSpriteAnimator(SpriteAnimator* aSpriteAnimator);

	public:
		void											SetRotationOffset(const Vector3D<float32>& aRotationOffset) { mRotationOffset = aRotationOffset; }

		void											SetSpeedScale(float32 aSpeedScale) { mSpriteAnimator->SetSpeedScale(aSpeedScale); }
		float32											GetSpeedScale() const { return mSpriteAnimator->GetSpeedScale(); };

		void											PlayState(uint32 aId, uint32 aFrame = 0) { mSpriteAnimator->PlayState(aId, aFrame); }

		void											AddState(uint32 aId, uint32 aFrameStart, uint32 aNumFrames, float32 aAnimDuration, BOOL aLoop) { mSpriteAnimator->AddState(aId, aFrameStart, aNumFrames, aAnimDuration, aLoop); }

		void											SetFlipXY(BOOL aFlipX, BOOL aFlipY) { mSpriteAnimator->SetFlipX(aFlipX); mSpriteAnimator->SetFlipY(aFlipY); }
		void											SetFlipX(BOOL aFlipX) { mSpriteAnimator->SetFlipX(aFlipX); }
		BOOL											GetFlipX() const { return mSpriteAnimator->GetFlipX(); }
		void											SetFlipY(BOOL aFlipY) { mSpriteAnimator->SetFlipY(aFlipY); }
		BOOL											GetFlipY() const { return mSpriteAnimator->GetFlipY(); }
		
	}; // SpriteAnimatorComponent
} // namespace graphics
#endif // _ENGINE_GRAPHICS_SPRITEANIMATORCOMPONENT_H_
