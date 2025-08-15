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
  if (socketClient)
    return socketClient->fileno();
  else
    return -1;
}

int
IRCClient::fd(void) const
{
  if (socketClient)
    return socketClient->fileno();
  else
    return -1;
}

bool
IRCClient::connected(void)
{
  if (socketClient)
    return socketClient->connected();
  else
   return false;
}

bool
IRCClient::connected(void) const
{
  if (socketClient)
    return socketClient->connected();
  else
   return false;
}


void
IRCClient::clear(void)
{
  socketClient = 0;
}
