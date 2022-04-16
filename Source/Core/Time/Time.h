#include "Core/Core/BasicTypes.h"

struct SystemTime
{
    UInt Year;
    UInt Month;
    UInt DayOfWeek;
    UInt Day;
    UInt Hour;
    UInt Minute;
    UInt Second;
    UInt Milliseconds;
};

class Time
{
public:
    static UInt64 Counter();
    static UInt64 Frequency();
    static void Sleep(UInt milliseconds);
    static void GetSystemTime(SystemTime* in);
};
