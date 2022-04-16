#include "Core/Time/Time.h"

#include <time.h>
#include <unistd.h>

UInt64 Time::Counter()
{
	timespec counter;
	clock_gettime(CLOCK_REALTIME, &counter);
	return UInt64(counter.tv_sec) * 1000000000 + UInt64(tick.tv_nsec);
}

UInt64 Time::Frequency()
{
	return 1'000'000'000;
}

void Time::Sleep(UInt milliseconds)
{
	if (milliseconds) usleep(useconds_t(milliseconds * 1000));
}

void Time::GetSystemTime(SystemTime* in)
{
	struct timeval time;
	gettimeofday(&time, nullptr);
	struct tm localTime;
	localtime_r(&time.tv_sec, &localTime);

	in->Year = localTime.tm_year + 1900;
	in->Month = localTime.tm_mon + 1;
	in->DayOfWeek = localTime.tm_wday;
	in->Day = localTime.tm_mday;
	in->Hour = localTime.tm_hour;
	in->Minute = localTime.tm_min;
	in->Second = localTime.tm_sec;
	in->Milliseconds = time.tv_usec / 1000;
}
