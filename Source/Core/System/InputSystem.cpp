#include "InputSystem.h"

bool Keyboard::s_KeysDown[HA_MAX_KEYS];
bool Keyboard::s_AnyKeyDown = false;
bool Keyboard::s_KeysUp[HA_MAX_KEYS];
bool Keyboard::s_AnyKeyUp = false;
bool Keyboard::s_Keys[HA_MAX_KEYS];
bool Keyboard::s_AnyKey = false;
bool Mouse::s_ButtonsDown[HA_MAX_BUTTONS];
bool Mouse::s_AnyButtonDown = false;
bool Mouse::s_ButtonsUp[HA_MAX_BUTTONS];
bool Mouse::s_AnyButtonUp = false;
bool Mouse::s_Buttons[HA_MAX_BUTTONS];
bool Mouse::s_AnyButton = false;
float Mouse::s_MouseX = 0.0f;
float Mouse::s_MouseY = 0.0f;
float Mouse::s_MouseDelta = 0.0f;

void Keyboard::Reset()
{
	for (int i = 0; i < HA_MAX_KEYS; i++)
	{
		s_KeysDown[i] = false;
		s_KeysUp[i] = false;
	}
	s_AnyKeyDown = false;
	s_AnyKeyUp = false;
}

void Keyboard::OnKeyDown(const int key)
{
	s_Keys[key] = true;
	s_KeysDown[key] = true;
	s_AnyKey = true;
	s_AnyKeyDown = true;
}

void Keyboard::OnKeyUp(const int key)
{
	s_Keys[key] = false;
	s_KeysUp[key] = true;
	s_AnyKey = false;
	s_AnyKeyUp = true;
}

bool Keyboard::IsKey(const int key)
{
	return s_Keys[key];
}

bool Keyboard::IsKeyDown(const int key)
{
	return s_KeysDown[key];
}

bool Keyboard::IsKeyUp(const int key)
{
	return s_KeysUp[key];
}

bool Keyboard::IsAnyKey()
{
	return s_AnyKey;
}

bool Keyboard::IsAnyKeyDown()
{
	return s_AnyKeyDown;
}

bool Keyboard::IsAnyKeyUp()
{
	return s_AnyKeyUp;
}

void Mouse::Reset()
{
	s_ButtonsDown[0] = false;
	s_ButtonsDown[1] = false;
	s_ButtonsDown[2] = false;
	s_ButtonsDown[3] = false;
	s_ButtonsUp[0] = false;
	s_ButtonsUp[1] = false;
	s_ButtonsUp[2] = false;
	s_ButtonsUp[3] = false;
	s_AnyButtonDown = false;
	s_AnyButtonUp = false;
	s_MouseDelta = 0.0f;
}

void Mouse::OnMouseDown(const int button)
{
	s_Buttons[button] = true;
	s_ButtonsDown[button] = true;
	s_AnyButtonDown = true;
	s_AnyButton = true;
}

void Mouse::OnMouseUp(const int button)
{
	s_Buttons[button] = false;
	s_ButtonsUp[button] = true;
	s_AnyButtonUp = true;
	s_AnyButton = false;
}

void Mouse::OnMouseMove(const float x, const float y)
{
	s_MouseX = x;
	s_MouseY = y;
}

void Mouse::OnMouseScroll(const float delta)
{
	s_MouseDelta = delta;
}

bool Mouse::IsButton(const int button)
{
	return s_Buttons[button];
}

bool Mouse::IsButtonDown(const int button)
{
	return s_ButtonsDown[button];
}

bool Mouse::IsButtonUp(const int button)
{
	return s_ButtonsUp[button];
}

bool Mouse::IsAnyButton()
{
	return s_AnyButton;
}

bool Mouse::IsAnyButtonDown()
{
	return s_AnyButtonDown;
}

bool Mouse::IsAnyButtonUp()
{
	return s_AnyButtonUp;
}

float Mouse::GetMouseX()
{
	return s_MouseX;
}

float Mouse::GetMouseY()
{
	return s_MouseY;
}

float Mouse::GetMouseDelta()
{
	return s_MouseDelta;
}

Controller::Controller()
{
	for (int i = 0; i < HA_MAX_CONTROLLER_BUTTONS; i++)
	{
		m_Buttons[i] = false;
	}
	m_LeftTrigger = 0.0f;
	m_RightTrigger = 0.0f;
	m_LeftAxis.X = 0.0f;
	m_LeftAxis.Y = 0.0f;
	m_RightAxis.X = 0.0f;
	m_RightAxis.Y = 0.0f;
	m_Connected = false;
}

void Controller::SetButton(const int button, bool value)
{
	m_Buttons[button] = value;
}

void Controller::SetLeftTrigger(const float value)
{
	m_LeftTrigger = value;
}

void Controller::SetRightTrigger(const float value)
{
	m_RightTrigger = value;
}

void Controller::SetRightAxis(const Axis& axis)
{
	m_RightAxis = axis;
}

void Controller::SetLeftAxis(const Axis& axis)
{
	m_LeftAxis = axis;
}

void Controller::SetConnected(bool value)
{
	m_Connected = value;
}

bool Controller::IsButton(const int button) const
{
	return m_Buttons[button];
}

float Controller::GetLeftTrigger() const
{
	return m_LeftTrigger;
}

float Controller::GetRightTrigger() const
{
	return m_RightTrigger;
}

Controller::Axis Controller::GetLeftAxis() const
{
	return m_LeftAxis;
}

Controller::Axis Controller::GetRightAxis() const
{
	return m_RightAxis;
}

bool Controller::IsConnected() const
{
	return m_Connected;
}
