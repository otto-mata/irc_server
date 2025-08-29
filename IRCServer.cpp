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

  std::map<int, IRCClient*>::iterator itClient = cMap.find(req->origin());
  IRCClient* user;

  if (itClient != cMap.end() && req->size() == 0) {
    std::cout << "[*][IRCServer] Disconnected client" << std::endl;
    cMap.erase(itClient);
    return 0;
  } else if (itClient == cMap.end()) {
    std::cout << "[+][IRCServer] New client" << std::endl;
    Client& c = clientByFileno(req->origin());
    cMap[req->origin()] = new IRCClient(c);
  }
  user = cMap[req->origin()];
  std::string reqBody(req->raw());
  user->addToBuffer(reqBody);
  std::cout << user->getBuffer() << std::endl;
  if (user->bufferReady()) {
    if (user->getBuffer() == "PING\r\n")
      return new Response("PONG\r\n");
  }

  return 0;
}

void
IRCServer::onClientDisconnect(Client& c)
{
  std::map<int, IRCClient*>::iterator itClient = cMap.find(c.fileno());

  cMap.erase(itClient);
  std::cout << "[*][SocketServer] Client disconnected." << std::endl;
}
