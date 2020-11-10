#ifndef GLSL_LEXER_H
#define GLSL_LEXER_H

#include "Token.hpp"
#include <vector>

namespace GLSL {
class Lexer {
private:
    const char* source;
    unsigned int head;
    char character;
    unsigned int line;
    unsigned int source_size;
    std::vector<Token*> tokens;

    bool skipWhiteSpaces();
    bool skipComments();
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