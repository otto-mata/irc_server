#ifndef IRCCLIENT_HPP
#define IRCCLIENT_HPP
#include "socket-server/Client.hpp"
#include <string>
#include <sstream>

class IRCClient
{
private:
  Client* socketClient;
  std::string _nickname;
  std::string _realname;
  std::string _hostname;
  std::string _username;
  std::string _buffering;
  
  bool _isNew;



public:
  IRCClient();
  IRCClient(Client& sockC);
  IRCClient(IRCClient const& other);
  IRCClient& operator=(IRCClient const& other);
  ~IRCClient();
  int fd(void);
  int fd(void) const;
  bool connected(void);
  bool connected(void) const;
  void clear(void);
  void addToBuffer(std::string& s);
  bool bufferReady(void);
  std::string getBuffer(void);
  void emptyBuffer(void);
};

#endif
