#include "server.h"

//port user?
//define backlog nb maxi de connexions acceptees

void server() {
  int sock_fd; //socket ecoutee
  int new_fd;  //nouvelle connexion
  char buffer[256];
  struct addrinfo hints, *resinfo= NULL;
 
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
  hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  getaddrinfo(NULL, "4343", &hints, &resinfo);

  if((sock_fd = socket(resinfo->ai_family, resinfo->ai_socktype, resinfo->ai_protocol)) > 0)
    printf("the socket is created\n");

  if(bind(sock_fd, resinfo->ai_addr, resinfo->ai_addrlen) == 0)
    printf("binding socket\n");

  if(listen(sock_fd, 10))
    printf("listening");

  while(1) {
    new_fd= accept(sock_fd, (struct sockaddr *) NULL, NULL);
    if(new_fd > 0)
      printf("accept\n");
    if(fork()) { 
      close(new_fd);
      continue;
    }
    else {
      close(sock_fd);
      while(recv(new_fd, buffer, strlen(buffer), 0) > 0)
	printf("%s", buffer); 
      close(new_fd);
      return;
    }
  }
  close(sock_fd);
}

int main() {
  server();
  return 0;
}

