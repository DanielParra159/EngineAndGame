#ifndef _ENGINE_CORE_LOG_H_
#define _ENGINE_CORE_LOG_H_
//  Very basic log funtions to output strings and formated strings.

namespace core
{
	//  Print a string
	void											LogString (const char* aStr);
    
	//  Print a printf like formated string, output is limited to 4095 character.
	void											LogFormatString (const char* aFmt, ...);

} // namespace core
#endif // _ENGINE_CORE_LOG_H_
