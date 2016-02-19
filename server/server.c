#include "server.h"

//port user?
//define backlog nb maxi de connexions acceptees

void server() {
  int sock_fd; //socket ecoutee
  int new_fd, reuse = 1, n;  //nouvelle connexion
  char buffer[256];

  struct addrinfo hints, *resinfo= NULL;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */

  if (getaddrinfo(NULL, "4242", &hints, &resinfo) != 0)
    err(1, "err getaddrinfo");
  if((sock_fd = socket(resinfo->ai_family, resinfo->ai_socktype, resinfo->ai_protocol)) > 0)
    printf("the socket is created\n");
  freeaddrinfo(resinfo);
  if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    err(1, "setsockopt problem");
  if(bind(sock_fd, resinfo->ai_addr, resinfo->ai_addrlen) == 0)
    printf("binding socket\n");
  if(listen(sock_fd, 10))
    printf("listening");
  while(1) {
    new_fd= accept(sock_fd, (struct sockaddr *) NULL, NULL);

    if (fork())
      {
	close(new_fd);
	continue;
      }
    else
      {
	close(sock_fd);
	while ((n = read(new_fd,buffer, 256)) > 0)
	  {
	    if (write(new_fd, buffer, n) == -1)
	      err(1, "erreur write");
	  }
	close(new_fd);
	return;
      }
  }
  close(sock_fd);
    /*   if(new_fd > 0) */
  /*     printf("accept"); */

  /*   recv(new_fd, buffer, 256, 0); */
  /*   printf("%s\n", buffer); */
  /*   write(new_fd, "hello\n", 6); */
  /*   close(new_fd); */
  /* } */
  // close(sock_fd);
}

int main() {
  server();
  return 0;
}
