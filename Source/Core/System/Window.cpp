#include "Window.h"
#include "Core/Core/PlatformDetection.h"
#include "Core/Core/Platform.h"

#if defined(HA_PLATFORM_WINDOWS)
#include "Core/Windows/Window.h"
#elif defined(HA_PLATFORM_LINUX)
#include "Core/Linux/Window.h"
#endif

BaseWindow::BaseWindow()
	: m_IsFullscreen(false), 
	m_IsRunning(true), 
	m_StartWidth(0), 
	m_StartHeight(0)
{
	Platform::PushWindow(this);
}

BaseWindow* BaseWindow::Create()
{
#if defined(HA_PLATFORM_WINDOWS)
	return Allocator::New<WindowsWindow>();
#elif defined(HA_PLATFORM_LINUX)
	return Allocator::New<LinuxWindow>();
#endif
}

void BaseWindow::OnWindowClose()
{
	WindowCloseEvent e;
	SendEvent(e);
	m_IsRunning = false;
}

void BaseWindow::OnKeyDown(const int key)
{
	KeyDownEvent e(key);
	SendEvent(e);
}

void BaseWindow::OnKeyUp(const int key)
{
	KeyUpEvent e(key);
	SendEvent(e);
}

void BaseWindow::OnMouseDown(const int button)
{
	MouseDownEvent e(button);
	SendEvent(e);
}

void BaseWindow::OnMouseUp(const int button)
{
	MouseUpEvent e(button);
	SendEvent(e);
}

void BaseWindow::OnMouseMove(const float x, const float y)
{
	MouseMoveEvent e(x, y);
	SendEvent(e);
}

void BaseWindow::OnMouseScroll(const float delta)
{
	MouseScrollEvent e(delta);
	SendEvent(e);
}

void BaseWindow::OnWindowMove(const int x, const int y)
{
	WindowMoveEvent e(x, y);
	SendEvent(e);
}

void BaseWindow::OnWindowSize(const int width, const int height)
{
	WindowSizeEvent e(width, height);
	SendEvent(e);
}
