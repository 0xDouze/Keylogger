#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "../server/server.h"

void create_clients(sqlite3 *db, int id_client, char mac_addr[25], char *data);

void research_clients(sqlite3 *db, int id_client);

void get_all_clients(sqlite3 *db);

void update_clients(sqlite3 *db, char *data, int id_client);

void delete_clients(sqlite3 *db, char *mac_addr);

void add_data(sqlite3 *db, char *data, char *mac_addr);
