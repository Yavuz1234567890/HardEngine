#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Core/System/Window.h"
#include "Core/Time/Timer.h"
#include "Core/File/File.h"
#include "Core/Utils/Log.h"

class Application
{
public:
	Application(const String& title, const int width, const int height, const int x, const int y, const int mode, const String& iconPath);
	~Application();

	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void OnEvent(Event& e) = 0;

	void Run();
private:
	BaseWindow* m_Window;
	String m_Title;
	int m_Width, m_Height;
	int m_PositionX, m_PositionY;
	int m_WindowMode;
	String m_IconPath;
	Timer m_Timer;
	float m_DeltaTime;
};

#endif
