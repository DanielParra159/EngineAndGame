#include "Audio\Sound3D.h"

#include <cassert>
#include <algorithm>    // std::max


namespace audio {

	void Sound3D::Play(eAudioGroups aGroup, bool aLoop)
	{
		AudioManager* lAudioManager = AudioManager::Instance();
		lAudioManager->PlaySound(this, aGroup, aLoop);
		lAudioManager->SetSound3DAttributes(this);
		lAudioManager->ResumeSound(this);
	}

	void Sound3D::Play(eAudioGroups aGroup, const Vector3D<float32>& aPosition, bool aLoop)
	{
		SetPosition(aPosition);
		Play(aGroup, aLoop);
	}

	void Sound3D::SetPosition(const Vector3D<float32>& aPosition)
	{
		mPosition.mX = aPosition.mX;
		mPosition.mY = aPosition.mY;
		mPosition.mZ = aPosition.mZ;
		
		if (mChannelId > -1 && IsPlaying())
			AudioManager::Instance()->SetSound3DAttributes(this);
	}

	void Sound3D::SetVelocity(const Vector3D<float32>& aVelocity)
	{
		mVelocity.mX = aVelocity.mX;
		mVelocity.mY = aVelocity.mY;
		mVelocity.mZ = aVelocity.mZ;

		if (mChannelId > -1 && IsPlaying())
			AudioManager::Instance()->SetSound3DAttributes(this);
	}

} // namespace audio
