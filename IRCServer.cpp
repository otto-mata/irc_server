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
    ircClients.begin(), ircClients.end(), client_by_fd(req->origin()));
  if (itClient != ircClients.end() && req->size() == 0) {
    std::cout << "[*][IRCServer] Disconnected client" << std::endl;
    ircClients.erase(itClient);
  }
  if (itClient == ircClients.end()) {
    std::cout << "[+][IRCServer] New client" << std::endl;
    Client& c = clientByFileno(req->origin());
    ircClients.push_back(IRCClient(c));
    itClient = ircClients.end() - 1;
  } 
  /*   std::cout << "Received request: " << req->size() << " byte"
              << (req->size() > 1 ? "s" : "") << ". " << req->raw() <<
    std::endl;



      try {
        Client c = clientByFileno(req->origin());
        ircClients.push_back(IRCClient(c));
        client = &ircClients.back();
      } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
      }

    } else
      client = &(*itClient); */
  std::cout << "[*][IRCServer] Request on fd #"<< itClient->fd() << std::endl;
  std::string reqBody(req->raw());
  if (reqBody.find("\r\n") == std::string::npos) {
  }
  if (reqBody == "PING\n")
    return new Response("PONG\r\n");
  return 0;
}

/* void
IRCServer::sendResponse(Client& c)
{
} */

void
IRCServer::onClientDisconnect(Client& c)
{
  VClients::iterator itClient = std::find_if(
    ircClients.begin(), ircClients.end(), client_by_fd(c.fileno()));
  ircClients.erase(itClient);
  std::cout << "[*][SocketServer] Client disconnected." << std::endl;
}
