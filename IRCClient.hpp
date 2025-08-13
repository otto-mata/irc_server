#ifndef IRCCLIENT_HPP
#define IRCCLIENT_HPP
#include "socket-server/Client.hpp"

class IRCClient
{
private:
  Client& socketClient;
public:
  IRCClient(Client& sockC);
  ~IRCClient();
};

#endif
