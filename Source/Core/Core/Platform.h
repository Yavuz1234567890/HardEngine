#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "Core/Containers/Vector.h"
#include "Core/System/Window.h"
#include "Core/Thread/Mutex.h"

class Platform
{
public:
	static void Init();
	static void PollEvents();
	static BaseWindow* GetWindow(void* handle);
	static void PushWindow(BaseWindow* window);
	static void RemoveWindow(BaseWindow* window);
	static Vector<BaseWindow*> GetWindows();
public:
	static Vector<BaseWindow*> s_Windows;
	static Mutex s_WindowsMutex;
};

#endif
