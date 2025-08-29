#ifndef COMMON_HPP
#define COMMON_HPP

#ifndef PKT_SIZE
#define PKT_SIZE 1024
#endif

#include <netinet/in.h>
#include <string>
typedef struct sockaddr_in SockAddrIn;
struct Response
{
public:
  Response()
    : _body("")
  {
  }
  Response(std::string body)
    : _body(body)
  {
  }
  size_t size(void) { return _body.size(); }
  char const * raw(void) { return _body.c_str(); }

private:
  std::string _body;
};

struct Request
{
public:
  Request(int fd)
    : _body(""), _fd(fd)
  {
  }
  Request(std::string body, int fd)
    : _body(body), _fd(fd)
  {
  }
  size_t size(void) { return _body.size(); }
  char const * raw(void) { return _body.c_str(); }
  int origin(void) {return (_fd);}
private:
  std::string _body;
  int _fd;
};

#endif
