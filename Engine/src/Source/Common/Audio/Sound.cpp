#include "Audio\Sound.h"

#include <cassert>
#include <algorithm>    // std::max


namespace audio {

	void Sound::Init(int32 aSoundId)
	{
		mSoundId = aSoundId;
		mChannelId = -1;
	}

	void Sound::Release()
	{
		
	}

	void Sound::Play(eAudioGroups aGroup, BOOL aLoop)
	{
		AudioManager::Instance()->PlaySound(this, aGroup, aLoop);
	}

	void Sound::Stop()
	{
		return AudioManager::Instance()->StopSound(this);
	}

	void Sound::Pause()
	{
		return AudioManager::Instance()->PauseSound(this);
	}

	void Sound::Resume()
	{
		return AudioManager::Instance()->ResumeSound(this);
	}

	void Sound::SetMute(BOOL aMute)
	{
		return AudioManager::Instance()->MuteSound(this, aMute);
	}

	BOOL Sound::IsPlaying()
	{
		return AudioManager::Instance()->IsPlayingSound(this);
	}

} // namespace Audio
