#include "Graphics/SpriteAnimator.h"

#include "Graphics/RenderManager.h"
#include "Graphics/Texture.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"

#include "System/Time.h"

#include "Core/Log.h"

#include "Support/Math.h"

#include <GL/glew.h>

namespace graphics
{
	float32 sVertexData[] = {
		// X      Y     Z     Nx    Ny     Nz    U     V
		//Front
		-0.5f, -0.5f,  0.0f, 0.0f ,0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.0f, 0.0f ,0.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.0f, 0.0f ,0.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.0f, 0.0f ,0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.0f, 0.0f ,0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.0f, 0.0f ,0.0f, 1.0f, 0.0f, 1.0f
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

		LOOP_ITERATOR(TStates::iterator, mStates, lIterator, lEndElement) {
			delete lIterator->second;
		}
		mStates.clear();
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

		float32 UMin = lXFrame * mFrameWidth / mMaterial->GetDiffuseTexture()->GetWidth();
		float32 VMin = lYFrame * mFrameHeight / mMaterial->GetDiffuseTexture()->GetHeight();
		float32 UMax = (lXFrame +1) * mFrameWidth / mMaterial->GetDiffuseTexture()->GetWidth();
		float32 VMax = (lYFrame + 1) * mFrameHeight / mMaterial->GetDiffuseTexture()->GetHeight();

		sVertexData[6] = sVertexData[38] = sVertexData[46] = UMin;
		sVertexData[23] = sVertexData[31] = sVertexData[39] = VMin;
		sVertexData[14] = sVertexData[22] = sVertexData[30] = UMax;
		sVertexData[7] = sVertexData[15] = sVertexData[47] = VMax;

		mMaterial->UseMaterial();
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(sVertexData), sVertexData);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//RenderManager::Instance()->RenderSpriteAnimator(aPosition, aScale, aRotation, this);

		Matrix4 lModelMatrix;
		Matrix4x4::translate(&lModelMatrix, aPosition);
		Matrix4x4::rotate(&lModelMatrix, aRotation);
		Matrix4x4::scale(&lModelMatrix, aScale);


		static float32 lLihgtPosX = 0.0f;
		static int32 lSign = 1;
		lLihgtPosX += sys::Time::GetDeltaSec() * lSign * 4;
		if (Math::Abs(lLihgtPosX) > 50.0f)
			lSign *= -1;

		Camera* lRenderCamera = RenderManager::Instance()->GetRenderCamera();

		mMaterial->PrepareToRender(&lModelMatrix, lRenderCamera->GetCameraPosition(), Vector3D<float32>(1.0f, 1.0f, 1.0f), Vector3D<float32>(lLihgtPosX, 8.0f, 3.0f));
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
		if (!mCurrentState->mPlaying)
			return;

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
		mCurrentState->mPlaying = TRUE;
	}

	void SpriteAnimator::AddState(uint32 aId, uint32 aFrameStart, uint32 aNumFrames, float32 aAnimDuration, BOOL aLoop)
	{
		AnimateSpriteState* lAnimateSpriteState = new AnimateSpriteState();
		lAnimateSpriteState->Init(aFrameStart, aNumFrames, aAnimDuration, aLoop);

		mStates.insert(std::pair<int32, AnimateSpriteState*>(aId, lAnimateSpriteState));
	}

	//-----------------------------------------------------------AnimateSpriteState------------------------------------

	void AnimateSpriteState::Init(uint32 aFrameStart, uint32 aNumFrames, float32 aAnimDuration, BOOL aLoop)
	{
		mStartFrame = aFrameStart;
		mNumFrames = aNumFrames;
		mAnimDuration = aAnimDuration;
		mLoop = aLoop;
	}
} // namespace graphics