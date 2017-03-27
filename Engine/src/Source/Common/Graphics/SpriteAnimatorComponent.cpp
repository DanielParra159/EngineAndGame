#include "Graphics/SpriteAnimatorComponent.h"

#include "Logic/IGameObject.h"

#include "Graphics/RenderManager.h"

namespace graphics {
	REGISTER_COMPONENT_BODY(SpriteAnimatorComponent, graphics)
		
	void SpriteAnimatorComponent::Release()
	{
		graphics::RenderManager::Instance()->DeleteSpriteAnimator(mSpriteAnimator);
		mSpriteAnimator = NULL;
	}
		
	void SpriteAnimatorComponent::Render()
	{
		mSpriteAnimator->Render(mParent->GetPosition(), mParent->GetScale(), &(*mParent->GetRotation() + mRotationOffset));
	}

	void SpriteAnimatorComponent::Update()
	{
		mSpriteAnimator->Update();
	}

	void SpriteAnimatorComponent::SetCallbacks(logic::IGameObject* aGameObject, UpdateFunction& aUpdateFunction, FixedUpdateFunction& aFixedUpdateFunction, RenderFunction& aRenderFunction)
	{
		IComponent::SetCallbacks(aGameObject, aUpdateFunction, aFixedUpdateFunction, aRenderFunction);
		aUpdateFunction = IComponent::UpdateCallbackFunction;
		aFixedUpdateFunction = NULL;
		aRenderFunction = IComponent::RenderCallbackFunction;
	}
	void SpriteAnimatorComponent::SetSpriteAnimator(SpriteAnimator* aSpriteAnimator)
	{
		mSpriteAnimator = aSpriteAnimator;
	}

} // namespace graphics
