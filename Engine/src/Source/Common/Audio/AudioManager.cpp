#include "Audio\AudioManager.h"
#include "Audio\Sound2D.h"
#include "Audio\Sound3D.h"

#include "IO\FileSystem.h"

#include "fmod_errors.h"

#include <algorithm>
#include <iostream>
#include <cmath>
#include <cerrno>
#include <cfenv>

#include <assert.h>


namespace audio {

	BOOL ERRCHECK(FMOD_RESULT result){
		if (result != FMOD_OK){
			printf("FMOD error %d - %s", result, FMOD_ErrorString(result));
			return FALSE;
		}
		return TRUE;
	}

	SINGLETON_BODY(AudioManager);
	
	BOOL AudioManager::Init(float32 aDistanceFactor)
	{
		if (!ERRCHECK(FMOD::System_Create(&mAudioSystem)))
			assert(FALSE);

		int32 driverCount = 0;
		if (!ERRCHECK(mAudioSystem->getNumDrivers(&driverCount)))
			assert(FALSE);

		if (driverCount == 0)
			assert(FALSE);

		if (!ERRCHECK(mAudioSystem->init(mNumChannels, FMOD_INIT_NORMAL, 0)))
			assert(FALSE);

		if (!ERRCHECK(mAudioSystem->set3DSettings(1.0, aDistanceFactor, 1.0f)))
			assert(FALSE);

		if (!ERRCHECK(mAudioSystem->createChannelGroup(NULL, &mChannelMusic)))
			assert(FALSE);

		if (!ERRCHECK(mAudioSystem->createChannelGroup(NULL, &mChannelEffects)))
			assert(FALSE);

		mDistanceFactor = aDistanceFactor;

		SetEffectsVolume(0.0f);
		SetMusicVolume(0.0f);

		mNextChannelId = 0;
		mNumLoadedSounds = 0;

		return TRUE;
	}

	void AudioManager::Release()
	{
		LOOP_ITERATOR(TLoadedSounds::const_iterator, mLoadedSounds, lIterator, lEndElement)
		{
			(*lIterator)->release();
		}
		mLoadedSounds.clear();
		mSoundsIds.clear();

		ERRCHECK(mAudioSystem->close());

		ERRCHECK(mAudioSystem->release());

	}

	void AudioManager::SetListenerAttributes(const Vector3D<float32>& aPosition, const Vector3D<float32>& aVelocity,
											 const Vector3D<float32>& aForward, const Vector3D<float32>& aUp)
	{
		FMOD_VECTOR listener_pos = { EXPOSE_VECTOR3D(aPosition) };
		FMOD_VECTOR listener_vel = { EXPOSE_VECTOR3D(aVelocity) };
		FMOD_VECTOR listener_forward = { EXPOSE_VECTOR3D(aForward) };
		FMOD_VECTOR listener_up = { EXPOSE_VECTOR3D(aUp) };
		mAudioSystem->set3DListenerAttributes(0, &listener_pos, &listener_vel, &listener_forward, &listener_up);
	}

	void AudioManager::Update(){
		mAudioSystem->update();
	}

	Sound2D* AudioManager::CreateSound2D(const std::string &aFileName)
	{
		Sound2D *lResult = NULL;

		int32 lSoundId = LoadSound2D(aFileName);
		if (lSoundId > -1)
		{
			lResult = new Sound2D();
			lResult->Init(lSoundId);
		}

		return lResult;
	}

	Sound3D* AudioManager::CreateSound3D(const std::string &aFileName, float32 aMinDistance, float32 aMaxDistance)
	{
		Sound3D *lResult = NULL;

		int32 lSoundId = LoadSound3D(aFileName, aMinDistance, aMaxDistance);

		if (lSoundId > -1)
		{
			lResult = new Sound3D();
			lResult->Init(lSoundId);
		}

		return lResult;
	}


	int32 AudioManager::LoadSound2D(const std::string &aFileName)
	{
		int32 lResult = -1;

		TSoundsIds::const_iterator lSoundterator = mSoundsIds.find(aFileName);

		if (lSoundterator != mSoundsIds.end())
		{
			++lSoundterator->second->mReferences;
			return lSoundterator->second->mId;
		}

		TSound lSound;

		if (ERRCHECK(mAudioSystem->createSound((io::FileSystem::Instance()->GetCurrentDir() + "\\" + aFileName).c_str(), FMOD_2D, 0, &lSound)))
		{
			lResult = AddSoundToList(aFileName, lSound); 
		}

		return lResult;
	}

