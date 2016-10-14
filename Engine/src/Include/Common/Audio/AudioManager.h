#ifndef _ENGINE_AUDIO_AUDIOMANAGER_H_
#define _ENGINE_AUDIO_AUDIOMANAGER_H_

#include "Defs.h"
#include "Types.h"
#include "Support\Vector3D.h"
#include "Support\IdReferences.h"

#include "fmod.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace audio {

	/**
	Groups that Sound can belong
	*/
	enum eAudioGroups
	{
		eEffects, 
		eMusic
	};

	/**
	This manager is responsible for reproduce and manage sounds 
	*/
	class AudioManager
	{
	friend class Sound2D;
	friend class Sound3D;

	typedef FMOD::Sound*										TSound;
	typedef FMOD::Channel*										TSoundChannel;
	typedef FMOD::ChannelGroup*									TChannelGroup;
	typedef std::unordered_map<std::string, IdReferences*>		TSoundsIds;
	typedef std::vector<TSound>									TLoadedSounds;
	typedef std::unordered_map<int32, TSoundChannel>			TSoundChannels;

	SINGLETON_HEAD(AudioManager);
	private:
		/**
		Sounds ids list referenced by name
		*/
		TSoundsIds										mSoundsIds;
		/**
		All the sounds loaded
		*/
		TLoadedSounds									mLoadedSounds;
		/**
		Num of loaded sounds
		*/
		uint32											mNumLoadedSounds;
		/**
		Channels list referenced by channel id
		*/
		TSoundChannels									mSoundChannels;

		FMOD::System*									mAudioSystem;
		TChannelGroup									mChannelMusic;
		TChannelGroup									mChannelEffects;
		const int32										mNumChannels = 36;
		/**
		It's used to reference in mSoundChannels
		*/
		int32											mNextChannelId;
		/**
		Units per meter
		*/
		float32											mDistanceFactor;


	public:
		BOOL											Init(float32 aDistanceFactor);
		void											Update();
		void											Release();

		/**
		Set the listener attributes for 3D sound
		@param aPosition, position of listener
		@param aVelocity, velocity of listener
		@param aForward, forward of listener
		@param aUp, up of listener
		*/
		void											SetListenerAttributes(const Vector3D<float32>& aPosition, const Vector3D<float32>& aVelocity,
																			  const Vector3D<float32>& aForward, const Vector3D<float32>& aUp);
		/**
		Create a 2D sound
		@param aFileName, sound name
		@return The sound created or null
		*/
		Sound2D*											CreateSound2D(const std::string &aFileName);
		/**
		Create a 3D sound
		@param aFileName, sound name
		@param aMinDistance, minimum distance that you can hear the sound
		@param aMaxDistance, maximum distance that you can hear the sound
		@return The sound created or null
		*/
		Sound3D*										CreateSound3D(const std::string &aFileName, float32 aMinDistance, float32 aMaxDistance);

		/**
		Set volume to all sounds in the effects group
		@param aVolume, volume to set
		*/
		void											SetEffectsVolume(float32 aVolume);
		/**
		Set volume to all sounds in the music group
		@param aVolume, volume to set
		*/
		void											SetMusicVolume(float32 aVolume);

		/**
		Stop all sounds
		*/
		void											StopAllSounds();
		/**
		Stop all sounds in a specific group
		@param aGroup, the group
		*/
		void											StopAllSounds(eAudioGroups aGroup);

		/**
		Pause all sounds
		*/
		void											PauseAllSounds();
		/**
		Pause all sounds in a specific group
		@param aGroup, the group
		*/
		void											PauseAllSounds(eAudioGroups aGroup);

		/**
		Resume all sounds
		*/
		void											ResumeAllSounds();
		/**
		Resume all sounds in a specific group
		@param aGroup, the group
		*/
		void											ResumeAllSounds(eAudioGroups aGroup);

	private:
		AudioManager() : mSoundsIds (), mLoadedSounds(), mSoundChannels(){}
		~AudioManager() {}

		/**
		Internal function to load a 2D sound
		@param aFileName, the sound to load
		@return sound id or -1
		*/
		int32											LoadSound2D(const std::string &aFileName);
		/**
		Internal function to load a 3D sound
		@param aFileName, the sound to load
		@param aMinDistance, minimum distance that you can hear the sound
		@param aMaxDistance, maximum distance that you can hear the sound
		@return sound id or -1
		*/
		int32											LoadSound3D(const std::string &aFileName, float32 aMinDistance, float32 aMaxDistance);
		/**
		Internal function to add a sound to the list of loaded sounds
		@param aFileName, the sound name to add, used as key
		@param aSound, the sound to add
		@return sound id or -1
		*/
		int32											AddSoundToList(const std::string &aFileName, TSound aSound);

		/**
		Play a sound
		@param aSound, the sound to play
		@param aGroup, the group to which the sound belongs
		@param aLoop, loop mode
		*/
		void PlaySound(Sound2D* aSound, eAudioGroups aGroup, BOOL aLoop = false);
		/**
		Stop a sound
		@param aSound, the sound to stop
		*/
		void StopSound(Sound2D* aSound);
		/**
		Pause a sound
		@param aSound, the sound to pause
		*/
		void PauseSound(Sound2D* aSound);
		/**
		Resume a sound
		@param aSound, the sound to resume
		*/
		void ResumeSound(Sound2D* aSound);
		/**
		Mutes a sound
		@param aSound, the sound to stop
		@param aMute, TRUE to mute
		*/
		void MuteSound(Sound2D* aSound, BOOL aMute);
		/**
		Check if a sound is playing
		@param aSound, the sound to check
		@return TRUE if is playing
		*/
		BOOL IsPlayingSound(const Sound2D* aSound);
		/**
		Set the volume to a sound
		@param aSound, the sound to set the volumen
		*/
		void SetSoundVolume(Sound2D* aSound);

		/**
		Set the 3D attributes to a sound (position and velocity)
		@param aSound, the sound set to the attributes
		*/
		void SetSound3DAttributes(Sound3D *aSound);
	};

} // namespace audio

#endif // _ENGINE_AUDIO_AUDIOMANAGER_H_
