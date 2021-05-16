#include <stdio.h>
#include <sys/socket.h>

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080


// Simlates client that makes multiple requests simultaneously
int main(int argc, char const *argv[])
{
  int sock = 0; long valread;

  struct sockaddr_in serv_addr;
  size_t addrlen = sizeof(serv_addr);

  char *hello = "Hello from client";
  char buffer[1024] = {0};

  if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
  {
    perror("error creating socket");
    return -1;
  }

  memset((char *)&serv_addr, 0, addrlen);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // Convert IPv4 and IPv6 addresses from text to binary format
  if(inet_pton(AF_INET,"127.0.0.1", &serv_addr.sin_addr) <= 0)
  {
    printf("\nInvalid address/ Address not supported");
    return -1;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, (socklen_t)addrlen) < 0)
  {
    printf("\nConnection failed");
    return -1;
  }

  send(sock, hello, strlen(hello), 0);
  printf("Hello message sent\n");
  valread = read(sock, buffer, 1024);
  printf("%s\n", buffer);
  return 0;
}

