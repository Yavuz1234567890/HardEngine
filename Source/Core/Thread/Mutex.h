#ifndef MUTEX_H_
#define MUTEX_H_

#include "Core/Core/BasicTypes.h"
#include "Core/Core/PlatformDetection.h"

#if defined(HA_PLATFORM_LINUX)
#include <pthread.h>
#endif

class Mutex
{
public:
	Mutex();
	~Mutex();

	void Lock();
	void Unlock();
private:
#if defined(HA_PLATFORM_WINDOWS)
	void* m_Base;
#elif defined(HA_PLATFORM_LINUX)
	pthread_mutex_t m_Base;
#endif
};

#endif
