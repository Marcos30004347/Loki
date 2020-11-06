#ifndef LEXER_H
#define LEXER_H

#include "Token.hpp"
#include <vector>

namespace HLSL {
class Lexer {
private:
    const char* source;
    unsigned int head;
    char character;
    unsigned int line;
    unsigned int source_size;
    std::vector<Token*> tokens;

    void skipWhiteSpaces();
    void skipComments();
    void advance();

    void collectIdentifier();
    void collectStringLiteral();
    void collectNumberLiteral();
public:
    Lexer(const char* src);
    Token* getToken(unsigned int i);
    unsigned int getTokensCount();
};
}


#endif