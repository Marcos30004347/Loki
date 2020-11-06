#include "Parser.hpp"
#include <stdio.h>
#include <stdlib.h>

namespace HLSL {

Parser::Parser(Lexer* lexer) {
    this->lexer = lexer;
    this->current_token_index = 0;
}

bool Parser::isNumeric() {
    return this->currentToken()->type == Token::TOKEN_FLOAT_LITERAL || this->currentToken()->type == Token::TOKEN_INT_LITERAL;
}


void Parser::readNumeric() {
    if(
        this->currentToken()->type != Token::TOKEN_FLOAT_LITERAL
        && this->currentToken()->type != Token::TOKEN_INT_LITERAL
    ) {
        printf("Expecting Numeric value at line '%u'!\n", this->currentToken()->line);
    }
    this->readToken(this->currentToken()->type);
}

void Parser::readToken(Token::Type tokenType) {
    Token* token = this->lexer->getToken(this->current_token_index);
    if(token->type != tokenType) {
        printf("Unexpected token '%s' at line '%i', expecting %i!\n", token->value, token->line, tokenType);
        exit(-1);
    }

    this->current_token_index++;
}

Token* Parser::currentToken() {
    return this->lexer->getToken(this->current_token_index);
}

Token* Parser::previousToken() {
    return this->lexer->getToken(this->current_token_index - 1);
}

Token* Parser::getToken(unsigned int index) {
    return this->lexer->getToken(index);
}

}