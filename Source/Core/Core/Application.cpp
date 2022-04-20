#include "Application.h"
#include "Platform.h"
#include "Core/System/InputSystem.h"
#include "Core/System/ControllerSystem.h"
#include "Debug.h"

#include <string.h>

Application::Application(const String& title, const int width, const int height, const int x, const int y, const int mode, const String& iconPath)
	: m_Title(title),
	m_Width(width),
	m_Height(height),
	m_PositionX(x),
	m_PositionY(y),
	m_WindowMode(mode),
	m_IconPath(iconPath),
	m_Window(nullptr),
	m_DeltaTime(0.0f)
{

}

Application::~Application()
{

}

void Application::Run()
{
	Platform::Init();
	Log::Init();
	Debug::Init();
	ControllerSystem::Init();
	Mouse::Reset();
	Keyboard::Reset();
	m_Window = BaseWindow::Create();
	Function<void(Event&)> eventFn;
	eventFn.template Bind<Application, &Application::OnEvent>(this);
	m_Window->SetEventFunction(eventFn);
	m_Window->Init(m_Title, m_Width, m_Height, m_PositionX, m_PositionY, m_WindowMode, m_IconPath);
	Init();
	while (m_Window->IsRunning())
	{
		m_DeltaTime = m_Timer.Tick();
		Update(m_DeltaTime);
		Mouse::Reset();
		Keyboard::Reset();
		ControllerSystem::Update();
		Platform::PollEvents();
	}
}
