#ifndef TIMER_H_
#define TIMER_H_

#include "Core/Time/Time.h"

class Timer
{
public:
	Timer();
	~Timer();

	float GetElapsedTime();
	float Tick();
private:
	UInt64 m_Frequency;
	UInt64 m_LastTick, m_StartTick;
};

#endif
