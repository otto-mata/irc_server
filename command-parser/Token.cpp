#include "Token.hpp"
Token::Token(TokenType type, std::string lexeme)
  : _type(type)
  , _lex(lexeme)
{
}

Token::~Token() {}

std::string
Token::toString(void)
{
  std::string t;

  switch (_type)
  {
#define ENUMSW(X) case X: t.assign(#X); break;
  ENUMSW(STRING)
  ENUMSW(COLON)
  ENUMSW(SPACE)
  ENUMSW(EOL)
#undef ENUMSW
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
