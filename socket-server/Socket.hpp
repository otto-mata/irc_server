#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "Client.hpp"
#include "common.hpp"
#include <exception>
#include <sstream>
#include <stdexcept>

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
  unsigned short _port;
  int _fd;
  SockAddrIn _in;
  bool _mustStop;
  Client _clients[MAX_CLIENTS];

public:
  SocketServer(unsigned short serverPort);
  ~SocketServer();

  void serve(void);
  int fileno(void);
  virtual void onClientDisconnect(Client& c);
  virtual Response* onRequest(Request* req);
  Client& clientByFileno(int fd);
  class SocketServerException : public std::exception
  {
  public:
    virtual const char* what() const throw();
  };
  class ClientNotFound : public std::exception
  {
  public:
    virtual const char* what() const throw() { return "Client not found."; }
  };
};

#endif
