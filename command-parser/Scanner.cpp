#include "Scanner.hpp"
#include <stdexcept>

bool
Scanner::isAtEnd(void)
{
  return _curr >= _source.length();
}

void
Scanner::scanToken(void)
{
  char c = advance();
  switch (c) {
    case ':':
      addToken(COLON);
      break;
    case ' ':
      addToken(SPACE);
      break;
    default:
      addStringToken();
      break;
  }
}

char
Scanner::advance(void)
{
  try {
    return _source.at(_curr++);
  } catch (const std::out_of_range& e) {
    _curr = _source.length();
    return '\0';
  }
}

char
Scanner::peek(void)
{
  try {
    return _source.at(_curr);
  } catch (const std::out_of_range& e) {
    _curr = _source.length();
    return '\0';
  }
}

void
Scanner::addStringToken(void)
{
  while (peek() != ' ' && peek() != ':' && !isAtEnd())
    advance();
  std::string s = _source.substr(_start, _curr - _start);
  _tokens.push_back(Token(STRING, s));
}

void
Scanner::addToken(TokenType t)
{
  std::string s = _source.substr(_start, _curr - _start);
  _tokens.push_back(Token(t, s));
}

Scanner::Scanner(std::string source)
  : _source(source)
{
  _tokens = std::vector<Token>();
  _start = 0;
  _curr = 0;
}

Scanner::~Scanner() {}

std::vector<Token>
Scanner::scanTokens(void)
{
  while (!isAtEnd())
  {
    _start = _curr;
    scanToken();
  }
  _tokens.push_back(Token(EOL, ""));
  return _tokens;
}
