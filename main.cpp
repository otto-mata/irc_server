#include "IRCServer.hpp"

int main(void)
{
  IRCServer server = IRCServer();
  server.serve();
}
