#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include "socket-server/Socket.hpp"
#include "IRCClient.hpp"
#include <vector>
#include <map>

typedef std::vector<IRCClient> VClients;

class IRCServer : public SocketServer
{
private:
  std::vector<IRCClient> ircClients;
  std::map<int, IRCClient*> cMap;
public:
  IRCServer(/* args */);
  ~IRCServer();
  virtual Response* onRequest(Request* req);
  virtual void onClientDisconnect(Client& c);
};

#endif
