#include "IRCClient.hpp"

IRCClient::IRCClient()
  : socketClient(0)
{
}

IRCClient::IRCClient(Client& sockC)
  : socketClient(&sockC)
{
}

IRCClient::IRCClient(IRCClient const& other): socketClient(other.socketClient) {}

IRCClient&
IRCClient::operator=(IRCClient const& other)
{
  if (this != &other)
    socketClient = other.socketClient;
  return (*this);
}

IRCClient::~IRCClient() {}

int
IRCClient::fd(void)
{
  return socketClient->fileno();
}

int
IRCClient::fd(void) const
{
  return socketClient->fileno();
}
