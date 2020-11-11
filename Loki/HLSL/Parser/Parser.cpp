#include "Parser.hpp"
#include <stdio.h>
#include <stdlib.h>

#include "Lib/String.hpp"

// GLobal declarations
#include "Declarations.hpp"
#include "Buffer.hpp"
#include "Struct.hpp"

#include "BuiltInTypes.hpp"

namespace HLSL {

ASTProgram::ASTProgram(): AST{NodeType::AST_PROGRAM} {}

Parser::Parser(Lexer* lexer) {
    this->lexer = lexer;
    this->current_token_index = 0;
    this->scope = new Scope();

    addBuiltInTypesToScope(this);
}

bool Parser::isNumeric() {
    return this->currentToken()->type == Token::TOKEN_FLOAT_LITERAL || this->currentToken()->type == Token::TOKEN_INT_LITERAL;
}
unsigned int Parser::getTokenIndex() {
    return this->current_token_index;
}

void Parser::setTokenIndex(unsigned int index) {
    this->current_token_index = index;
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
    if(this->current_token_index >= this->lexer->getTokensCount()) return nullptr;
    return this->lexer->getToken(this->current_token_index);
}

Token* Parser::previousToken() {
    return this->lexer->getToken(this->current_token_index - 1);
}

Token* Parser::getToken(unsigned int index) {
    return this->lexer->getToken(index);
}
ASTProgram* Parser::parseProgram(ProgramType type, const char* prorgamMain) {
    ASTProgram* program = new ASTProgram();
    program->program_type = type;
    program->program_main = copyStr(prorgamMain);
    program->program_declarations = std::vector<AST*>(0);

    while(this->currentToken() && this->current_token_index < this->lexer->getTokensCount()) {
        
        switch (this->currentToken()->type) {
            case Token::TOKEN_CBUFFER:
            case Token::TOKEN_TBUFFER:
                program->program_declarations.push_back(parseBuffer(this)); break;
                break;
            default:
                program->program_declarations.push_back(parseDeclaration(this));
                break;
        }
        while(this->currentToken() && this->currentToken()->type == Token::TOKEN_SEMICOLON) this->readToken(Token::TOKEN_SEMICOLON);
    }
    return program;
}

}