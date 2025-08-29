#include "Command.hpp"

Command::Command(std::vector<Token>& tv)
{
  size_t i = 0;
  _source = 0;
  _params = 0;
  _trailing = 0;
  _cmd.assign("");
  for (std::vector<Token>::iterator it = tv.begin(); it < tv.end(); it++) {
    if (it->getType() == SPACE)
      continue;
    if (i == 0 && it->getType() == COLON)
      _source = new std::string((++it)->getLexeme());
    else if ((i == 0 || i == 1) && it->getType() == STRING && _cmd.length() == 0) {
      _cmd = it->getLexeme();
    } else if (it->getType() == COLON) {
      _trailing = new std::string();
      while (it < tv.end()) {
        if (it->getType() == STRING)
          _trailing->append(it->getLexeme());
        else if (it->getType() == SPACE)
          _trailing->append(" ");
        it++;
      }
    } else if (it->getType() != EOL){
      if (!_params)
        _params = new std::vector<std::string>();
      if (it->getType() == STRING)
        _params->push_back(it->getLexeme());
    }
    i++;
  }
}

Command::~Command()
{
  if (_source)
    delete _source;
  if (_params)
    delete _params;
  if (_trailing)
    delete _trailing;
}

std::string
Command::toString(void)
{
  std::string s;

  s = "COMMAND: " + _cmd + "\n";
  if (_params) {
    s += "PARAMS: [";
    for (std::vector<std::string>::iterator it = _params->begin();
         it < _params->end();
         it++) {
      s += *it;
      if (it < _params->end() - 1)
        s += ", ";
    }
    s += "]\n";
  }
  if (_source) {
    s += "SOURCE: " + *_source + "\n";
  }
  if (_trailing) {
    s += "TRAILING: " + *_trailing + "\n";
  }
  return s;
}
