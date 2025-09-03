#include "IRCServer.hpp"
#include "logger/Logger.hpp"

static int
atoi_overflow_guard(char* nptr, int* res)
{
  int guard;

  guard = 0;
  *res = 0;
  while (*nptr == ' ' || (*nptr > 8 && *nptr < 14))
    nptr++;
  if (*nptr == '-' || *nptr == '+') {
    nptr++;
  }
  while (*nptr && *nptr >= '0' && *nptr <= '9' && !guard) {
    *res *= 10;
    guard = __builtin_sadd_overflow(*res, *nptr - '0', res);
    nptr++;
  }
  if (guard)
    return (0);
  return (!(*nptr) || (*nptr >= '0' && *nptr <= '9'));
}

int
main(int argc, char** argv)
{
  Logging::Engine console("IrcServ");
  if (argc < 3) {
    console.fatal("Usage: " + std::string(argv[0]) + " <port> <password>");
    return (1);
  }
  if (argc > 3)
    console.warn("Warning: Only the first two arguments (PORT and PASSWORD) are used.");
  int nPort;
  if (!atoi_overflow_guard(argv[1], &nPort)) {
    console.fatal("Invalid port number: integer overflow or wrong format.");
    return (2);
  }
  if (nPort > 65535) {
    console.fatal("Invalid port number: should be in range [0 - 65536[.");
    return (2);
  }
  unsigned short port = nPort;
  IRCServer server = IRCServer(port, std::string(argv[2]));
  server.serve();
}
