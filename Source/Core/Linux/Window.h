#ifndef LINUX_WINDOW_H_
#define LINUX_WINDOW_H_

#include "Core/System/Window.h"

class LinuxWindow : public BaseWindow
{
public:
	LinuxWindow()
	{

	}

	~LinuxWindow()
	{
	
	}

	bool Init(const String& title, int width, int height, int x, int y, const int mode, const String& iconPath) override
	{

	}

	void SetFullscreen(bool fullscreen) override
	{

	}

	void SetTitle(const String& title) override
	{

	}

	void MakeMaximized() override
	{

	}

	void MakeMinimized() override
	{

	}

	void MakeHiden() override
	{

	}

	void MakeNormal() override
	{

	}
	
	void* GetNativeHandle() const override
	{

	}
};

#endif
