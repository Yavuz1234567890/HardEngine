#ifndef WINDOWS_WINDOW_H_
#define WINDOWS_WINDOW_H_

#include "Core/Core/PlatformDetection.h"
#include "Core/File/FileSystem.h"
#include "Platform.h"

#include <windows.h>

class WindowsWindow : public BaseWindow
{
public:
	WindowsWindow()
		: BaseWindow(),
		m_hWnd(NULL)
	{

	}

	~WindowsWindow()
	{
		if (m_hWnd)
		{
			DestroyWindow(m_hWnd);
			m_hWnd = NULL;
		}
	}

	LRESULT CALLBACK OnWindowMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		switch (Msg)
		{
		case WM_DESTROY:
			OnWindowClose();
			::PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			OnKeyDown((const int)wParam);
			break;
		case WM_KEYUP:
			OnKeyUp((const int)wParam);
			break;
		case WM_LBUTTONDOWN:
			OnMouseDown(0);
			break;
		case WM_RBUTTONDOWN:
			OnMouseDown(1);
			break;
		case WM_MBUTTONDOWN:
			OnMouseDown(2);
			break;
		case WM_XBUTTONDOWN:
			if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
			{
				OnMouseDown(3);
			}
			if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2)
			{
				OnMouseDown(4);
			}
			break;
		case WM_LBUTTONUP:
			OnMouseUp(0);
			break;
		case WM_RBUTTONUP:
			OnMouseUp(1);
			break;
		case WM_MBUTTONUP:
			OnMouseUp(2);
			break;
		case WM_XBUTTONUP:
			if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
			{
				OnMouseUp(3);
			}
			if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2)
			{
				OnMouseUp(4);
			}
			break;
		case WM_MOUSEMOVE:
		{
			const float posX = (float)((short)LOWORD(lParam));
			const float posY = (float)((short)HIWORD(lParam));
			OnMouseMove(posX, posY);
		}
		break;
		case WM_MOUSEWHEEL:
		{
			const float delta = (float)((short)HIWORD(wParam));
			OnMouseScroll(delta / 120.0f);
		}
		break;
		case WM_SIZE:
			OnWindowSize((const int)LOWORD(lParam), (const int)HIWORD(lParam));
			break;
		case WM_MOVE:
			OnWindowMove((const int)(short)LOWORD(lParam), (const int)(short)HIWORD(lParam));
			break;
		}
		return DefWindowProcW(m_hWnd, Msg, wParam, lParam);
	}

	bool Init(const String& title, int width, int height, int x, int y, const int mode, const String& iconPath) override
	{
		m_StartWidth = width;
		m_StartHeight = height;
		m_Title = title;
		DWORD dwStyle = 0, dwExStyle = 0;
		if (mode & BaseWindow::TOOLWINDOW)
		{
			dwExStyle |= WS_EX_TOOLWINDOW;
		}
		else
		{
			dwExStyle |= WS_EX_APPWINDOW;
		}
		if (mode & BaseWindow::RESIZABLE)
		{
			dwStyle |= WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX | WS_THICKFRAME;
		}
		if (mode & BaseWindow::POPUP)
		{
			dwStyle |= WS_POPUP;
		}
		RECT rect = { 0, 0, (LONG)width, (LONG)height };
		AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle);
		WCHAR wtitle[280];
		WString::ToCString(wtitle, title.CData());
		m_hWnd = CreateWindowExW(dwExStyle, GetWindowClass().lpszClassName, wtitle, dwStyle, x, y, width, height, nullptr, nullptr, GetWindowClass().hInstance, nullptr);
		if (iconPath != "None")
		{
			HANDLE hIconSmall = LoadImage(NULL, FileSystem::GetCurrentDir().PushBack(iconPath).PushBack("_small.ico").CData(), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
			HANDLE hIconBig = LoadImage(NULL, FileSystem::GetCurrentDir().PushBack(iconPath).PushBack("_big.ico").CData(), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
			if (hIconSmall)
			{
				SendMessage(m_hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSmall);
				SendMessage(m_hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIconBig);
				SendMessage(GetWindow(m_hWnd, GW_OWNER), WM_SETICON, ICON_SMALL, (LPARAM)hIconSmall);
				SendMessage(GetWindow(m_hWnd, GW_OWNER), WM_SETICON, ICON_BIG, (LPARAM)hIconBig);
			}
		}
		ShowWindow(m_hWnd, SW_SHOW);
		UpdateWindow(m_hWnd);
		return m_hWnd != NULL;
	}

	void SetFullscreen(bool fullscreen) override
	{
		if (m_IsFullscreen != fullscreen)
		{
			if (fullscreen)
			{
				LONG style = GetWindowLong(m_hWnd, GWL_STYLE);
				LONG exStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
				SetWindowLong(m_hWnd, GWL_STYLE, style & ~(WS_CAPTION | WS_THICKFRAME));
				SetWindowLong(m_hWnd, GWL_EXSTYLE, exStyle & ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));
				SendMessage(m_hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
				SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			}
			else
			{
				LONG style = GetWindowLong(m_hWnd, GWL_STYLE);
				LONG exStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
				SetWindowLong(m_hWnd, GWL_STYLE, style | (WS_CAPTION | WS_THICKFRAME));
				SetWindowLong(m_hWnd, GWL_EXSTYLE, exStyle | (WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));
				SendMessage(m_hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
				if (IsZoomed(m_hWnd)) 
				{
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
				}
			}
			m_IsFullscreen = fullscreen;
		}
	}

	void SetTitle(const String& title) override
	{
		WCHAR wtitle[280];
		WString::ToCString(wtitle, title.CData());
		SetWindowTextW(m_hWnd, wtitle);
	}

	void MakeMaximized() override
	{
		ShowWindow(m_hWnd, SW_SHOWMAXIMIZED);
	}

	void MakeMinimized() override
	{
		ShowWindow(m_hWnd, SW_SHOWMINIMIZED);
	}

	void MakeHiden() override
	{
		ShowWindow(m_hWnd, SW_HIDE);
	}

	void MakeNormal() override
	{
		ShowWindow(m_hWnd, SW_SHOWNORMAL);
	}

	void* GetNativeHandle() const override
	{
		return (void*)m_hWnd;
	}
private:
	HWND m_hWnd;
	bool m_Running;
};

#endif
