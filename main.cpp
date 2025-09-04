#include "IRCServer.hpp"

int main(int argc, char **argv)
{
  if (argc < 2)
    return (1);
  IRCServer serv;
  Command cmd = Command(&serv);
  std::string text = argv[1];
  serv.createChannel("chez");
  cmd.parse(text);
  cmd.execute();
  /*std::cout << cmd.getSource() << std::endl;
  std::cout << cmd.getCommand() << std::endl;
  //std::cout << cmd.getParams()[1] << std::endl;
  std::cout << cmd.getTrailing() << std::endl;*/
}
