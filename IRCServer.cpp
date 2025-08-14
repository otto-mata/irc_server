#include "IRCServer.hpp"
#include <algorithm>
#include <string>
#include <iostream>
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
  VClients::iterator itClient = std::find_if(
    ircClients.begin(), ircClients.end(), client_by_fd(req->origin()));

  IRCClient* client;

  if (itClient == ircClients.end()) {
    try {
      Client c = clientByFileno(req->origin());
      ircClients.push_back(IRCClient(c));
      client = &ircClients.back();
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
    }

  } else
    client = &(*itClient);
  return new Response("hello world");
}

/* void
IRCServer::sendResponse(Client& c)
{
} */
