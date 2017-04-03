#include "Graphics/SpriteAnimator.h"

#include "Graphics/RenderManager.h"
#include "Graphics/Texture.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"

#include "System/Time.h"

#include "Core/Log.h"

#include "Support/Math.h"

#include <GL/glew.h>

#include <unordered_set>

namespace graphics
{
	float32 sVertexData[] = {
		// X      Y     Z     Nx    Ny     Nz    U     V
		//Front
		-0.5f, 0.5f,  0.0f, 0.0f ,0.0f, -1.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.0f, 0.0f ,0.0f, -1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.0f, 0.0f ,0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f,  0.0f, 0.0f ,0.0f, -1.0f, 0.0f, 1.0f,
		0.5f, 0.5f,  0.0f, 0.0f ,0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, -0.5f,  0.0f, 0.0f ,0.0f, -1.0f, 1.0f, 0.0f
	};

	void SpriteAnimator::Init(const std::string& aTextureName, eTextureFormats aTextureFormat, uint32 aRows, uint32 aCols) {
		mMaterial = RenderManager::Instance()->LoadMaterial("SpriteDiffuse");
		const Texture* lTexture = RenderManager::Instance()->LoadTexture(aTextureName, aTextureFormat);
		mMaterial->SetDiffuseTexture(lTexture);

		mCols = aCols;
		mRows = aRows;
		mSpeedScale = 1.0f;

		mFrameWidth = lTexture->GetWidth() / (float32)aCols;
		mFrameHeight = lTexture->GetHeight() / (float32)aRows;
		//mMaterial->SetMatrix4("projection", &Matrix4x4::Orthographic(0.0f, (float32)aWindowWidth, (float32)aWindowHeight, 0.0f));

		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &mVBO);
		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(sVertexData), sVertexData, GL_DYNAMIC_DRAW);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void SpriteAnimator::Release() {
		RenderManager::Instance()->UnloadMaterial(mMaterial);
		mMaterial = NULL;

		LOOP_ITERATOR(TStates::iterator, mStates, lIterator, lEndElement) 
		{
			delete lIterator->second;
		}
		mStates.clear();

		LOOP_ITERATOR(TStateTransitions::iterator, mTransitions, lIterator, lEndElement)
		{
			TConditionsList lConditions = (*lIterator).second;
			LOOP_ITERATOR(TConditionsList::iterator, lConditions, lConditionsIterator, lConditionsEndElement)
			{
				delete (*lConditionsIterator);
			}
			lConditions.clear();
		}
		mTransitions.clear();
		mCurrentState = NULL;
	}

	void SpriteAnimator::PrepareToRender(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale, const Vector3D<float32>* aRotation) {
		RenderManager::Instance()->PrepareToRender(aPosition, aScale, aRotation, this);
	}

	void SpriteAnimator::Render(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale, const Vector3D<float32>* aRotation)  const
	{
		uint32 lFrame = mCurrentState->mCurrentFrame + mCurrentState->mStartFrame;
		uint32 lXFrame = lFrame % mCols;
		uint32 lYFrame = lFrame / mCols;

		float32 lUMin = lXFrame * mFrameWidth / mMaterial->GetDiffuseTexture()->GetWidth();
		float32 lUMax = (lXFrame +1) * mFrameWidth / mMaterial->GetDiffuseTexture()->GetWidth();
		float32 VMin = lYFrame * mFrameHeight / mMaterial->GetDiffuseTexture()->GetHeight();
		float32 VMax = (lYFrame + 1) * mFrameHeight / mMaterial->GetDiffuseTexture()->GetHeight();
		if (mFlipX)
		{
			float32 lAux = lUMin;
			lUMin = lUMax;
			lUMax = lAux;
		}
		if (mFlipY)
		{
			float32 lAux = VMin;
			VMin = VMax;
			VMax = lAux;
		}

		sVertexData[6] = sVertexData[22] = sVertexData[30] = lUMin;
		sVertexData[14] = sVertexData[38] = sVertexData[46] = lUMax;
		sVertexData[23] = sVertexData[15] = sVertexData[47] = VMin;
		sVertexData[7] = sVertexData[39] = sVertexData[31] = VMax;

		mMaterial->UseMaterial();
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(sVertexData), sVertexData);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//RenderManager::Instance()->RenderSpriteAnimator(aPosition, aScale, aRotation, this);

		Matrix4 lModelMatrix;
		Matrix4x4::translate(&lModelMatrix, aPosition);
		Matrix4x4::rotate(&lModelMatrix, aRotation);
		Matrix4x4::scale(&lModelMatrix, aScale);

		Camera* lRenderCamera = RenderManager::Instance()->GetRenderCamera();

		mMaterial->PrepareToRender(&lModelMatrix, lRenderCamera->GetCameraPosition());
		mMaterial->SetVertexFloatAttribPointer("position", 3, FALSE, 8, 0, mVBO);
		mMaterial->SetVertexFloatAttribPointer("normal", 3, FALSE, 8, 3, mVBO);
		mMaterial->SetVertexFloatAttribPointer("texcoord", 2, FALSE, 8, 6, mVBO);
		//@TODO: if is the same material only need to asign these attrib. one time
		mMaterial->SetMatrix4("view", lRenderCamera->GetView());
		mMaterial->SetMatrix4("proj", lRenderCamera->GetProj());
		mMaterial->ActiveDiffuseTexture();
		mMaterial->ActiveNormalTexture();
		

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void SpriteAnimator::Update()
	{
		if (!mCurrentState->mPlaying) {
			CheckStateConditions();
			return;
		}

		float32 lSpeed = mCurrentState->mNumFrames / mCurrentState->mAnimDuration;
		mCurrentState->mCurrentTime += sys::Time::GetDeltaSec() * lSpeed * mSpeedScale;
		if (mCurrentState->mCurrentTime > mCurrentState->mAnimDuration)
		{
			if (mCurrentState->mLoop)
			{
				mCurrentState->mCurrentTime -= mCurrentState->mAnimDuration;
			}
			else {
				mCurrentState->mCurrentTime = mCurrentState->mAnimDuration;
				mCurrentState->mPlaying = FALSE;
			}
		}
		mCurrentState->mCurrentFrame = (uint32)(mCurrentState->mCurrentTime / (mCurrentState->mAnimDuration / mCurrentState->mNumFrames));

		CheckStateConditions();
	}

	void SpriteAnimator::CheckStateConditions() {
		TConditionsList lConditions = mTransitions[mCurrentState->mId];
		BOOL lAllowedCondition = FALSE;
		std::unordered_set<StateCondition*> lAllowedStates, lNoAllowedStates;
		LOOP_ITERATOR(TConditionsList::const_iterator, lConditions, lConditionsIterator, lConditionsEndElement)
		{
			lAllowedCondition = FALSE;
			switch ((*lConditionsIterator)->mType)
			{
			case eCurrentTime:
				if ((*lConditionsIterator)->mValue.mFloatValue >= mCurrentState->mCurrentTime
					&& lNoAllowedStates.find(*lConditionsIterator) == lNoAllowedStates.end()) {
					lAllowedStates.insert(*lConditionsIterator);
					lAllowedCondition = TRUE;
				}
				break;
			case eEnd:
				if (!mCurrentState->mPlaying 
					&& lNoAllowedStates.find(*lConditionsIterator) == lNoAllowedStates.end()) {
					lAllowedStates.insert(*lConditionsIterator);
					lAllowedCondition = TRUE;
				}
				break;
			case eGreaterInt:
				break;
			case eGreaterFloat:
				break;
			case eFalseBool:
			{
				TParameters::const_iterator lParameter = mParameters.find((*lConditionsIterator)->mParameter);
				if (lParameter != mParameters.end() && !(*lParameter).second.mBoolValue
					&& lNoAllowedStates.find(*lConditionsIterator) == lNoAllowedStates.end()) {
					lAllowedStates.insert(*lConditionsIterator);
					lAllowedCondition = TRUE;
				}
				break;
			}
			case eTrueBool:
			{
				TParameters::const_iterator lParameter = mParameters.find((*lConditionsIterator)->mParameter);
				if (lParameter != mParameters.end() && (*lParameter).second.mBoolValue
					&& lNoAllowedStates.find(*lConditionsIterator) == lNoAllowedStates.end()) {
					lAllowedStates.insert(*lConditionsIterator);
					lAllowedCondition = TRUE;
				}
				break;
			}
			case eTrigger:
				if (mParameters.find((*lConditionsIterator)->mParameter) != mParameters.end()
					&& lNoAllowedStates.find(*lConditionsIterator) == lNoAllowedStates.end()) {
					lAllowedStates.insert(*lConditionsIterator);
					lAllowedCondition = TRUE;
				}
				break;
			}
			

			if (!lAllowedCondition) {
				lNoAllowedStates.insert(*lConditionsIterator);
				lAllowedStates.erase(*lConditionsIterator);
			}
		}

		std::unordered_set<StateCondition*>::const_iterator lIterator = lAllowedStates.begin();
		if (lIterator != lAllowedStates.end())
		{
			if ((*lIterator)->mType == eTrigger)
			{
				mParameters.erase((*lIterator)->mParameter);
			}
			PlayState((*lIterator)->mNextState);
		}

	}

	void SpriteAnimator::SetSpeedScale(float32 aSpeedScale)
	{
		mSpeedScale = aSpeedScale;
	}

	IRenderable* SpriteAnimator::CreateInstance() {
		SpriteAnimator* lResult = new SpriteAnimator();
		lResult->Init(mMaterial->GetDiffuseTexture()->GetName(), mMaterial->GetDiffuseTexture()->GetFormat(), mRows, mCols);

		return lResult;
	}

	void SpriteAnimator::PlayState(uint32 aId, uint32 aFrame)
	{
		mCurrentState = mStates[aId];
		assert(aFrame <= mCurrentState->mNumFrames && "SpriteAnimator::PlayState aFrame <= mCurrentState->mNumFrames");
		mCurrentState->mCurrentFrame = aFrame;
		mCurrentState->mCurrentTime = aFrame * (mCurrentState->mAnimDuration / mCurrentState->mNumFrames);
		mCurrentState->mPlaying = TRUE;
	}

	void SpriteAnimator::AddState(uint32 aId, uint32 aFrameStart, uint32 aNumFrames, float32 aAnimDuration, BOOL aLoop)
	{
		AnimateSpriteState* lAnimateSpriteState = new AnimateSpriteState();
		lAnimateSpriteState->Init(aId, aFrameStart, aNumFrames, aAnimDuration, aLoop);

		mStates.insert(std::pair<int32, AnimateSpriteState*>(aId, lAnimateSpriteState));
	}

	void SpriteAnimator::AddTransition(uint32 aFromState, uint32 aToState, eConditionType aType, float32 aFloatValue, const std::string& aParameter)
	{
		StateCondition* lStateCondition = new StateCondition();
		lStateCondition->Init(aToState, aFloatValue, aType, aParameter);
		mTransitions[aFromState].push_back(lStateCondition);
	}
	void SpriteAnimator::AddTransition(uint32 aFromState, uint32 aToState, eConditionType aType, int32 aIntValue, const std::string& aParameter)
	{
		StateCondition* lStateCondition = new StateCondition();
		lStateCondition->Init(aToState, aIntValue, aType, aParameter);
		mTransitions[aFromState].push_back(lStateCondition);
	}
	void SpriteAnimator::AddTransition(uint32 aFromState, uint32 aToState, eConditionType aType, const std::string& aParameter)
	{
		assert(aType == eTrigger || aType == eEnd || aType == eTrueBool || aType == eFalseBool);
		StateCondition* lStateCondition = new StateCondition();
		lStateCondition->Init(aToState, aType, aParameter);
		mTransitions[aFromState].push_back(lStateCondition);
	}
	void SpriteAnimator::SetFloatParameter(const std::string& aName, float32 aFloatValue)
	{
		uValue lValue = uValue();
		lValue.mFloatValue = aFloatValue;
		mParameters[aName] = lValue;
	}
	void SpriteAnimator::SetIntParameter(const std::string& aName, int32 aIntValue)
	{
		uValue lValue = uValue();
		lValue.mIntValue = aIntValue;
		mParameters[aName] = lValue;
	}
	void SpriteAnimator::SetBoolParameter(const std::string& aName, BOOL aBoolValue)
	{
		uValue lValue = uValue();
		lValue.mBoolValue = aBoolValue;
		mParameters[aName] = lValue;
	}
	void SpriteAnimator::SetTriggerParameter(const std::string& aName)
	{
		mParameters[aName] = uValue();
	}

	void SpriteAnimator::SetFlipXY(BOOL aFlipX, BOOL aFlipY)
	{
		mFlipX = aFlipX;
		//mMaterial->SetBool("flipX", mFlipX);
		mFlipY = aFlipY;
		//mMaterial->SetBool("flipY", mFlipY);
	}
	void SpriteAnimator::SetFlipX(BOOL aFlipX)
	{
		mFlipX = aFlipX;
		//mMaterial->SetBool("flipX", mFlipX);
	}
	void SpriteAnimator::SetFlipY(BOOL aFlipY)
	{
		mFlipY = aFlipY;
		//mMaterial->SetBool("flipY", mFlipY);
	}

	//-----------------------------------------------------------AnimateSpriteState------------------------------------

	void AnimateSpriteState::Init(uint32 aId, uint32 aFrameStart, uint32 aNumFrames, float32 aAnimDuration, BOOL aLoop)
	{
		mId = aId;
		mStartFrame = aFrameStart-1;
		mNumFrames = aNumFrames;
		mAnimDuration = aAnimDuration;
		mLoop = aLoop;
	}

	//-----------------------------------------------------------StateCondition------------------------------------
	void StateCondition::Init(uint32 aNextState, int32 aIntValue, eConditionType aType, const std::string& aParameter)
	{
		mParameter = aParameter;
		mNextState = aNextState;
		mType = aType;
		mValue.mIntValue = aIntValue;
	}
	void StateCondition::Init(uint32 aNextState, float32 aFloatValue, eConditionType aType, const std::string& aParameter)
	{
		mParameter = aParameter;
		mNextState = aNextState;
		mType = aType;
		mValue.mFloatValue = aFloatValue;
	}
	void StateCondition::Init(uint32 aNextState, eConditionType aType, const std::string& aParameter)
	{
		mParameter = aParameter;
		mNextState = aNextState;
		mType = aType;
	}
} // namespace graphics