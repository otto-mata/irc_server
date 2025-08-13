#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "common.hpp"
#include "Client.hpp"
#include <exception>

#ifndef BACKLOG
#define BACKLOG 5
#endif

#ifndef MAX_CLIENTS
#define MAX_CLIENTS 512
#endif

#ifndef POLL_INTERVAL
#define POLL_INTERVAL 500
#endif

class SocketServer
{
private:
  unsigned short port;
  int fd;
  SockAddrIn in;
  bool mustStop;
	Client clients[MAX_CLIENTS];

public:
  SocketServer(unsigned short serverPort);
  ~SocketServer();

  void serve(void);
  int fileno(void);
	virtual void handleRequest(Client& c);
	virtual void sendResponse(Client& c);
  class SocketServerException : public std::exception
  {
  public:
    virtual const char* what() const throw();
  };
};

#endif
