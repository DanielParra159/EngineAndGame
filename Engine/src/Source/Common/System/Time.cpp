#include "System\Time.h"
#include "Core\Log.h"

#include <stdio.h>

#include <SDL_timer.h>

namespace sys
{
	SINGLETON_BODY(Time);
	float32 Time::mDeltaSec = 0.0f;
	float32 Time::mFixedDeltaSec = 0.0f;


	float64 Time::GetCurrentSec()
	{
		return SDL_GetTicks() / 1000.0;
	}

	float32 Time::GetDeltaSec()
	{
		return Time::mDeltaSec;
	}

	float32 Time::GetFixedDeltaSec()
	{
		return Time::mFixedDeltaSec;
	}

	void Time::Init(float32 aFixedDeltaSec)
	{
		mFixedDeltaSec = aFixedDeltaSec;
	}

	float32 Time::Update()
	{
		uint32 lNewTime = Time::GetCurrentMili();
		float32 lElapsedTime = (lNewTime - lLastUpdateMili) / 1000.0f;

		Time::mDeltaSec = lElapsedTime;

		lLastUpdateMili = lNewTime;

		return lElapsedTime;
	}

	uint32 Time::GetCurrentMili()
	{
		return SDL_GetTicks();
	}
} // sys