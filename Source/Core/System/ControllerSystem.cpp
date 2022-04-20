#include "ControllerSystem.h"

#include <math.h>

Controller ControllerSystem::s_Controllers[HA_MAX_GAMEPADS];

void ControllerSystem::Init()
{
#if defined(HA_PLATFORM_WINDOWS)
	InitWindows();
#elif defined(HA_PLATFORM_LINUX)
	InitLinux();
#endif
}

void ControllerSystem::PowerMotor(UInt64 index, UInt16 left, UInt16 right)
{
#if defined(HA_PLATFORM_WINDOWS)
	PowerMotorWindows(index, left, right);
#elif defined(HA_PLATFORM_LINUX)
	PowerMotorLinux(index, left, right);
#endif
}

void ControllerSystem::Update()
{
#if defined(HA_PLATFORM_WINDOWS)
	UpdateWindows();
#elif defined(HA_PLATFORM_LINUX)
	UpdateLinux();
#endif
}

Controller ControllerSystem::GetController(UInt64 index)
{
	return s_Controllers[index];
}

#if defined(HA_PLATFORM_WINDOWS)

#include <windows.h>
#include <xinput.h>

typedef decltype(XInputGetState)* GetStateFn;
typedef decltype(XInputSetState)* SetStateFn;

GetStateFn XInput_GetState;
SetStateFn XInput_SetState;
XINPUT_STATE State;
HMODULE XInputLibHandle = NULL;
XINPUT_VIBRATION MotorPower;

void ControllerSystem::InitWindows()
{
	XInputLibHandle = LoadLibraryW(L"Xinput9_1_0.dll");
	if (XInputLibHandle)
	{
		XInput_GetState = (GetStateFn)GetProcAddress(XInputLibHandle, "XInputGetState");
		XInput_SetState = (SetStateFn)GetProcAddress(XInputLibHandle, "XInputSetState");
		if (!XInput_GetState || !XInput_SetState)
		{
			FreeLibrary(XInputLibHandle);
			return;
		}
	}

	DWORD dwResult = 0;
	for (int i = 0; i < HA_MAX_GAMEPADS; i++)
	{
		ZeroMemory(&State, sizeof(XINPUT_STATE));
		dwResult = XInput_GetState(i, &State);
		s_Controllers[i].SetConnected(dwResult == ERROR_SUCCESS);
	}
}

void ControllerSystem::PowerMotorWindows(UInt64 index, UInt16 left, UInt16 right)
{
	if (s_Controllers[index].IsConnected())
	{
		ZeroMemory(&MotorPower, sizeof(XINPUT_VIBRATION));
		MotorPower.wLeftMotorSpeed = left;
		MotorPower.wRightMotorSpeed = right;
		XInput_SetState((DWORD)index, &MotorPower);
	}
}

static Controller::Axis NormalizeAxis(const float x, const float y)
{
	float base = sqrtf(x * x + y * y);
	float normX = x / base;
	float normY = y / base;
	float normBase = 0.0f;
	if (base > 7849) 
	{
		if (base > 32767)
		{
			base = 32767;
		}
		base -= 7849;
		normBase = base / (32767 - 7849);
	}
	else 
	{
		base = 0.0f;
		normBase = 0.0f;
	}
	return { normX * normBase, normY * normBase };
}

void ControllerSystem::UpdateWindows()
{
	DWORD dwResult = 0;
	for (int i = 0; i < HA_MAX_GAMEPADS; i++)
	{
		ZeroMemory(&State, sizeof(XINPUT_STATE));
		dwResult = XInput_GetState(i, &State);
		s_Controllers[i].SetConnected(dwResult == ERROR_SUCCESS);
		if (s_Controllers[i].IsConnected())
		{
			s_Controllers[i].SetLeftTrigger(State.Gamepad.bLeftTrigger / 255.0f);
			s_Controllers[i].SetRightTrigger(State.Gamepad.bRightTrigger / 255.0f);
			s_Controllers[i].SetLeftAxis(NormalizeAxis(State.Gamepad.sThumbLX, State.Gamepad.sThumbLY));
			s_Controllers[i].SetRightAxis(NormalizeAxis(State.Gamepad.sThumbRX, State.Gamepad.sThumbRY));

			s_Controllers[i].SetButton(HA_GAMEPAD_A, State.Gamepad.wButtons & XINPUT_GAMEPAD_A);
			s_Controllers[i].SetButton(HA_GAMEPAD_B, State.Gamepad.wButtons & XINPUT_GAMEPAD_B);
			s_Controllers[i].SetButton(HA_GAMEPAD_X, State.Gamepad.wButtons & XINPUT_GAMEPAD_X);
			s_Controllers[i].SetButton(HA_GAMEPAD_Y, State.Gamepad.wButtons & XINPUT_GAMEPAD_Y);
			s_Controllers[i].SetButton(HA_GAMEPAD_START, State.Gamepad.wButtons & XINPUT_GAMEPAD_START);
			s_Controllers[i].SetButton(HA_GAMEPAD_BACK, State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
			s_Controllers[i].SetButton(HA_GAMEPAD_LEFT_SHOULDER, State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
			s_Controllers[i].SetButton(HA_GAMEPAD_RIGHT_SHOULDER, State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
			s_Controllers[i].SetButton(HA_GAMEPAD_LEFT_THUMB, State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
			s_Controllers[i].SetButton(HA_GAMEPAD_RIGHT_SHOULDER, State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
			s_Controllers[i].SetButton(HA_GAMEPAD_UP, State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
			s_Controllers[i].SetButton(HA_GAMEPAD_DOWN, State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
			s_Controllers[i].SetButton(HA_GAMEPAD_LEFT, State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
			s_Controllers[i].SetButton(HA_GAMEPAD_RIGHT, State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
		}
	}
}

#elif defined(HA_PLATFORM_LINUX)

void ControllerSystem::InitLinux()
{

}

void ControllerSystem::PowerMotorLinux(UInt64 index, UInt16 left, UInt16 right)
{

}

void ControllerSystem::UpdateLinux()
{

}

#endif
