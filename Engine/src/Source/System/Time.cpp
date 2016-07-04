#include "System\Time.h"

#include <SDL_timer.h>

namespace sys
{
	float64 Time::GetCurrentSec()
	{
		return SDL_GetTicks() / 1000.0;
	}

	float32 Time::GetDeltaSec()
	{
		return mDeltaSec;
	}

	void Time::SetDeltaSec(float32 aDeltaSec)
	{
		mDeltaSec = aDeltaSec;
	}

	uint32 Time::GetCurrentMili()
	{
		return SDL_GetTicks();
	}
} // sys