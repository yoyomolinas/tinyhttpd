#include <stdio.h>
#include <sys/socket.h>

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>

#include "queue.h"

#define MULTITHREADED 0 // boolean

#define MAX_THREAD_COUNT 50
#define PORT 8080

#define RESPONSE_TIME 5 // in seconds

void respond(int sock) 
{
  char buffer[1024];
  read(sock, buffer, 1024);
  printf("%s\n", buffer);
  
  // A predefined response
  char *resp = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length:12\n\nHello world!";

  // Simulate delay in response
  sleep(RESPONSE_TIME);

  write(sock, resp, strlen(resp));
  printf("-------------------Message sent------------------\n");
  close(sock);
}

void * respond_thread(void *arg)
{
  int sock = *((int *)arg);
  respond(sock);
  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  
  int server_fd, new_socket; long valread;
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  //Create socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("Error initializing socket fiile descriptor");
    exit(EXIT_FAILURE);
  }

  memset((char *)&address, 0 , sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);
  

  if(bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
    perror("Error when binding");
    exit(EXIT_FAILURE);
  }

  if(listen(server_fd, 10) < 0) 
  {
    perror("Error when attempting to listening");
    exit(EXIT_FAILURE);
  }

  pthread_t tids[60];
  struct Queue *queue = create_queue();

  while(1) 
  {
    printf("\n++++++++++++ Waiting for new connection +++++++++++\n\n");
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))  < 0)
    {
      perror("error when accepting new connection");
      exit(EXIT_FAILURE);
    }

    if (!MULTITHREADED) respond(new_socket); continue;

    int tid = pthread_create(&tids[queue->cur + 1], NULL, respond_thread, &new_socket);
    if (tid != 0) {
      perror("Error creating thread to respond!");
    }

    add(queue, tid);
    printf("%i processes running concurrently", length(queue));
    while (length(queue) > MAX_THREAD_COUNT) {
      int tid = pop(queue);
      pthread_join(tids[tid], NULL);
    }
  }
  
  return 0;
}

