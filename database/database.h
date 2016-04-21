#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "../server/server.h"

char *itoa(int n);

void create_clients(sqlite3 *db, char mac_addr[25], char *data);

int research_clients(sqlite3 *db, int id_client);

void get_all_clients(sqlite3 *db);

void update_data(sqlite3 *db, char *data, int id_client);

void delete_clients(sqlite3 *db, int id_client);

void research_data(sqlite3 *db, int id_client);

void create_data(sqlite3 *db, int id_server, int id_client, char *data);
