#include "Debug.h"
#include "Core/Utils/Log.h"

#include <stdio.h>

void Debug::Print(const char* out)
{
	printf("%s", out);
}

void Debug::LogFn(const int level, const char* out)
{
	if (level == Log::INFO)
	{
		SetColor(GREEN);
		Print("[Info] ");
	}
	if (level == Log::ERR)
	{
		SetColor(RED);
		Print("[Error] ");
	}
	if (level == Log::WARNING)
	{
		SetColor(YELLOW);
		Print("[Warning] ");
	}
	Print(out);
	Print("\n");
	SetColor(DEFAULT);
}
