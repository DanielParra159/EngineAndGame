#include "Audio\AudioManager.h"
#include "Audio\Sound.h"
//#include "Audio\Sound3D.h"

#include "fmod_errors.h"

#include <algorithm>

namespace audio {

	BOOL ERRCHECK(FMOD_RESULT result){
		if (result != FMOD_OK){
			printf("FMOD error %d - %s", result, FMOD_ErrorString(result));
			return FALSE;
		}
		return TRUE;
	}

	AudioManager* AudioManager::sInstance = 0;

	AudioManager* AudioManager::Instance()
	{
		if (AudioManager::sInstance == 0)
		{
			AudioManager::sInstance = new AudioManager();
			return AudioManager::sInstance;
		}
		return AudioManager::sInstance;
	}
	
	BOOL AudioManager::Init()
	{
		if (!ERRCHECK(FMOD::System_Create(&mFmodSystem)))
			return FALSE;

		int32 driverCount = 0;
		if (!ERRCHECK(mFmodSystem->getNumDrivers(&driverCount)))
			return FALSE;

		if (driverCount == 0)
			return FALSE;

		if (!ERRCHECK(mFmodSystem->init(mNumChannels, FMOD_INIT_NORMAL, 0)))
			return FALSE;

		if (!ERRCHECK(mFmodSystem->set3DSettings(1.0, mDistanceFactor, 1.0f)))
			return FALSE;

		if (!ERRCHECK(mFmodSystem->createChannelGroup(NULL, &mChannelMusic)))
			return FALSE;

		if (ERRCHECK(mFmodSystem->createChannelGroup(NULL, &mChannelEffects)))
			return FALSE;

		SetEffectsVolume(1.0f);
		SetMusicVolume(1.0f);
		mAudioPath = "./assets/audio/";

		mNextChannelId = 0;
		mNumLoadedSounds = 0;

		return TRUE;
	}

	void AudioManager::Release()
	{
		TLoadedSounds::const_iterator lIterator;
		TLoadedSounds::const_iterator lEndElement = mLoadedSounds.end();
		for (lIterator = mLoadedSounds.begin(); lIterator != lEndElement; ++lIterator)
		{
			(*lIterator)->release();
		}
		mLoadedSounds.clear();
		mSoundsIds.clear();

		ERRCHECK(mFmodSystem->close());

		ERRCHECK(mFmodSystem->release());

	}

	/*void AudioManager::setListenerAttributes(const Vector3D<float32> &pos, const Vector3D<float32> &vel, const Vector3D<float32> &forward, const Vector3D<float32> &up)
	{
		FMOD_VECTOR listener_pos = { pos.mX, pos.mY, pos.mZ };
		FMOD_VECTOR listener_vel = { vel.mX, vel.mY, vel.mZ };
		FMOD_VECTOR listener_forward = { forward.mX, forward.mY, forward.mZ };
		FMOD_VECTOR listener_up = { up.mX, up.mY, up.mZ };
		fmodSystem->set3DListenerAttributes(0, &listener_pos, &listener_vel, &listener_forward, &listener_up);
	}*/

	void AudioManager::Update(){
		mFmodSystem->update();
	}

	Sound* AudioManager::CreateSound(const std::string &aFileName)
	{
		Sound *result = 0;

		int32 lSoundId = LoadSound(aFileName);
		if (lSoundId > -1)
		{
			result = new Sound();
			result->Init(lSoundId);
		}

		return result;
	}

	int32 AudioManager::LoadSound(const std::string &aFileName)
	{
		int32 lResult = -1;

		TSoundsIds::const_iterator lSoundterator = mSoundsIds.find(aFileName);

		if (lSoundterator != mSoundsIds.end())
		{
			++lSoundterator->second->mReferences;
			return lSoundterator->second->mId;
		}

		TSound lFmodSound;

		if (ERRCHECK(mFmodSystem->createSound(aFileName.c_str(), FMOD_2D, 0, &lFmodSound)))
		{
			uint32 lCapacity = mLoadedSounds.capacity();
			if (mNumLoadedSounds == lCapacity)
			{
				mLoadedSounds.push_back(lFmodSound);
				lResult = ++lCapacity;
			}
			else
			{
				uint32 lSize = mLoadedSounds.size();
				uint32 i = 0;
				while (i < lSize && mLoadedSounds[i] != 0)
				{
					++i;
				}
				lResult = i;

				if (i < lSize)
				{
					mLoadedSounds[lResult] = lFmodSound;
				}
				else
				{
					mLoadedSounds.push_back(lFmodSound);
				}
			}

			mSoundsIds[aFileName] = new IdReferences(lResult, 1);
			++mNumLoadedSounds;
		}

		return lResult;
	}

