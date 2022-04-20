#ifndef LOG_H_
#define LOG_H_

#include "Core/Containers/Vector.h"
#include "Core/Containers/Function.h"
#include "Core/Containers/String.h"
#include "Core/Thread/Mutex.h"
#include "Core/Time/Time.h"
#include "Core/File/File.h"

class Log
{
public:
	enum
	{
		INFO,
		ERR,
		WARNING
	};

	static void Init();
	static void LogMessageArgs(const int level, const char* fmt, va_list args);
	static void Info(const char* fmt, ...);
	static void Error(const char* fmt, ...);
	static void Warning(const char* fmt, ...);
private:
	static void LogToFile(const int level, const char* out);

	static Mutex s_LogMutex;
	static File s_LogFile;
};

#define HA_INFO(fmt, ...) Log::Info(fmt, __VA_ARGS__)
#define HA_ERROR(fmt, ...) Log::Error(fmt, __VA_ARGS__)
#define HA_WARNING(fmt, ...) Log::Warning(fmt, __VA_ARGS__)

#endif
