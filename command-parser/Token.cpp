#include "Token.hpp"
#define ENUMSW(X) case X: t.assign(#X); break;
Token::Token(TokenType type, std::string lexeme, int col)
  : _type(type)
  , _lex(lexeme)
  , _col(col)
{
}

Token::~Token() {}

std::string
Token::toString(void)
{
  std::string t;

  switch (_type)
  {
  ENUMSW(STRING)
  ENUMSW(COLON)
  ENUMSW(SPACE)
  ENUMSW(EOL)
  }
  return  t + " " + _lex;
}

TokenType
Token::getType(void)
{
  return _type;
}

std::string
Token::getLexeme(void)
{
  return _lex;
}
