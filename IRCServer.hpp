#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include "IRCChannel.hpp"
#include "IRCClient.hpp"
#include "logger/Logger.hpp"
#include "socket-server/Socket.hpp"
#include <map>
#include <vector>

class IRCServer : public SocketServer
{
private:
  std::string _pass;
  std::map<int, IRCClient*> cMap;
  std::map<std::string, IRCChannel> _channels;
  Logging::Engine logger;

public:
  IRCServer(unsigned short portNumber, std::string pass);
  ~IRCServer();
  virtual Response* onRequest(Request* req);
  virtual void onClientDisconnect(Client& c);
  void createChannel(std::string channelName);
  void addUserToChannel(IRCClient* c, std::string channelName);
  void addAdminToChannel(IRCClient* c, std::string channelName);
};

#endif
