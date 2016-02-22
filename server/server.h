#pragma once

#define _XOPEN_SOURCE
#define _GNU_SOURCE 1

#include <err.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

void save_data (char *buffer);
void server();
