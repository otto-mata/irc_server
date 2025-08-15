#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "common.hpp"

class Client
{
private:
  int fd;
  char buffer[PKT_SIZE + 1];
  char rbuffer[PKT_SIZE + 1];
  size_t outlen;
  Response* res;
  bool mustSend;
  bool disconnected;

public:
  Client(void);
  ~Client();
  int fileno(void);
  void setfileno(int fd);
  size_t outsz(void);
  void setoutsz(size_t n);
  Request* receive(void);
  ssize_t respond(void);
  void setRes(Response* res);
  bool connected(void);
  bool connected(void) const;
  void reset(void);
};

#endif
