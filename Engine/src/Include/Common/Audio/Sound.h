#ifndef _ENGINE_AUDIO_SOUND_H_
#define _ENGINE_AUDIO_SOUND_H_

#include "Audio/AudioManager.h"

#include "fmod.hpp"

#include <string>

namespace audio {
	class Sound
	{
	friend class AudioManager;
	protected:
		int32											mSoundId;
		int32											mChannelId;
		float											mVolume;
	public:	
		typedef FMOD::Sound* TFmodSound;

		virtual void									Play(eAudioGroups aGroup, BOOL aLoop = false);
		virtual void									Stop();
		virtual void									Pause();
		virtual void									Resume();

		virtual void									SetMute(BOOL aMute);
		virtual BOOL									IsPlaying();

	protected:
		Sound() {}
		virtual ~Sound() {}

		virtual void									Init(int32 aSoundId);
		virtual void									Release();
	};

} // namespace audio

#endif // _ENGINE_AUDIO_SOUND_H_
