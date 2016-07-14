#ifndef _ENGINE_AUDIO_AUDIOMANAGER_H_
#define _ENGINE_AUDIO_AUDIOMANAGER_H_

#include "Types.h"
//#include "Support\Vector3D.h"
#include "Support\IdReferences.h"

#include "fmod.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace audio {

	enum eAudioGroups
	{
		eEffects, 
		eMusic
	};

	class AudioManager
	{
	friend class Sound;
	//friend class Sound3D;

	typedef FMOD::Sound*										TSound;
	typedef FMOD::Channel*										TSoundChannel;
	typedef FMOD::ChannelGroup*									TChannelGroup;
	typedef std::unordered_map<std::string, IdReferences*>		TSoundsIds;
	typedef std::vector<TSound>									TLoadedSounds;
	typedef std::unordered_map<int32, TSoundChannel>			TSoundChannels;

	private:
		static AudioManager*							sInstance;

		TSoundsIds										mSoundsIds;
		TLoadedSounds									mLoadedSounds;
		uint32											mNumLoadedSounds;
		TSoundChannels									mSoundChannels;

		FMOD_RESULT										mResult;
		FMOD::System*									mFmodSystem;
		std::string										mAudioPath;
		const int32										mNumChannels = 36;
		int32											mNextChannelId;
		TChannelGroup									mChannelMusic;
		TChannelGroup									mChannelEffects;
		const float32									mDistanceFactor = 1.0f; // Units per meter. @TODO: configurable


	public:
		static AudioManager*							Instance();

		BOOL											Init();
		void											Update();
		void											Release();

		//void setListenerAttributes(const Vector3D<float32> &pos, const Vector3D<float32> &vel, const Vector3D<float32> &forward, const Vector3D<float32> &up);

		Sound*											CreateSound(const std::string &aFileName);
		//Sound3D* createSound3D(const std::string &keyName, float minDistance, float maxDistance);

		void											SetEffectsVolume(float32 aVolume);
		void											SetMusicVolume(float32 aVolume);

		void											StopAllSounds();
		void											StopAllSounds(eAudioGroups aGroup);

		void											PauseAllSounds();
		void											PauseAllSounds(eAudioGroups aGroup);

		void											ResumeAllSounds();
		void											ResumeAllSounds(eAudioGroups aGroup);

	private:
		AudioManager() : mSoundsIds (), mLoadedSounds(), mSoundChannels(){}
		~AudioManager() {}

		int32											LoadSound(const std::string &aFileName);

		void PlaySound(Sound* aSound, eAudioGroups aGroup, BOOL aLoop = false);
		void StopSound(Sound* aSound);
		void PauseSound(Sound* aSound);
		void ResumeSound(Sound* aSound);
		void MuteSound(Sound* aSound, BOOL aMute);
		BOOL IsPlayingSound(const Sound* aSound);
		void SetSoundVolume(Sound* aSound);
	};

} // namespace audio

#endif // _ENGINE_AUDIO_AUDIOMANAGER_H_
