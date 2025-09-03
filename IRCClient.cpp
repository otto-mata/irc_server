
#include "IRCClient.hpp"

IRCClient::IRCClient()
  : _socketClient(0)
{
}


IRCClient::IRCClient(Client& sockC)
  : _socketClient(&sockC)
{
}

IRCClient::IRCClient(IRCClient const& other): _socketClient(other._socketClient) {}

IRCClient&
IRCClient::operator=(IRCClient const& other)
{
  if (this != &other)
    _socketClient = other._socketClient;
  return (*this);
}

IRCClient::~IRCClient() {}

int
IRCClient::fd(void)
{
  if (_socketClient)
    return _socketClient->fileno();
  else
    return -1;
}

int
IRCClient::fd(void) const
{
  if (_socketClient)
    return _socketClient->fileno();
  else
    return -1;
}

bool
IRCClient::connected(void)
{
  if (_socketClient)
    return _socketClient->connected();
  else
   return false;
}

bool
IRCClient::connected(void) const
{
  if (_socketClient)
    return _socketClient->connected();
  else
   return false;
}


void
IRCClient::clear(void)
{
  _socketClient = 0;
}

void
IRCClient::addToBuffer(std::string& s)
{
  _buffering += s;
}

bool
IRCClient::bufferReady(void)
{
  return _buffering.find("\r\n") != std::string::npos;
}

std::string
IRCClient::getBuffer(void)
{
  return std::string(_buffering);
}

void
IRCClient::emptyBuffer(void)
{
  _buffering.clear();
}
