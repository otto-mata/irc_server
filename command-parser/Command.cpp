#include "Command.hpp"

Command::Command(std::vector<Token>& tv)
{
  size_t i = 0;
  source = 0;
  params = 0;
  trailing = 0;
  for (std::vector<Token>::iterator it = tv.begin(); it < tv.end(); it++) {
    if (i == 0 && it->getType() == COLON)
      source = new std::string((++it)->getLexeme());
    else if (it->getType() == COLON) {
      trailing = new std::string();
      while (it < tv.end()) {
        if (it->getType() == STRING)
          trailing->append(it->getLexeme());
        else if (it->getType() == SPACE)
          trailing->append(" ");
        it++;
      }
    } else if ((i == 1 && source) || (!source && i == 0)) {
      cmd = it->getLexeme();
    } else {
      if (!params)
        params = new std::vector<std::string>();
      if (it->getType() == STRING)
        params->push_back(it->getLexeme());
    }
    i++;
  }
}

Command::~Command()
{
  if (source)
    delete source;
  if (params)
    delete params;
  if (trailing)
    delete trailing;
}

std::string
Command::toString(void)
{
  std::string s;

  s = "COMMAND: " + cmd + "\n";
  if (params) {
    s += "PARAMS: [";
    for (std::vector<std::string>::iterator it = params->begin();
         it < params->end();
         it++) {
      s += *it;
      if (it < params->end() - 1)
        s += ", ";
    }
    s += "]\n";
  }
  if (source) {
    s += "SOURCE: " + *source + "\n";
  }
  if (trailing) {
    s += "TRAILING: " + *trailing + "\n";
  }
  return s;
}
