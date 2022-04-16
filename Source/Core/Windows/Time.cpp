#include "Core/Time/Time.h"
#include "Core/Core/PlatformDetection.h"

#include <windows.h>

UInt64 Time::Counter()
{
	UInt64 counter = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter);
	return counter;
}

UInt64 Time::Frequency()
{
	UInt64 frequency = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	return frequency;
}

void Time::Sleep(UInt milliseconds)
{
	::Sleep((DWORD)milliseconds);
}

void Time::GetSystemTime(SystemTime* in)
{
	SYSTEMTIME time;
	::GetLocalTime(&time);
	in->Year = time.wYear;
	in->Month = time.wMonth;
	in->DayOfWeek = time.wDayOfWeek;
	in->Day = time.wDay;
	in->Hour = time.wHour;
	in->Minute = time.wMinute;
	in->Second = time.wSecond;
	in->Milliseconds = time.wMilliseconds;
}
