#include "Logger.hpp"
#include <iostream>

void
Logging::Engine::_output(char const* const color,
                         const char* level,
                         std::string m)
{
  std::cout << color << "[" + _name + "][" + level + "] " << m
            << Logging::Colors::Reset << std::endl;
}

Logging::Engine::~Engine(){}

Logging::Engine::Engine()
  : _name("Log")
  , _level(INFO)
  , _warnCount(0)
  , _errCount(0)
  , _fatalOccured(false)
{
}

Logging::Engine::Engine(std::string name)
  : _name(name)
  , _level(INFO)
  , _warnCount(0)
  , _errCount(0)
  , _fatalOccured(false)
{
}

Logging::Engine::Engine(std::string name, LogLevel level)
  : _name(name)
  , _level(level)
  , _warnCount(0)
  , _errCount(0)
  , _fatalOccured(false)
{
}

Logging::Engine::Engine(char const* name) 
  : _name(name)
  , _level(INFO)
  , _warnCount(0)
  , _errCount(0)
  , _fatalOccured(false)
{
}
Logging::Engine::Engine(char const* name, LogLevel level)
  : _name(name)
  , _level(level)
  , _warnCount(0)
  , _errCount(0)
  , _fatalOccured(false)
{
}
bool
Logging::Engine::fatalOccured(void) const
{
  return _fatalOccured;
}

int
Logging::Engine::warnings(void) const
{
  return _warnCount;
}

int
Logging::Engine::errors(void) const
{
  return _errCount;
}

void
Logging::Engine::fatal(std::string m)
{
  _output(Colors::Red, "FATAL", m);
  _fatalOccured = true;
}

void
Logging::Engine::err(std::string m)
{
  _output(Colors::Red, "ERROR", m);
  _errCount++;
}

void
Logging::Engine::warn(std::string m)
{
  _output(Colors::Gold, "WARNING", m);
  _warnCount++;
}

void
Logging::Engine::log(std::string m)
{
  _output(Colors::White, "INFO", m);
}

void
Logging::Engine::debug(std::string m)
{
  _output(Colors::Yellow, "DEBUG", m);
}
