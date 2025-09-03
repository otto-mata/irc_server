#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <string>

namespace Logging {

class Colors
{
public:
  static char const* const Reset;
  static char const* const Black;
  static char const* const Red;
  static char const* const Green;
  static char const* const Yellow;
  static char const* const Blue;
  static char const* const Magenta;
  static char const* const Cyan;
  static char const* const White;
  static char const* const Gold;
  static char const* const Grey;
};

typedef enum
{
  DEBUG,
  INFO,
  WARN,
  ERROR,
  FATAL
} LogLevel;

class Engine
{
private:
  std::string _name;
  int _warnCount;
  int _errCount;
  bool _fatalOccured;
  void _output(char const* const color,
               const char* level,
               std::string m);

public:
  Engine();
  Engine(std::string name);
  Engine(char const* name);
  ~Engine();
  bool fatalOccured(void) const;
  int warnings(void) const;
  int errors(void) const;
  void fatal(std::string m);
  void err(std::string m);
  void warn(std::string m);
  void log(std::string m);
  void debug(std::string m);
};

}

#endif /* LOGGER_HPP */
