#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
int main(int argc, char *argv[]) {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    printf("Failed to create socket\n");
    return EXIT_FAILURE;
  }
  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);
  if (connect(sock, (struct sockaddr *)&server_addr, 80) == 0) {
    printf("connected\n");
    char buf[] = {1, 2, 3, 4};
    send(sock, buf, 4, MSG_CONFIRM);
  }

  return EXIT_SUCCESS;
}
