#ifndef _ENGINE_GRAPHICS_SPRITEANIMATOR_H_
#define _ENGINE_GRAPHICS_SPRITEANIMATOR_H_

#include "Types.h"
#include "Support/Vector3D.h"

#include "Graphics/IRenderable.h"
#include "Graphics/Texture.h"

#include <string>
#include <map>

namespace graphics
{
	class Material;
	class AnimateSpriteState;
	/**
	
	*/
	class SpriteAnimator : public IRenderable
	{
		friend class RenderManager;

		typedef std::map<uint32, AnimateSpriteState*>	TStates;
	private:
		uint32 mVAO, mVBO;
		Material* mMaterial;
		uint32 mTexture;
		float32											mFrameWidth;
		float32											mFrameHeight;
		float32											mSpeedScale;
		uint32											mFrames;
		uint32											mRows;
		uint32											mCols;
		TStates											mStates;
		AnimateSpriteState*								mCurrentState;
		BOOL											mFlipX;
		BOOL											mFlipY;
	public:
		virtual void									PrepareToRender(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale = &Vector3D<float32>::one, const Vector3D<float32>* aRotation = &Vector3D<float32>::zero);

		virtual void									Update();

		void											SetSpeedScale(float32 aSpeedScale);
		float32											GetSpeedScale() const { return mSpeedScale; };

		void											PlayState(uint32 aId, uint32 aFrame = 0);

		void											AddState(uint32 aId, uint32 aFrameStart, uint32 aNumFrames, float32 aAnimDuration, BOOL aLoop);

		void											SetFlipXY(BOOL aFlipX, BOOL aFlipY);
		void											SetFlipX(BOOL aFlipX);
		BOOL											GetFlipX() const { return mFlipX; }
		void											SetFlipY(BOOL aFlipY);
		BOOL											GetFlipY() const { return mFlipY; }

	protected:
		SpriteAnimator() : mSpeedScale(0.0f) {}
		virtual ~SpriteAnimator(){}

		virtual void									Init(const std::string& aTextureName, eTextureFormats aTextureFormat,
			uint32 aRows, uint32 aCols);
		virtual void									Release();

		virtual void									Render(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale = &Vector3D<float32>::one, const Vector3D<float32>* aRotation = &Vector3D<float32>::zero)  const;
		virtual IRenderable*							CreateInstance();

	}; // AnimateSprite

	class AnimateSpriteState
	{
		friend class SpriteAnimator;
	private:
		uint32											mCurrentFrame;
		uint32											mStartFrame;
		uint32											mNumFrames;
		float32											mAnimDuration;
		float32											mCurrentTime;
		BOOL											mLoop;
		BOOL											mPlaying;

	public:
		AnimateSpriteState() : mCurrentFrame(0), mStartFrame(0), mNumFrames(0), mAnimDuration(0.0f), mCurrentTime(0.0f),
			mLoop(FALSE), mPlaying(FALSE) {}
		virtual ~AnimateSpriteState() {}

		void											Init(uint32 aFrameStart, uint32 aNumFrames, float32 aAnimDuration, BOOL aLoop);

	}; // SpriteAnimator
} // namespace graphics
#endif // _ENGINE_GRAPHICS_SPRITEANIMATOR_H_