	/*Sound3D* AudioManager::createSound3D(const std::string &aKeyName, float minDistance, float maxDistance)
	{
		if (m_soundsName.find(aKeyName) == m_soundsName.end()) return 0;

		if (m_fmodSounds.find(aKeyName) != m_fmodSounds.end())
		{
			Sound3D *sound = new Sound3D(m_fmodSounds[aKeyName], aKeyName);
			m_soundList.push_back(sound);
			return sound;
		}

		TFmodSound fmodSound;
		std::string name = audioPath + m_soundsName[aKeyName];
		if ((result = fmodSystem->createSound(name.c_str(), FMOD_3D, 0, &fmodSound)) != FMOD_OK)
		{
			ERRCHECK(result);
			return 0;
		}

		if ((result = fmodSound->set3DMinMaxDistance(minDistance * DISTANCEFACTOR, maxDistance * DISTANCEFACTOR)) != FMOD_OK)
		{
			ERRCHECK(result);
			return 0;
		}

		Sound3D *sound = new Sound3D(fmodSound, aKeyName);
		m_fmodSounds[aKeyName] = fmodSound;
		m_soundList.push_back(sound);
		return sound;
	}*/

	void AudioManager::PlaySound(Sound *aSound, eAudioGroups aGroup, BOOL aLoop)
	{
		
		TSoundChannel lChannel = 0;
		if (aSound->mChannelId > -1)
		{
			lChannel = mSoundChannels[aSound->mChannelId];
		}

		if (!aLoop)
			mLoadedSounds[aSound->mSoundId]->setMode(FMOD_LOOP_OFF);
		else
		{
			mLoadedSounds[aSound->mSoundId]->setMode(FMOD_LOOP_NORMAL);
			//sound->m_fmodSound->setLoopCount(-1);
		}

		ERRCHECK(mFmodSystem->playSound(mLoadedSounds[aSound->mSoundId], 0, true, &lChannel));
		
		mSoundChannels[++mNextChannelId] = lChannel;
		aSound->mChannelId = mNextChannelId;

		if (aGroup == eAudioGroups::eMusic)
			lChannel->setChannelGroup(mChannelMusic);
		else
			lChannel->setChannelGroup(mChannelEffects);

		lChannel->setPaused(false);

	}

	void AudioManager::StopSound(Sound* aSound)
	{
		TSoundChannel lChannel = mSoundChannels[aSound->mChannelId];
		lChannel->stop();
		delete lChannel;
		mSoundChannels.erase(aSound->mChannelId);
	}

	void AudioManager::PauseSound(Sound* aSound)
	{
		TSoundChannel lChannel = mSoundChannels[aSound->mChannelId];
		lChannel->setPaused(TRUE);
	}

	void AudioManager::ResumeSound(Sound* aSound)
	{
		TSoundChannel lChannel = mSoundChannels[aSound->mChannelId];
		lChannel->setPaused(FALSE);
	}

	void AudioManager::MuteSound(Sound* aSound, BOOL aMute)
	{
		TSoundChannel lChannel = mSoundChannels[aSound->mChannelId];
		lChannel->setMute(aMute);
	}

	BOOL AudioManager::IsPlayingSound(const Sound* aSound)
	{
		TSound lSound;
		TSoundChannel lChannel = mSoundChannels[aSound->mChannelId];
		lChannel->getCurrentSound(&lSound);

		if (lSound != mLoadedSounds[aSound->mSoundId]) return FALSE;

		bool lValue;
		lChannel->isPlaying(&lValue);

		return lValue;
	}

	void AudioManager::SetSoundVolume(Sound *aSound)
	{
		TSound lSound;
		TSoundChannel lChannel = mSoundChannels[aSound->mChannelId];

		lChannel->getCurrentSound(&lSound);

		if (lSound != mLoadedSounds[aSound->mSoundId]) return;

		ERRCHECK(lChannel->setVolume(aSound->mVolume));
	}


	void AudioManager::SetEffectsVolume(float32 aVolume)
	{
		aVolume = std::max(0.0f, std::min(aVolume, 1.0f));
		mChannelEffects->setVolume(aVolume);
	}
	
	void AudioManager::SetMusicVolume(float32 aVolume)
	{
		aVolume = std::max(0.0f, std::min(aVolume, 1.0f));
		mChannelMusic->setVolume(aVolume);
	}

	void AudioManager::StopAllSounds()
	{
		StopAllSounds(eAudioGroups::eEffects);
		StopAllSounds(eAudioGroups::eMusic);
	}

	void AudioManager::StopAllSounds(eAudioGroups aGroup)
	{
		if (aGroup == eAudioGroups::eEffects)
			mChannelEffects->stop();
		else
			mChannelMusic->stop();
	}

	void AudioManager::PauseAllSounds()
	{
		PauseAllSounds(eAudioGroups::eEffects);
		PauseAllSounds(eAudioGroups::eMusic);
	}

	void AudioManager::PauseAllSounds(eAudioGroups aGroup)
	{
		if (aGroup == eAudioGroups::eEffects)
			mChannelEffects->setPaused(true);
		else
			mChannelMusic->setPaused(true);
	}

	void AudioManager::ResumeAllSounds()
	{
		ResumeAllSounds(eAudioGroups::eEffects);
		ResumeAllSounds(eAudioGroups::eMusic);
	}

	void AudioManager::ResumeAllSounds(eAudioGroups aGroup)
	{
		if (aGroup == eAudioGroups::eEffects)
			mChannelEffects->setPaused(false);
		else
			mChannelMusic->setPaused(false);
	}

} // namespace audio
