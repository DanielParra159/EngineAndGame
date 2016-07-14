#ifndef _ENGINE_AUDIO_SOUND3D_H_
#define _ENGINE_AUDIO_SOUND3D_H_

#include "Types.h"
#include "Support\Vector3D.h"

#include "Audio\Sound.h"
#include "Audio\AudioManager.h"

#include "fmod.hpp"

#include <string>

namespace audio {
	class Sound3D : public Sound
	{
	friend class AudioManager;
	protected:
		Vector3D<float32>								mPosition;
		Vector3D<float32>								mVelocity;
	public:	
		void											Play(eAudioGroups aGroup, bool aLoop = false);
		void											Play(eAudioGroups aGroup, const Vector3D<float32>& aPosition, bool aLoop = false);

		void											SetPosition(const Vector3D<float32>& aPosition);

		void											SetVelocity(const Vector3D<float32>& aVelocity);

	protected:
		Sound3D() {};
		virtual ~Sound3D() {}
	};

} // namespace audio

#endif // _ENGINE_AUDIO_SOUND3D_H_
