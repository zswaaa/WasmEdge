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

  /// Reuse address
  int optval = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const void*>(&optval), sizeof(int)) < 0) {
    // TODO: errno
    return EXIT_FAILURE;
  }

  /// Bind the socket address
  sockaddr_in myAddr = {
      .sin_family = AF_INET,
      .sin_port = htons(PORT),
      .sin_addr =
          {
              .s_addr = htonl(INADDR_ANY),
          },
  };
  if (bind(fd, reinterpret_cast<const sockaddr *>(&myAddr), sizeof(myAddr)) <
      0) {
    // TODO: errno
    return EXIT_FAILURE;
  }

  /// Start listening
  if (listen(fd, 1) < 0) {
    // TODO: errno
    return EXIT_FAILURE;
  }

  /// Accept connection from client
  int clientFd;
  sockaddr srcAddr;
  socklen_t srcAddrLen;
  if ((clientFd = accept(fd, &srcAddr, &srcAddrLen)) < 0) {
    // TODO: errno
    return EXIT_FAILURE;
  }

  /// Receive message
  char buf[BUF_SIZE] = {0};
  if ((bytesRecv = recv(clientFd, buf, BUF_SIZE, 0)) < 0) {
    // TODO: errno
    return EXIT_FAILURE;
  }

  /// Reverse the message and send it back
  std::string msg(buf, bytesRecv);
  msg = std::string(msg.rbegin(), msg.rend());
  if ((bytesSent = send(clientFd, msg.c_str(), msg.length(), MSG_CONFIRM)) < 0) {
    // TODO: errno
    return EXIT_FAILURE;
  }

  /// Close connection
  if (close(clientFd) < 0) {
    // TODO: errno
    return EXIT_FAILURE;
  }

  /// Close TCP socket
  if (close(fd) < 0) {
    // TODO: errno
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
