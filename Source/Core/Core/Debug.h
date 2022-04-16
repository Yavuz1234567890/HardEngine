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
private:
#if defined(HA_PLATFORM_WINDOWS)
	static void* s_ConsoleHandle;
#endif
};