	int32 AudioManager::LoadSound3D(const std::string &aFileName, float32 aMinDistance, float32 aMaxDistance)
	{
		int32 lResult = -1;

		TSoundsIds::const_iterator lSoundterator = mSoundsIds.find(aFileName);

		if (lSoundterator != mSoundsIds.end())
		{
			++lSoundterator->second->mReferences;
			return lSoundterator->second->mId;
		}

		TSound lSound;

		if (ERRCHECK(mAudioSystem->createSound((io::FileSystem::Instance()->GetCurrentDir() + "\\" + aFileName).c_str(), FMOD_3D, 0, &lSound)))
		{
			if (ERRCHECK(lSound->set3DMinMaxDistance(aMinDistance * mDistanceFactor, aMaxDistance * mDistanceFactor)))
			{
				lResult = AddSoundToList(aFileName, lSound);
			}
		}

		return lResult;
	}

	int32 AudioManager::AddSoundToList(const std::string &aFileName, TSound aSound)
	{
		int32 lResult = -1;

		uint32 lCapacity = mLoadedSounds.capacity();
		if (mNumLoadedSounds == lCapacity)
		{
			mLoadedSounds.push_back(aSound);
			lResult = lCapacity;
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
				mLoadedSounds[lResult] = aSound;
			}
			else
			{
				mLoadedSounds.push_back(aSound);
			}
		}

		mSoundsIds[aFileName] = new IdReferences(lResult, 1);
		++mNumLoadedSounds;

		return lResult;
	}

	void AudioManager::PlaySound(Sound2D *aSound, eAudioGroups aGroup, BOOL aLoop)
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

		if (ERRCHECK(mAudioSystem->playSound(mLoadedSounds[aSound->mSoundId], 0, true, &lChannel)))
		{

			mSoundChannels[++mNextChannelId] = lChannel;
			aSound->mChannelId = mNextChannelId;

			if (aGroup == eAudioGroups::eMusic)
				lChannel->setChannelGroup(mChannelMusic);
			else
				lChannel->setChannelGroup(mChannelEffects);

			lChannel->setPaused(false);
		}

	}

	void AudioManager::StopSound(Sound2D* aSound)
	{
		TSoundChannel lChannel = mSoundChannels[aSound->mChannelId];
		lChannel->stop();
		//delete lChannel;
		mSoundChannels.erase(aSound->mChannelId);
	}

	void AudioManager::PauseSound(Sound2D* aSound)
	{
		TSoundChannel lChannel = mSoundChannels[aSound->mChannelId];
		lChannel->setPaused(TRUE);
	}

	void AudioManager::ResumeSound(Sound2D* aSound)
	{
		TSoundChannel lChannel = mSoundChannels[aSound->mChannelId];
		lChannel->setPaused(FALSE);
	}

	void AudioManager::MuteSound(Sound2D* aSound, BOOL aMute)
	{
		TSoundChannel lChannel = mSoundChannels[aSound->mChannelId];
		lChannel->setMute(aMute);
	}

	BOOL AudioManager::IsPlayingSound(const Sound2D* aSound)
	{
		TSound lSound;
		TSoundChannel lChannel = mSoundChannels[aSound->mChannelId];
		lChannel->getCurrentSound(&lSound);

		if (lSound != mLoadedSounds[aSound->mSoundId]) return FALSE;

		bool lValue;
		lChannel->isPlaying(&lValue);

		return lValue;
	}

	void AudioManager::SetSoundVolume(Sound2D *aSound)
	{
		TSound lSound;
		TSoundChannel lChannel = mSoundChannels[aSound->mChannelId];

		lChannel->getCurrentSound(&lSound);

		if (lSound != mLoadedSounds[aSound->mSoundId]) return;

		ERRCHECK(lChannel->setVolume(aSound->mVolume));
	}

	void AudioManager::SetSound3DAttributes(Sound3D *aSound)
	{
		FMOD_VECTOR lPosition = { EXPOSE_VECTOR3D(aSound->mPosition) };
		FMOD_VECTOR lVelocity = { EXPOSE_VECTOR3D(aSound->mVelocity) };
		
		mSoundChannels[aSound->mChannelId]->set3DAttributes(&lPosition, &lVelocity);
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
