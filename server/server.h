#pragma once

#include <err.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <poll.h>
#include <stropts.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void	save_data (char *buffer);
void	server();
int	init_socket(nfds_t*);

#define BUFFSIZE 1024
#define PORT "4141"
