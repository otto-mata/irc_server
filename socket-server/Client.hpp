#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "common.hpp"

class Client
{
private:
  int _fd;
  char _buffer[PKT_SIZE + 1];
  char _rbuffer[PKT_SIZE + 1];
  size_t _outlen;
  Response* _res;
  bool _mustSend;
  bool _disconnected;

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
