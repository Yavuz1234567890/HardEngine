#include "Core/Core/Debug.h"

#include <stdio.h>
#include <signal.h>

void Debug::Init()
{

}

void Debug::SetColor(const int color)
{
	if (color == RED)
	{
		printf("\033[0;31m");
	}
	if (color == GREEN)
	{
		printf("\033[0;32m");
	}
	if (color == YELLOW)
	{
		printf("\033[0;33m");
	}
	if (color == DEFAULT)
	{
		printf("\033[0;37m");
	}
}

void Debug::Break()
{
	raise(SIGTRAP);
}
