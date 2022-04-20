#include "Log.h"
#include "Core/Core/Debug.h"

#include <string.h>

Mutex Log::s_LogMutex;
File Log::s_LogFile;

void Log::Init()
{
	s_LogFile.Open(File::WRITABLE, "Log.txt");
}

void Log::LogMessageArgs(const int level, const char* fmt, va_list args)
{
	String buffer;
	buffer.AppendFormatArgs(fmt, args);
	s_LogMutex.Lock();
	Debug::LogFn(level, buffer.CData());
	LogToFile(level, buffer.CData());
}

void Log::Info(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	LogMessageArgs(INFO, fmt, args);
	va_end(args);
}

void Log::Error(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	LogMessageArgs(ERR, fmt, args);
	va_end(args);
}

void Log::Warning(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	LogMessageArgs(WARNING, fmt, args);
	va_end(args);
}

void Log::LogToFile(const int level, const char* out)
{
	if (level == Log::INFO)
	{
		s_LogFile.Write("[Info] ", strlen("[Info] "));
	}
	if (level == Log::ERR)
	{
		s_LogFile.Write("[Error] ", strlen("[Error] "));
	}
	if (level == Log::WARNING)
	{
		s_LogFile.Write("[Warning] ", strlen("[Warning] "));
	}
	s_LogFile.Write(out, strlen(out));
	s_LogFile.Write("\n", 1);
}
