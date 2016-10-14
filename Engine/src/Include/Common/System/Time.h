#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

#include "Defs.h"
#include "Types.h"

namespace sys 
{
	/**
	System time access functions
	*/
	class Time {
		SINGLETON_HEAD(Time);
	private:
		static float32									mDeltaSec;
		uint32											lLastUpdateMili;
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
