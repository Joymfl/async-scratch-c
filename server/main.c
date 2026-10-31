#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    printf("Failed to create socket\n");
    return EXIT_FAILURE;
  }
  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);
  inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

  int res = bind(sock, (struct sockaddr *)(&server_addr), 80);
  printf("res: %d\n", res);
  socklen_t addr;

  accept(sock, (struct sockaddr *)(&server_addr), &addr);
  printf("listening on port 8080\n");
  int result = listen(sock, 1);
  // for (;;) {
  //   accept(sock, (struct sockaddr *)(&server_addr), &addr);
  //   char buf[32];
  //
  //   inet_ntop(AF_INET, &addr, buf, addr);
  //   printf("connection addr: %s", buf);
  // }
  char recv_buf[5];

  // printf("receiving on: %s \n");
  for (;;) {
    int result = recv(sock, recv_buf, 5, MSG_WAITALL);
    if (result != -1) {
      printf("data: %s\n", recv_buf);
    }
  }

  return EXIT_SUCCESS;
}
