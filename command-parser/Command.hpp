#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "Token.hpp"
#include <vector>

class Command
{
private:
  std::string* source;
  std::string cmd;
  std::vector<std::string>* params;
  std::string* trailing;
public:
  Command(std::vector<Token>& tv);
  ~Command();
  std::string toString(void);
};

#endif
