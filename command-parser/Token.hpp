#ifndef TOKEN_HPP
#define TOKEN_HPP
#include "TokenType.hpp"
#include <string>

class Token
{
  private:
    TokenType _type;
    std::string _lex;
  public:
    Token(TokenType type, std::string lexeme);
    ~Token();
    std::string toString(void);
    TokenType getType(void);
    std::string getLexeme(void);
};

#endif /* TOKEN_HPP */
