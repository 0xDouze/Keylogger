#include "database.h"
#include <errno.h> //a enlever quand include server.h
#include <string.h>

void create_clients(sqlite3 *db, int id_client, char mac_addr[25], char *data) {
  char *sql= "INSERT INTO clients(id, mac_addr, data)"\
	      "VALUES(";
  strcat(sql, id_client);
  strcat(sql, ", ");
  strcat(sql, mac_addr);
  strcat(sql, ", ");
  strcat(sql, data);
  strcat(sql, ");");

  int exec= sqlite3_exec(db, sql, NULL, 0, 0);

  if(exec != SQLITE_OK)
    perror("SQL error");
  else
    printf("success");
}


int main() {
  sqlite3 *keylogger;
  int res= sqlite3_open("keylogger.db", &keylogger);

  if(res) {
    perror("can't succeed");
    exit(0);
  }
  else
    printf("success");
  create_clients(keylogger, 2, "78.4H.9T.DF.T3.Q5", "blblbl");
  sqlite3_close(keylogger);
  return 0;
}
