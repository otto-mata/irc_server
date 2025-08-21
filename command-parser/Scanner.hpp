#ifndef SCANNER_HPP
#define SCANNER_HPP
#include "Token.hpp"
#include <string>
#include <vector>

class Scanner
{
private:
  std::vector<Token> _tokens;
  std::string _source;
  int _start;
  int _curr;
  bool isAtEnd(void);
  void scanToken(void);
  char advance(void);
  char peek(void);
  void addStringToken(void);
  void addToken(TokenType t);

public:
  Scanner(std::string source);
  ~Scanner();
  std::vector<Token> scanTokens(void);
};

#endif /* SCANNER_HPP */
