#include "Client.hpp"
#include "Socket.hpp"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unistd.h>

Client::Client(void)
{
  _fd = -1;
  _outlen = 0;
  _mustSend = 0;
  _disconnected = true;
  ::memset(_buffer, 0, PKT_SIZE + 1);
  ::memset(_rbuffer, 0, PKT_SIZE + 1);
}

Client::~Client()
{
  if (_fd > 0)
    close(_fd);
}

int
Client::fileno(void)
{
  return (_fd);
}

void
Client::setfileno(int fd)
{
  _fd = fd;
}

size_t
Client::outsz(void)
{
  return _outlen;
}

void
Client::setoutsz(size_t n)
{
  _outlen = n;
}

void
Client::reset(void)
{
  close(_fd);
  _fd = -1;
  _outlen = 0;
  _disconnected = true;
  ::memset(_buffer, 0, PKT_SIZE + 1);
  ::memset(_rbuffer, 0, PKT_SIZE + 1);
}

std::string
Client::receive(void)
{
  ssize_t n = recv(_fd, _buffer, PKT_SIZE, 0);
  if (n <= 0) {
    if (n == 0)
      return (0);
    else
      perror("ServerSocket::Client::receive - recv");
  }
  _outlen = n;
  return (new Request(std::string(_buffer), fileno()));
}

ssize_t
Client::respond(void)
{
  ssize_t n = -1;
  if (_mustSend) {
    n = send(_fd, _rbuffer, PKT_SIZE, 0);
    if (n <= 0) {
      if (n == 0)
        return (0);
      else
        perror("ServerSocket::Client::respond - send");
      reset();
    }
    delete _res;

    std::cerr << "[+][Client] Sending data to client on fd " << _fd << std::endl;
    _res = 0;
    _mustSend = 0;
  }
  return (n);
}

void
Client::setRes(Response* res)
{
  _res = res;
  _mustSend = 0;
  if (res) {
    _outlen = res->size();
    ::memset(_rbuffer, 0, PKT_SIZE);
    ::memcpy(_rbuffer, _res->raw(), _outlen);
    _mustSend = 1;
  }
}

bool
Client::connected(void)
{
  return !_disconnected;
}

bool
Client::connected(void) const
{
  return !_disconnected;
}
