#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP
#define PKT_SIZE 1<<14

#include "socket-server/Socket.hpp"
#include "IRCClient.hpp"
#include <vector>
class IRCServer : public SocketServer
{
private:
  std::vector<IRCClient> ircClients;
public:
  IRCServer(/* args */);
  ~IRCServer();
  virtual void handleRequest(Client& c);
  virtual void sendResponse(Client& c);
};

#endif
