#include "Token.hpp"
#include "Lib/String.hpp"

namespace GLSL {

Token::Token(Token::Type type, char* value, unsigned int line) {
    this->type = type;
    this->value = value;
    this->line = line;
}

Token::Token(Token::Type type, const char* value,  unsigned int line) {
    this->type = type;
    this->value = copyStr(value);
    this->line = line;
}

}