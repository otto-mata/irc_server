#include "IRCServer.hpp"
#include <algorithm>
#include <iostream>
#include <string>
struct client_by_fd
{
public:
  client_by_fd(int cfd)
    : fd(cfd)
  {
  }
  bool operator()(IRCClient const& c) { return c.fd() == fd; }

private:
  int fd;
};

IRCServer::IRCServer()
  : SocketServer(6667)
{
}

IRCServer::~IRCServer() {}

Response*
IRCServer::onRequest(Request* req)
{
  if (!req)
    return (0);

  VClients::iterator itClient = std::find_if(
    _ircClients.begin(), _ircClients.end(), client_by_fd(req->origin()));
  if (itClient != _ircClients.end() && req->size() == 0) {
    std::cout << "[*][IRCServer] Disconnected client" << std::endl;
    _ircClients.erase(itClient);
  }
  if (itClient == _ircClients.end()) {
    std::cout << "[+][IRCServer] New client" << std::endl;
    Client& c = clientByFileno(req->origin());
    _ircClients.push_back(IRCClient(c));
    itClient = _ircClients.end() - 1;
  }
  std::string reqBody(req->raw());
  itClient->addToBuffer(reqBody);
  std::cout << itClient->getBuffer() << std::endl; 
  if (itClient->bufferReady()) {
    if (itClient->getBuffer() == "PING\r\n")
      return new Response("PONG\r\n");
  }

  return 0;
}

void
IRCServer::onClientDisconnect(Client& c)
{
  VClients::iterator itClient = std::find_if(
    _ircClients.begin(), _ircClients.end(), client_by_fd(c.fileno()));
  _ircClients.erase(itClient);
  std::cout << "[*][SocketServer] Client disconnected." << std::endl;
}
