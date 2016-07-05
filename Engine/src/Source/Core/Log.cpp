#define VC_EXTRALEAN  // tells windows not include unnecessary stuff
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>

#include "Core\Log.h"

namespace core
{
	void LogString(const char* aStr)
	{
		printf(aStr);
		printf("\n");
		/*
		OutputDebugStringA(aStr);
		OutputDebugStringA("\n");
		*/
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

