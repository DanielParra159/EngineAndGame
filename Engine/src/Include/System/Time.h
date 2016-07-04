#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_
//  System time access functions, you application has to be time aware as undelaying hardware
//  may vary or evan the clock spped can vary during execution.

#include "Types.h"

namespace sys 
{
	static class Time {
	private:
		static float32									mDeltaSec;
	public:
		/**
		Get the number of seconds since the aplication start
		@return seconds since the Aplication start
		*/
		static float64									GetCurrentSec();
		/**
		Get the number of milliseconds since the aplication start
		@return milliseconds since the aplication start
		*/
		static uint32									GetCurrentMili();
		/**
		Get the number of seconds since the last update
		@return seconds since the last update
		*/
		static float32									GetDeltaSec();
	private:
		/**
		Set the number of seconds since the last update
		@param seconds since the last update
		*/
		static void										SetDeltaSec(float32 aDeltaSec);
	};

} // namespace sys 

#endif // _SYS_TIME_H_
