#ifndef _ENGINE_AUDIO_SOUND3D_H_
#define _ENGINE_AUDIO_SOUND3D_H_

#include "Types.h"
#include "Support\Vector3D.h"

#include "Audio\Sound2D.h"
#include "Audio\AudioManager.h"

#include "fmod.hpp"

#include <string>

namespace audio {
	/**
	Sound wrapper, this class allow to reproduce a 3D sound
	*/
	class Sound3D : public Sound2D
	{
	friend class AudioManager;
	protected:
		/**
		The sound position
		*/
		Vector3D<float32>								mPosition;
		/**
		The sound velocity
		*/
		Vector3D<float32>								mVelocity;
	public:	
		/**
		Plays the sound at the current position
		@param aGroup, the group to which the sound belongs
		@param aLoop, loop mode
		*/
		void											Play(eAudioGroups aGroup, bool aLoop = false);
		/**
		Plays the sound
		@param aGroup, the group to which the sound belongs
		@param aPosition, the position to assign
		@param aLoop, loop mode
		*/
		void											Play(eAudioGroups aGroup, const Vector3D<float32>& aPosition, bool aLoop = false);

		/**
		Set the sound position
		@param aPosition, position to assign
		*/
		void											SetPosition(const Vector3D<float32>& aPosition);

		/**
		Set the sound velocity
		@param aVelocity, velocity to assign
		*/
		void											SetVelocity(const Vector3D<float32>& aVelocity);

	protected:
		Sound3D() {};
		virtual ~Sound3D() {}
	};

} // namespace audio

#endif // _ENGINE_AUDIO_SOUND3D_H_
