#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include "IRCChannel.hpp"
#include "IRCClient.hpp"
#include "socket-server/Socket.hpp"
#include <map>
#include <vector>
#include <map>
#include "logger/Logger.hpp"

typedef std::vector<IRCClient> VClients;

class IRCServer : public SocketServer
{
private:
  std::map<int, IRCClient*> _cMap;
  std::map<std::string, IRCChannel> _channels;
  Logging::Engine _logger;
public:
  IRCServer(/* args */);
  ~IRCServer();
  virtual Response* onRequest(Request* req);
  virtual void onClientDisconnect(Client& c);
  void createChannel(std::string channelName);
  void addUserToChannel(IRCClient* c, std::string channelName);
  void addAdminToChannel(IRCClient* c, std::string channelName);
};

#endif
