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
  void  reset(void);

public:
  Client(void);
  ~Client();
  int fileno(void);
  void setfileno(int fd);
  size_t outsz(void);
  void setoutsz(size_t n);
  ssize_t receive(void);
  ssize_t respond(void);
  char *res(void);
  char *req(void);
};


#endif
