#ifndef _ENGINE_AUDIO_SOUND_H_
#define _ENGINE_AUDIO_SOUND_H_

#include "Audio/AudioManager.h"

#include "fmod.hpp"

#include <string>

namespace audio {
	/**
	Sound wrapper, this class allow to reproduce a 2D sound
	*/
	class Sound2D
	{
	friend class AudioManager;
	protected:
		/**
		The sound id
		*/
		int32											mSoundId;
		/**
		The channel id
		*/
		int32											mChannelId;
		/**
		Sound volume
		*/
		float32											mVolume;
	public:	
		/**
		Plays the sound
		@param aGroup, the group to which the sound belongs
		@param aLoop, loop mode
		*/
		virtual void									Play(eAudioGroups aGroup, BOOL aLoop = false);
		/**
		Stop the sound
		*/
		virtual void									Stop();
		/**
		Pause the sound
		*/
		virtual void									Pause();
		/**
		Resume the sound
		*/
		virtual void									Resume();

		/**
		Mutes the sound
		@param aMute, TRUE to mute
		*/
		virtual void									SetMute(BOOL aMute);
		/**
		Check if the sound is playing
		*/
		virtual BOOL									IsPlaying();

	protected:
		Sound2D() {}
		virtual ~Sound2D() {}

		virtual void									Init(int32 aSoundId);
		virtual void									Release();
	};

} // namespace audio

#endif // _ENGINE_AUDIO_SOUND_H_
