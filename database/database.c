#include "database.h"
#include <errno.h> //a enlever quand include server.h
#include <string.h>

static inline char *itoa(int nb) {
  char *res= (char *)malloc(sizeof(char)*3); 
  sprintf(res, "%d", nb);
  return res;
}

void create_clients(sqlite3 *db, int id_client, char mac_addr[25], char *data) {
  char *sql= "INSERT INTO clients(id, mac_addr, data) "\
	"VALUES(";
  char *res= malloc(sizeof(char)*256);
  strcat(res, sql);
  strcat(res, itoa(id_client));
  strcat(res, ", '");
  strcat(res, mac_addr);
  strcat(res, "', '");
  strcat(res, data);
  strcat(res, "');");
  printf("%s\n", res);

  if(sqlite3_exec(db, res, NULL, 0, 0) != SQLITE_OK)
    perror("SQL error");
  else
    printf("create success");
}

void research_clients(sqlite3 *db, int id_client) {
  char *sql= "SELECT * FROM clients "\
	      "WHERE id= ";
  char *res= malloc(sizeof(char)*256);
  strcat(res, sql);
  strcat(res, itoa(id_client));
  strcat(res, ";");
  printf("%s\n", res);

  if(sqlite3_exec(db, res, NULL, 0, 0 != SQLITE_OK))
    perror("SQL error\n");
  else
    printf("research success\n");
}

void update_clients(sqlite3 *db, char *data, int id_client) {
  char *sql= "UPDATE clients SET data= '";
  char *res= malloc(sizeof(char)*256);
  strcat(res, sql);
  strcat(res, data);
  strcat(res, "' WHERE id= ");
  strcat(res, itoa(id_client));
  strcat(res, ";");
  printf("%s\n", res);

  if(sqlite3_exec(db, res, NULL, 0, 0 != SQLITE_OK))
    perror("SQL error\n");
  else
    printf("update success\n");
}

void delete_clients(sqlite3 *db, char *mac_addr) {
  char *sql= "DELETE FROM clients "\
	      "WHERE mac_addr='";
  char *res= malloc(sizeof(char)*256);
  strcat(res, sql);
  strcat(res, mac_addr);
  strcat(res, "';");
  printf("%s\n", res);

  if(sqlite3_exec(db, res, NULL, 0, 0 != SQLITE_OK))
    perror("SQL error\n");
  else
    printf("delete success\n");
}



int main() {
  sqlite3 *keylogger;
  int res= sqlite3_open("keylogger.db", &keylogger);

  if(res) {
    perror("can't succeed\n");
    exit(0);
  }
  else
    printf("connection success\n");
  //create_clients(keylogger, 2, "78.4H.9T.DF.T3.Q5", "blblbl");
  //research_clients(keylogger, 2);
  //update_clients(keylogger, "kevin le plus bo", 2);
  //delete_clients(keylogger, "78.4H.9T.DF.T3.Q5");
  sqlite3_close(keylogger);
  return 0;
}
