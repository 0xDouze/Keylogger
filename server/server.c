#include "server.h"

//port user?
//define backlog nb maxi de connexions acceptees

void server() {
  int sock_fd; //socket ecoutee
  int new_fd, reuse = 1;  //nouvelle connexion
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

  if (getaddrinfo(NULL, "4243", &hints, &resinfo) != 0)
    err(1, "err getaddrinfo");
  
  if((sock_fd= socket(resinfo->ai_family, resinfo->ai_socktype, resinfo->ai_protocol)) > 0)
    printf("the socket is created\n");
  
  if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    err(1, "setsockopt problem");
  
  if(bind(sock_fd, resinfo->ai_addr, resinfo->ai_addrlen) == 0)
    printf("binding socket\n");

  freeaddrinfo(resinfo); 
  if(!listen(sock_fd, 100)) {
    printf("listening\n");
    //loop for poll
    if(poll(fds, reuse, 3*60) < 0)
      perror("poll error");
  }
  else 
    printf("%d\n", sock_fd);

  for(int i= 0; i < reuse; i++) {
    if(fds[i].revents != POLLIN)
      perror("error revents");

    if(fds[i].fd == fds[0].fd) {
      while(1) {
	printf("coucou\n");
    	if((new_fd= accept(sock_fd, (struct sockaddr *) NULL, NULL)) != -1) {
	  //incoming co to pollfdstruc
	  fds[reuse].fd= new_fd;
	  fds[reuse].events= POLLIN;
	  reuse++;
	  break;
	}
      }
    }
    
    else {
      while(recv(fds[i].fd, buffer, strlen(buffer), 0)) {
	printf("%s\n", buffer);
	if (write(fds[reuse].fd, buffer, strlen(buffer)) == -1)
	  err(1, "erreur write");
      }
      close(fds[reuse].fd);
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
