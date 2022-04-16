#include "Core/Containers/Vector.h"
#include "Core/Containers/Function.h"
#include "Core/Containers/String.h"
#include "Core/Thread/Mutex.h"
#include "Core/Time/Time.h"

class Log
{
public:
	typedef Function<void(const int, const char*)> LogFunction;

	enum
	{
		INFO,
		ERR,
		WARNING
	};

	static void PushFunction(const LogFunction& function);
	static void LogMessageArgs(const int level, const char* fmt, va_list args);
	static void Info(const char* fmt, ...);
	static void Error(const char* fmt, ...);
	static void Warning(const char* fmt, ...);
private:
	static Vector<LogFunction> s_LogFunctions;
	static Mutex s_LogMutex;
};

#define HA_INFO(fmt, ...) Log::Info(fmt, __VA_ARGS__)
#define HA_ERROR(fmt, ...) Log::Error(fmt, __VA_ARGS__)
#define HA_WARNING(fmt, ...) Log::Warning(fmt, __VA_ARGS__)
