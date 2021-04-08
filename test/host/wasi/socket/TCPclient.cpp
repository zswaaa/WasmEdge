// SPDX-License-Identifier: Apache-2.0
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd;
  ssize_t bytesSent, bytesRecv;

  /// Open TCP socket
  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    // TODO: errno
    return EXIT_FAILURE;
  }

  /// Connect to server
  sockaddr_in destAddr = {
      .sin_family = AF_INET,
      .sin_port = htons(PORT),
      .sin_addr =
          {
              .s_addr = htonl(INADDR_ANY),
          },
  };
  if (connect(fd, reinterpret_cast<const sockaddr *>(&destAddr),
              sizeof(destAddr)) < 0) {
    // TODO: errno
    return EXIT_FAILURE;
  }

  /// Send message
  std::string msg = "hydrogen";
  if ((bytesSent = send(fd, msg.c_str(), msg.length(), 0)) < 0) {
    // TODO: errno
    return EXIT_FAILURE;
  }

  /// Shutdown write
  if (shutdown(fd, SHUT_WR) < 0) {
    // TODO: errno
    return EXIT_FAILURE;
  }

  /// Receive message
  char buf[BUF_SIZE] = {0};
  if ((bytesRecv = recv(fd, buf, BUF_SIZE, MSG_WAITALL)) < 0) {
    // TODO: errno
    return EXIT_FAILURE;
  }

  /// Output message
  std::cout << std::string(buf, bytesRecv);

  /// Close TCP socket
  if (close(fd) < 0) {
    // TODO: errno
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
