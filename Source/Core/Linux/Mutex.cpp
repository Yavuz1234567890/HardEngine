#include "Core/Thread/Mutex.h"

Mutex::Mutex()
{
	const int status = pthread_mutex_init(&m_Base, nullptr);
}

Mutex::~Mutex()
{
	const int status = pthread_mutex_destroy(&m_Base);
}

void Mutex::Lock()
{
	const int status = pthread_mutex_lock(&m_Base);
}

void Mutex::Unlock()
{
	const int status = pthread_mutex_unlock(&m_Base);
}
