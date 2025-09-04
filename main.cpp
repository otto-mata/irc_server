#include "IRCServer.hpp"
#include "arguments.hpp"


int
main(int argc, char** argv)
{
  argument args = argument(argc, argv);
  int retCode = args.parseArgs();
  if (retCode)
    return retCode;
  
  try {
    IRCServer server = IRCServer(args.port, args.password);
    server.serve();
  } catch (const std::exception& e) {
    std::cerr << "Fatal error while starting/executing server." << std::endl;
  }
}
