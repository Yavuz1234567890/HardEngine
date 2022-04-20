#ifndef CONTROLLER_SYSTEM_H_
#define CONTROLLER_SYSTEM_H_

#include "InputSystem.h"
#include "Core/Core/BasicTypes.h"
#include "Core/Utils/GamepadDefines.h"
#include "Core/Core/PlatformDetection.h"

#define HA_MAX_GAMEPADS 4

class ControllerSystem
{
public:
	static void Init();
	static void Update();
	static Controller GetController(UInt64 index);
	static void PowerMotor(UInt64 index, UInt16 left, UInt16 right);
private:
#if defined(HA_PLATFORM_WINDOWS)
	static void InitWindows();
	static void UpdateWindows();
	static void PowerMotorWindows(UInt64 index, UInt16 left, UInt16 right);
#elif defined(HA_PLATFORM_LINUX)
	static void InitLinux();
	static void UpdateLinux();
	static void PowerMotorLinux(UInt64 index, UInt16 left, UInt16 right);
#endif

	static Controller s_Controllers[HA_MAX_GAMEPADS];
};

#endif
