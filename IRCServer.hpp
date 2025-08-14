#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include "socket-server/Socket.hpp"
#include "IRCClient.hpp"
#include <vector>


typedef std::vector<IRCClient> VClients;

class IRCServer : public SocketServer
{
private:
  std::vector<IRCClient> ircClients;
public:
  IRCServer(/* args */);
  ~IRCServer();
  virtual Response* onRequest(Request* req);
  /* virtual void sendResponse(Client& c); */
};

#endif
