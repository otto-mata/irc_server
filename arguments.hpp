#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP
#include "logger/Logger.hpp"
#include <string>

struct argument
{
private:
  int _argc;
  char** _argv;

  static int atoi_overflow_guard(char* nptr, int* res)
  {
    int guard = 0;
    int sign = 1;

    *res = 0;
    while (*nptr == ' ' || (*nptr > 8 && *nptr < 14))
      nptr++;
    if (*nptr == '-' || *nptr == '+') {
      sign = *nptr == '-' ? -1 : 1;
      nptr++;
    }
    while (*nptr && *nptr >= '0' && *nptr <= '9' && !guard) {
      *res *= 10;
      guard = __builtin_sadd_overflow(*res, *nptr - '0', res);
      nptr++;
    }
    guard =  __builtin_smul_overflow(*res, sign, res);
    if (guard)
      return (0);
    return (!(*nptr) || (*nptr >= '0' && *nptr <= '9'));
  }

public:
  unsigned short port;
  std::string password;
  argument(int argc, char** argv)
  {
    _argc = argc;
    _argv = argv;
  }
  int parseArgs(void)
  {

    Logging::Engine console("ArgParse");
    if (_argc < 3) {
      console.err("Usage: " + std::string(_argv[0]) + " <port> <password>");
      return 1;
    }
    if (_argc > 3)
      console.warn(
        "Warning: Only the first two arguments (PORT and PASSWORD) are used.");
    int nPort;
    if (!atoi_overflow_guard(_argv[1], &nPort)) {
      console.err("Invalid port number: integer overflow or wrong format.");
      return 2;
    }
    if (nPort > 65535 || nPort < 1) {
      console.err("Invalid port number: should be in range [0 - 65536[.");
      return 2;
    }
    port = nPort;
    password = std::string(_argv[2]);
    return 0;
  }
};
#endif
