#include "Core/Thread/Mutex.h"

#include <windows.h>

Mutex::Mutex()
{
	m_Base = CreateMutexW(nullptr, FALSE, nullptr);
}

Mutex::~Mutex()
{
	if (m_Base)
	{
		CloseHandle(m_Base);
		m_Base = nullptr;
	}
}

void Mutex::Lock()
{
	WaitForSingleObject(m_Base, INFINITE);
}

void Mutex::Unlock()
{
	ReleaseMutex(m_Base);
}
