#include "Log.h"

Vector<Log::LogFunction> Log::s_LogFunctions;
Mutex Log::s_LogMutex;

void Log::LogMessageArgs(const int level, const char* fmt, va_list args)
{
	String buffer;
	buffer.AppendFormatArgs(fmt, args);
	s_LogMutex.Lock();
	for (int i = 0; i < s_LogFunctions.Size(); i++)
	{
		s_LogFunctions[i](level, buffer.CData());
	}
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
