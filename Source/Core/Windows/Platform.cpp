#include "Core/Core/Platform.h"
#include "Platform.h"
#include "Window.h"

static WNDCLASSEXW s_WindowClass;

static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	WindowsWindow* wnd = static_cast<WindowsWindow*>(Platform::GetWindow(hWnd));
	if (wnd)
	{
		return wnd->OnWindowMessage(Msg, wParam, lParam);
	}
	return DefWindowProcW(hWnd, Msg, wParam, lParam);
}

void Platform::Init()
{
	ZeroMemory(&s_WindowClass, sizeof(s_WindowClass));
	s_WindowClass.cbClsExtra = NULL;
	s_WindowClass.cbSize = sizeof(WNDCLASSEXW);
	s_WindowClass.cbWndExtra = NULL;
	s_WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	s_WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	s_WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	s_WindowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	s_WindowClass.hInstance = GetModuleHandleW(nullptr);
	s_WindowClass.lpszClassName = L"HaWindowClass";
	s_WindowClass.lpszMenuName = L"";
	s_WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	s_WindowClass.lpfnWndProc = WndProc;
	
	if (!RegisterClassExW(&s_WindowClass))
	{
		return;
	}
}

void Platform::PollEvents()
{
	MSG Msg;
	while (PeekMessageW(&Msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessageW(&Msg);
	}
}

WNDCLASSEXW GetWindowClass()
{
	return s_WindowClass;
}
