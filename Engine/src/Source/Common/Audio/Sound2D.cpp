#include "Audio\Sound2D.h"

#include <cassert>
#include <algorithm>    // std::max


namespace audio {

	void Sound2D::Init(int32 aSoundId)
	{
		mSoundId = aSoundId;
		mChannelId = -1;
		mVolume = 0;
	}

	void Sound2D::Release()
	{
		
	}

	void Sound2D::Play(eAudioGroups aGroup, BOOL aLoop)
	{
		AudioManager::Instance()->PlaySound(this, aGroup, aLoop);
	}

	void Sound2D::Stop()
	{
		return AudioManager::Instance()->StopSound(this);
	}

	void Sound2D::Pause()
	{
		return AudioManager::Instance()->PauseSound(this);
	}

	void Sound2D::Resume()
	{
		return AudioManager::Instance()->ResumeSound(this);
	}

	void Sound2D::SetMute(BOOL aMute)
	{
		return AudioManager::Instance()->MuteSound(this, aMute);
	}

	BOOL Sound2D::IsPlaying()
	{
		return AudioManager::Instance()->IsPlayingSound(this);
	}

} // namespace Audio
