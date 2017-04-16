#ifndef _ENGINE_GRAPHICS_SPRITEANIMATOR_H_
#define _ENGINE_GRAPHICS_SPRITEANIMATOR_H_

#include "Types.h"
#include "Support/Vector3D.h"

#include "Graphics/IRenderable.h"
#include "Graphics/Texture.h"

#include <string>
#include <map>
#include <unordered_map>
#include <vector>

namespace graphics
{
	class Material;
	class AnimateSpriteState;
	class StateCondition;

	enum eConditionType {
		eCurrentTime, // check animation current time
		eEnd, // check if the animation is ended
		eGreaterFloat, eLessFloat,
		eTrueBool, eFalseBool,
		eGreaterInt, eGreaterEqualsInt, eEqualsInt, eLessEqualsInt, eLessInt,
		eTrigger
	};
	union uValue
	{
		int32 mIntValue;
		float32 mFloatValue;
		BOOL mBoolValue;
	};
	/**
	
	*/
	class SpriteAnimator : public IRenderable
	{
		friend class RenderManager;

		typedef std::map<uint32, AnimateSpriteState*>	TStates;
		typedef std::vector<StateCondition*>			TConditionsList;
		typedef std::map<uint32, TConditionsList>		TStateTransitions;
		typedef std::unordered_map<std::string, uValue> TParameters;
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
		BOOL											mFlipX;
		BOOL											mFlipY;
		TStates											mStates;
		AnimateSpriteState*								mCurrentState;
		TStateTransitions								mTransitions;
		TParameters										mParameters;
	public:
		virtual void									PrepareToRender(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale = &Vector3D<float32>::one, const Vector3D<float32>* aRotation = &Vector3D<float32>::zero);

		virtual void									Update();

		void											SetSpeedScale(float32 aSpeedScale);
		float32											GetSpeedScale() const { return mSpeedScale; };

		void											PlayState(uint32 aId, uint32 aFrame = 0);

		void											AddState(uint32 aId, uint32 aFrameStart, uint32 aNumFrames, float32 aAnimDuration, BOOL aLoop);
		void											AddTransition(uint32 aFromState, uint32 aToState, eConditionType aType, float32 aFloatValue, const std::string& aParameter);
		void											AddTransition(uint32 aFromState, uint32 aToState, eConditionType aType, int32 aIntValue, const std::string& aParameter);
		void											AddTransition(uint32 aFromState, uint32 aToState, eConditionType aType, const std::string& aParameter);
		void											SetFloatParameter(const std::string& aName, float32 aFloatValue);
		void											SetIntParameter(const std::string& aName, int32 aIntValue);
		void											SetBoolParameter(const std::string& aName, BOOL aBoolValue);
		void											SetTriggerParameter(const std::string& aName);

		/*		void											Init(uint32 aNextState, TConditionType aType, int32 aIntValue);
		void											Init(uint32 aNextState, TConditionType aType, float32 aFloatValue);
		void											Init(uint32 aNextState, TConditionType aType, BOOL aBoolValue);
		void											Init(uint32 aNextState, TConditionType aType);*/

		void											SetFlipXY(BOOL aFlipX, BOOL aFlipY);
		void											SetFlipX(BOOL aFlipX);
		BOOL											GetFlipX() const { return mFlipX; }
		void											SetFlipY(BOOL aFlipY);
		BOOL											GetFlipY() const { return mFlipY; }

		Material*										GetMaterial() { return mMaterial; }
		void											SetMaterial(Material *aMaterial);

	protected:
		SpriteAnimator() : mVAO(0), mVBO(0), mMaterial(NULL), mTexture(0), 
			mFrameWidth(0.0f), mFrameHeight(0.0f), mSpeedScale(0.0f),
			mFrames(0), mRows(0), mCols(0), mFlipX(FALSE), mFlipY(FALSE),
			mStates(), mCurrentState(NULL), mTransitions(){}
		virtual ~SpriteAnimator(){}

		virtual void									Init(const std::string& aTextureName, eTextureFormats aTextureFormat,
			uint32 aRows, uint32 aCols);
		virtual void									Release();

		virtual void									Render(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale = &Vector3D<float32>::one, const Vector3D<float32>* aRotation = &Vector3D<float32>::zero)  const;
		virtual IRenderable*							CreateInstance();

		void											CheckStateConditions();

	}; // AnimateSprite

	class AnimateSpriteState
	{
		friend class SpriteAnimator;
	private:
		uint32											mId;
		uint32											mCurrentFrame;
		uint32											mStartFrame;
		uint32											mNumFrames;
		float32											mAnimDuration;
		float32											mCurrentTime;
		BOOL											mLoop;
		BOOL											mPlaying;

	private:
		AnimateSpriteState() : mCurrentFrame(0), mStartFrame(0), mNumFrames(0), mAnimDuration(0.0f), mCurrentTime(0.0f),
			mLoop(FALSE), mPlaying(FALSE) {}
		~AnimateSpriteState() {}

		void											Init(uint32 aId, uint32 aFrameStart, uint32 aNumFrames, float32 aAnimDuration, BOOL aLoop);

	}; // SpriteAnimator

	class StateCondition {
		friend class SpriteAnimator;
	private:
		std::string										mParameter;
		uValue											mValue;
		eConditionType									mType;
		uint32											mNextState;
	private:
		StateCondition() : mValue(), mType(), mNextState(){}
		~StateCondition() {}

		void											Init(uint32 aNextState, int32 aIntValue, eConditionType aType, const std::string& aParameter);
		void											Init(uint32 aNextState, float32 aFloatValue, eConditionType aType, const std::string& aParameter);
		void											Init(uint32 aNextState, eConditionType aType, const std::string& aParameter);
	}; // StateCondition
} // namespace graphics
#endif // _ENGINE_GRAPHICS_SPRITEANIMATOR_H_
