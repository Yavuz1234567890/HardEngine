#ifndef DEBUG_H_
#define DEBUG_H_

#include "BasicTypes.h"
#include "PlatformDetection.h"

class Debug
{
public:
	enum
	{
		RED,
		GREEN,
		YELLOW,
		DEFAULT
	};

	static void Init();
	static void Print(const char* out);
	static void SetColor(const int color);
	static void Break();
	static void LogFn(const int level, const char* out);
private:
#if defined(HA_PLATFORM_WINDOWS)
	static void* s_ConsoleHandle;
#endif
};

#endif
