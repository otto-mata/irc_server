#ifndef IRCCLIENT_HPP
#define IRCCLIENT_HPP
#include "socket-server/Client.hpp"
#include <string>

class IRCClient
{
private:
  Client* socketClient;
  std::string _nickname;

public:
  IRCClient();
  IRCClient(Client& sockC);
  IRCClient(IRCClient const& other);
  IRCClient& operator=(IRCClient const& other);
  ~IRCClient();
  int fd(void);
  int fd(void) const;
};

#endif
