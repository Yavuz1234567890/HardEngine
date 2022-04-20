#include "Platform.h"

Vector<BaseWindow*> Platform::s_Windows;
Mutex Platform::s_WindowsMutex;

BaseWindow* Platform::GetWindow(void* handle)
{
	BaseWindow* result = nullptr;
	s_WindowsMutex.Lock();
	for (int i = 0; i < s_Windows.Size(); i++)
	{
		if (s_Windows[i]->GetNativeHandle() == handle)
		{
			result = s_Windows[i];
			break;
		}
	}
	s_WindowsMutex.Unlock();
	return result;
}

void Platform::PushWindow(BaseWindow* window)
{
	s_WindowsMutex.Lock();
	s_Windows.PushBack(window);
	s_WindowsMutex.Unlock();
}

void Platform::RemoveWindow(BaseWindow* window)
{
	s_WindowsMutex.Lock();
	for (int i = 0; i < s_Windows.Size(); i++)
	{
		if (s_Windows[i] == window)
		{
			s_Windows.Erase(i);
			break;
		}
	}
	s_WindowsMutex.Unlock();
}

Vector<BaseWindow*> Platform::GetWindows()
{
	return s_Windows;
}
