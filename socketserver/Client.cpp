#include "Client.hpp"
#include "Socket.hpp"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unistd.h>

Client::Client(void)
{
  fd = -1;
  outlen = 0;
  mustSend = 0;
  disconnected = true;
  ::memset(buffer, 0, PKT_SIZE + 1);
  ::memset(rbuffer, 0, PKT_SIZE + 1);
}

Client::~Client()
{
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
  fd = -1;
  outlen = 0;
  disconnected = true;
  ::memset(buffer, 0, PKT_SIZE + 1);
  ::memset(rbuffer, 0, PKT_SIZE + 1);
}

Request*
Client::receive(void)
{
  ssize_t n = recv(fd, buffer, PKT_SIZE, 0);
  if (n <= 0) {
    if (n == 0)
      return (0);
    else
      perror("ServerSocket::Client::receive - recv");
  }
  outlen = n;
  return (new Request(std::string(buffer), fileno()));
}

ssize_t
Client::respond(void)
{
  ssize_t n = -1;
  if (mustSend) {
    n = send(fd, rbuffer, PKT_SIZE, 0);
    if (n <= 0) {
      if (n == 0)
        return (0);
      else
        perror("ServerSocket::Client::respond - send");
      reset();
    }
    delete res;

    std::cerr << "[+][Client] Sending data to client on fd " << fd << std::endl;
    res = 0;
    mustSend = 0;
  }
  return (n);
}

void
Client::setRes(Response* _res)
{
  res = _res;
  mustSend = 0;
  if (_res) {
    outlen = _res->size();
    ::memset(rbuffer, 0, PKT_SIZE);
    ::memcpy(rbuffer, res->raw(), outlen);
    mustSend = 1;
  }
}

bool
Client::connected(void)
{
  return !disconnected;
}

bool
Client::connected(void) const
{
  return !disconnected;
}
