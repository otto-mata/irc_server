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
    : body("")
  {
  }
  Response(std::string _body)
    : body(_body)
  {
  }
  size_t size(void) { return body.size(); }
  char const * raw(void) { return body.c_str(); }

private:
  std::string body;
};

struct Request
{
public:
  Request(int _fd)
    : body(""), fd(_fd)
  {
  }
  Request(std::string _body, int _fd)
    : body(_body), fd(_fd)
  {
  }
  size_t size(void) { return body.size(); }
  char const * raw(void) { return body.c_str(); }
  int origin(void) {return (fd);}
private:
  std::string body;
  int fd;
};

#endif
