#include "Console.hpp"

#ifdef WINDOWS_PLOT
#include <windows.h>
#else
#include <iostream>
#endif

void Console::Log(const std::string& info)
{
#ifdef WINDOWS_PLOT
	OutputDebugStringA(info.c_str());
#else
	std::cout << info;
#endif
}
