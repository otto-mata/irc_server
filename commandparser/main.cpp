#include "Scanner.hpp"
#include <string>
#include <iostream>
#include "Command.hpp"

int main(int argc, char **argv)
{
  if (argc < 2)
    return (1);
  std::string arg(argv[1]);
  Scanner s(arg);
  std::vector<Token> v = s.scanTokens();
  Command cmd = Command(v);
  std::cout << cmd.toString();
}
