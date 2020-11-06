#ifndef PARSER_H
#define PARSER_H

#include "../Lexer/Lexer.hpp"

namespace HLSL {

class Parser {
private:
    Lexer* lexer;
    unsigned int current_token_index;
public:
    Parser(Lexer* lexer);

    void readToken(Token::Type tokenType);
    void readNumeric();

    Token* currentToken();
    Token* previousToken();
    Token* getToken(unsigned int index);

};

}

#endif
