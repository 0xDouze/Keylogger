#include <errno.h>
#include "server.h"

//port user?
//define backlog nb maxi de connexions acceptees

void server() {
  int sock_fd; //socket ecoutee
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

  if (getaddrinfo(NULL, "4243", &hints, &resinfo) != 0)
    err(1, "err getaddrinfo");

  if((sock_fd= socket(resinfo->ai_family, resinfo->ai_socktype, resinfo->ai_protocol)) > 0)
    printf("the socket is created\n");
  fds[0].fd= sock_fd;
  if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    err(1, "setsockopt problem");

  if(bind(sock_fd, resinfo->ai_addr, resinfo->ai_addrlen) == 0)
    printf("binding socket\n");

  freeaddrinfo(resinfo);
  if(!listen(sock_fd, 100)) {
    printf("listening\n");
    //loop for poll
    if(poll(fds, reuse, 1000) < 0)
      perror("poll error");
  }
  else
    printf("%d\n", sock_fd);

  while(1) {
    /* poll(fds, reuse, 1000); */
    /* for(int i= 0; i < reuse; i++) { */
    /*   if(fds[i].revents != POLLIN) */
    /*     perror("error revents"); */
    /*   ioctl(fds[0].fd, FIONBIO, &n); */
    /*   if(fds[i].fd == fds[0].fd) { */
    /*     while((new_fd= accept(sock_fd, (struct sockaddr *)NULL, NULL)) != -1) { */
    /*       //incoming co to pollfdstruc */
    /*       if (new_fd == EAGAIN || new_fd == EWOULDBLOCK) */
    /*         break; */
    /*       printf("while accept\n"); */
    /*       fds[reuse + 1].fd= new_fd; */
    /*       fds[reuse + 1].events= POLLIN; */
    /*       reuse++; */
    /*       printf("reuse\n"); */
    /*     } */
    /*   } */


    /*   else { */
    /*     ioctl(fds[i].fd, FIONREAD, &n); */
    /*     printf("ioctl\n"); */
    /*     //if(n == 0) { */
    /*       printf("n = 0\n"); */
    /*       close(fds[i].fd); */
    /*       reuse--; */
    /*       fds[i].events= 0; */
    /*       fds[i].fd= -1; */
    /*     //} */
    /*   	//else { */
    /*       printf("n = 0 else\n"); */
    /*       read(fds[i].fd, buffer, 256); */
    /*       printf("%s\n", buffer); */
    /*       write(fds[reuse].fd, buffer, strlen(buffer)); */
    /*     //} */
    /*   } */
    /*   printf("%d\n", i); */
    /* } */
    poll(fds, reuse, 1000000);
    for(int i = 0; i < reuse; i++)
      {
        if (fds[i].revents != POLLIN)
          printf("ca marche pas pollin\n");
        ioctl(fds[0].fd, FIONBIO, 1);
        printf("%d\n",i);
        if (fds[i].fd == fds[0].fd)
          {
            do
              {
                if (reuse == 4)
                  break;
                printf("coucou ca va la famille? reuse vaut : %d\n", reuse);
                new_fd = accept(fds[i].fd, (struct sockaddr*)NULL, NULL);
                if (new_fd == -1)
                  break;
                fds[reuse].fd = new_fd;
                fds[reuse].events = POLLIN;
                reuse++;
              } while (new_fd != -1);
          }
        else
          {
            /* ioctl(fds[i].fd, FIONREAD, &n); */
            /* if (n < 1) */
            /*   { */
            /*     close(fds[i].fd); */
            /*     fds[i].fd = -1; */
            /*   } */
            /* else */
            /*   { */
                if ((n = read(fds[i].fd, buffer, 256)) < 0)
                  close(fds[i].fd);
                printf("%s\n", buffer);
                memset(buffer, 0, 256);
                /* } */
          }
      }
  }
}

int main() {
  server();
  return 0;
}
