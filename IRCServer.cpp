#include "IRCServer.hpp"
#include <algorithm>
#include <iostream>
#include <string>

IRCServer::IRCServer()
  : SocketServer(6667)
  , logger("IRCServer", Logging::DEBUG)
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
    logger.debug("Client disconnected");
    cMap.erase(itClient);
    return 0;
  } else if (itClient == cMap.end()) {
    logger.log("New client");
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
  logger.debug("Client disconnected");
}

void
IRCServer::createChannel(std::string channelName)
{
  if (_channels.find(channelName) != _channels.end()) {
    //! TODO: ERROR HANDLING

    logger.err("Cannot create channel '" + channelName +
               "'. Channel already exists.");
    return;
  }
  _channels[channelName] = IRCChannel(channelName);
}

void
IRCServer::addUserToChannel(IRCClient* c, std::string channelName)
{
  if (_channels.find(channelName) == _channels.end()) {
    //! TODO: ERROR HANDLING

    logger.err("Cannot add user to channel '" + channelName +
               "'. Channel doesn't exist.");
    return;
  }
  _channels[channelName].addUser(c);
}

void
IRCServer::addAdminToChannel(IRCClient* c, std::string channelName)
{
  if (_channels.find(channelName) == _channels.end()) {
    //! TODO: ERROR HANDLING

    logger.err("Cannot add admin to channel '" + channelName +
               "'. Channel doesn't exist.");
    return;
  }
  _channels[channelName].adminUser(c);
}
