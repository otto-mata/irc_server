#include "Client.hpp"
#include <cstring>
#include <unistd.h>
#include <iostream>
#include "Socket.hpp"

Client::Client(void)
{
  fd = 0;
  outlen = 0;
  ::memset(buffer, 0, PKT_SIZE + 1);
  ::memset(rbuffer, 0, PKT_SIZE + 1);
}

Client::~Client() {
  if (fd > 0)
    close(fd);
}

int
Client::fileno(void)
{
  return (fd);
}

void
Client::setfileno(int _fd)
{
  fd = _fd;
}

size_t
Client::outsz(void)
{
  return outlen;
}

void
Client::setoutsz(size_t n)
{
  outlen = n;
}

void
Client::reset(void)
{
  close(fd);
  fd = 0;
  outlen = 0;
  ::memset(buffer, 0, PKT_SIZE + 1);
}

ssize_t
Client::receive(void)
{
  ssize_t n = recv(fd, buffer, PKT_SIZE, 0);
  if (n <= 0) {
    if (n == 0)
      std::cout << "Client disconnected." << std::endl;
    else
      perror("ServerSocket::Client::receive - recv");
    reset();
  }
  outlen = n;
  return (n);
}

ssize_t
Client::respond(void)
{
  ssize_t n = send(fd, rbuffer, PKT_SIZE, 0);
  if (n <= 0) {
    if (n == 0)
      std::cout << "Client disconnected." << std::endl;
    else
      perror("ServerSocket::Client::respond - send");
    reset();
  }
  return (n);
}

char*
Client::res(void)
{
  return buffer;
}

char*
Client::req(void)
{
  return rbuffer;
}
