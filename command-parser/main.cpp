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
  IRCServer serv;
  Command cmd = Command(&serv);
  std::cout << cmd.getSource() << std::endl;
  std::cout << cmd.getCommand() << std::endl;
  std::cout << cmd.getParams()[1] << std::endl;
  std::cout << cmd.getTrailing() << std::endl;
}
