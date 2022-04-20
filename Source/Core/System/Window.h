#ifndef WINDOW_H_
#define WINDOW_H_

#include "Core/Containers/String.h"
#include "Core/Containers/Function.h"
#include "Core/Core/Events.h"

class BaseWindow
{
public:
	enum
	{
		TOOLWINDOW = 1 << 0,
		RESIZABLE = 1 << 1,
		POPUP = 1 << 2
	};

	BaseWindow();
	~BaseWindow() { }

	virtual bool Init(const String& title, int width, int height, int x, int y, const int mode, const String& iconPath) = 0;
	virtual void SetFullscreen(bool fullscreen) = 0;
	virtual void SetTitle(const String& title) = 0;
	virtual void MakeMaximized() = 0;
	virtual void MakeMinimized() = 0;
	virtual void MakeHiden() = 0;
	virtual void MakeNormal() = 0;
	virtual void* GetNativeHandle() const = 0;
	void SetRunning(bool running) { m_IsRunning = running; }
	bool IsRunning() const { return m_IsRunning; }
	bool IsFullscreen() const { return m_IsFullscreen; }
	int GetStartWidth() const { return m_StartWidth; }
	int GetStartHeight() const { return m_StartHeight; }
	void SendEvent(Event& e) { m_EventFunction(e); }
	void SetEventFunction(const Function<void(Event&)>& rhs) { m_EventFunction = rhs; }
	static BaseWindow* Create();
protected:
	void OnWindowClose();
	void OnKeyDown(const int key);
	void OnKeyUp(const int key);
	void OnMouseDown(const int button);
	void OnMouseUp(const int button);
	void OnMouseMove(const float x, const float y);
	void OnMouseScroll(const float delta);
	void OnWindowMove(const int x, const int y);
	void OnWindowSize(const int width, const int height);

	Function<void(Event&)> m_EventFunction;
	bool m_IsRunning, m_IsFullscreen;
	int m_StartWidth, m_StartHeight;
	String m_Title;
};

#endif
