#include "Core/Core/Debug.h"
#include "Core/Core/PlatformDetection.h"

#include <windows.h>

void* Debug::s_ConsoleHandle = nullptr;

void Debug::Init()
{
	s_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Debug::SetColor(const int color)
{
	if (color == RED)
	{
		SetConsoleTextAttribute(s_ConsoleHandle, FOREGROUND_RED);
	}
	if (color == GREEN)
	{
		SetConsoleTextAttribute(s_ConsoleHandle, FOREGROUND_GREEN);
	}
	if (color == YELLOW)
	{
		SetConsoleTextAttribute(s_ConsoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
	}
	if (color == DEFAULT)
	{
		SetConsoleTextAttribute(s_ConsoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
}

void Debug::Break()
{
	DebugBreak();
}
