#include <errno.h>
#include "server.h"

void server() {
  int sock_fd; //socket ecoutee
  int io= 1;
  int new_fd, reuse = 1, n;  //nouvelle connexion
  char buffer[256];
  struct addrinfo hints, *resinfo= NULL;

  //create poll struct
  struct pollfd fds[200];

  memset(&hints, 0, sizeof(struct addrinfo));

  //init poll struct
  memset(fds, 0, sizeof(fds));

  //set up initial socket
  fds[0].events= POLLIN;

  hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */

  if (getaddrinfo(NULL, "4242", &hints, &resinfo) != 0)
    err(1, "err getaddrinfo");

  if((sock_fd= socket(resinfo->ai_family, resinfo->ai_socktype, resinfo->ai_protocol)) < 0)
    err(1, "err socket");

  if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    err(1, "setsockopt problem");

  if(bind(sock_fd, resinfo->ai_addr, resinfo->ai_addrlen) != 0)
    err(1, "err bind");

  freeaddrinfo(resinfo);

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
    poll(fds, reuse, 1000000);
    for(int i = 0; i < reuse; i++) {
      if (fds[i].revents == 0)
        continue;
      if (fds[i].revents != POLLIN && fds[i].revents != POLLPRI)
        {
          printf("%d\n", i);
          perror("pollin error");
        }

      if (fds[i].fd == fds[0].fd) {
      	do {
          new_fd = accept(fds[0].fd, (struct sockaddr*)NULL, NULL);
          if (new_fd == -1)
             break;
          fds[reuse].fd = new_fd;
          fds[reuse].events = POLLIN;
          reuse++;
        } while (new_fd != -1);
      }
      else {
	while(1) {
	  if((n = read(fds[i].fd, buffer, 256)) < 0)
	    close(fds[i].fd);
	  printf("%s\n", buffer);
	  memset(buffer, 0, 256);
	}
      }
    }
  }
}

int main() {
  server();
  return 0;
}
