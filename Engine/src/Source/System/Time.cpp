#include "System\Time.h"

#include <SDL_timer.h>

namespace sys
{
	double GetCurrentSec()
	{
		return SDL_GetTicks() / 1000.0;
	}

	uint32 GetCurrentMili()
	{
		return SDL_GetTicks();
	}
} // sys