#include "Timer.h"

Timer::Timer()
{
	m_Frequency = Time::Frequency();
	m_LastTick = Time::Counter();
	m_StartTick = m_LastTick;
}

Timer::~Timer()
{
	m_Frequency = 0;
	m_LastTick = 0;
	m_StartTick = 0;
}

float Timer::GetElapsedTime()
{
	return float(double(Time::Counter() - m_StartTick) / double(m_Frequency));
}

float Timer::Tick()
{
	UInt64 tick = Time::Counter();
	const float dt = float(double(tick - m_LastTick) / double(m_Frequency));
	m_LastTick = tick;
	return dt;
}
