#include "database.h"

char *itoa(int nb) {
  char *res= malloc(sizeof(char)*4); 
  sprintf(res, "%d", nb);
  return res;
}

static int callback(void *data, int argc, char **argv, char **azColName){
  int i;
  (void)data;
    for(i=0; i < argc; i++) {
      // (char*)data[i]= argv[i];
      printf("%s= %s\n", azColName[i], argv[i] ? argv[i]: "NULL");
    }
  return 0;
}

void create_clients(sqlite3 *db, char mac_addr[25], char *name) {
  char *sql= "INSERT INTO clients(id, mac_addr, name) "\
	"VALUES(NULL, '";
  char *res;
  if ((res = calloc(1024, sizeof(char))) == NULL)
    return;
  strcat(res, sql);
  strcat(res, mac_addr);
  strcat(res, "', '");
  strcat(res, name);
  strcat(res, "');");
  printf("%s\n", res);

  if(sqlite3_exec(db, res, NULL, 0, 0) != SQLITE_OK)
    perror("SQL error\n");
  else
    printf("create success\n");
  free(res);
}

int research_clients(sqlite3 *db, int id_client) { 
  char *sql= "SELECT * FROM clients "\
	      "WHERE id= "; 
   char *res= malloc(sizeof(char) * 256); 
   strcat(res, sql); 
   strcat(res, itoa(id_client)); 
   strcat(res, ";"); 
   printf("%s\n", res); 
   if(sqlite3_exec(db, res, callback, 0, 0) != SQLITE_OK) {
     perror("sql error\n"); 
     return 0;
   }
   else {
     printf("research client success\n");
     return 1;
   }
 }

void get_all_clients(sqlite3 *db) {
  char *sql= "SELECT mac_addr FROM clients;";

  if(sqlite3_exec(db, sql, callback, 0, 0) != SQLITE_OK)
    perror("SQL error\n");
  else
    printf("get all success\n");
}

void update_data(sqlite3 *db, char *data, int id_client) {
  char *sql= "UPDATE data SET data= '";
  char *res;
  if ((res = calloc(1024, sizeof(char))) == NULL)
    return;
  strcat(res, sql);
  strcat(res, data);
  strcat(res, "' WHERE id_client= ");
  strcat(res, itoa(id_client));
  strcat(res, ";");
  printf("%s\n", res);

  if(sqlite3_exec(db, res, NULL, 0, 0) != SQLITE_OK)
    perror("SQL error\n");
  else
    printf("update success\n");
  free(res);
}

void create_data(sqlite3 *db, int id_server, int id_client, char *data) {
  char *sql= "INSERT INTO data(id_server, id_client, data) "\
	      "VALUES(";
  char *res;
  if ((res = calloc(1024, sizeof(char))) == NULL)
    return;
  strcat(res, sql);
  strcat(res, itoa(id_server));
  strcat(res, ", ");
  strcat(res, itoa(id_client));
  strcat(res, ", '");
  strcat(res, data);
  strcat(res, "');");
  printf("%s\n", res);

  if(sqlite3_exec(db, res, NULL, 0, 0) != SQLITE_OK)
    perror("sqlite error\n");
  else
    printf("add data success\n");
  free(res);
}

void research_data(sqlite3 *db, int id_client) {
  char *sql= "SELECT data FROM data"\
	      " WHERE id_client= ";
  char *sql2= " in"\
	      "(SELECT id FROM clients"\
	      " WHERE id= id_client);";
  char *res= calloc(256, sizeof(char));
  strcat(res, sql);
  strcat(res, itoa(id_client));
  strcat(res, sql2);
  printf("%s\n", res);

  if(sqlite3_exec(db, res, callback, 0, 0) != SQLITE_OK)
    perror("sqlite error\n");
  else
    printf("research data success\n");
  free(res);
}

/*void concat_data(sqlite3 *db, char *data) {
}*/

void delete_clients(sqlite3 *db, int id_client) { 
   char *sql= "DELETE FROM clients "\
	       "WHERE id="; 
   char *res= malloc(sizeof(char) * 256); 
   strcat(res, sql); 
   strcat(res, itoa(id_client)); 
   strcat(res, ";"); 
   printf("%s\n", res); 

   if(sqlite3_exec(db, res, NULL, 0, 0) != SQLITE_OK) 
     perror("SQL error\n"); 
   else 
   printf("delete success\n"); 
 } 
