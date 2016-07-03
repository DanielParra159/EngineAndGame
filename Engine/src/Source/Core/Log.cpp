#include <windows.h>
#include <stdio.h>

#include "Core\Log.h"

namespace core
{
	void LogString(const char* aStr)
	{
		OutputDebugStringA(aStr);
		OutputDebugStringA("\n");
	}

	static char sFormatBuffer[4096];
	void LogFormatString(const char* aFmt, ...)
	{
		va_list lArgs;
		va_start(lArgs, aFmt);
		vsnprintf(sFormatBuffer, 4096, aFmt, lArgs);

		LogString(sFormatBuffer);
	}

} // namespace core

