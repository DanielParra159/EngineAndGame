#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_
//  System time access functions, you application has to be time aware as undelaying hardware
//  may vary or evan the clock spped can vary during execution.

#include "Types.h"

namespace sys 
{
	class Time {
	private:
		static Time*									sInstance;
		static float32									mDeltaSec;
		uint32											lLastUpdateMili;
	public:
		static Time*									Instance();
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

		/**
		Update the deltaSec passed since the last update
		*/
		void Update();
	private:
		Time() {}
		~Time() {}
	};

} // namespace sys 

#endif // _SYS_TIME_H_
