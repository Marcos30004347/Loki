
#ifndef PARSER
#define PARSER

#include "AST.hpp"
#include "Scope.hpp"
#include "Lexer.hpp"
#include <stack>
struct Parser {
    Scope* scope;
    Lexer* lexer;
    Token* current_token;
    Token* previous_token;
    std::stack<Token*> token_stack;
};

Parser* initParser(Lexer* lexer, Scope* scope);

AST* parseStart(Parser* parser) ;

void parserReadToken(Parser* parser, Token::TokenType type);

// EXPRESSION → EQUALITY;
AST* parseExpression(Parser* parser, Scope* scope);

// EQUALITY → COMPARISON (('!=' | '==') COMPARISON)*;      ex: 1 == 1 != 3 == 3;
AST* parseEquality(Parser* parser, Scope* scope);

// COMPARISON → TERM (('>' | '>=' | '<' | '<=') TERM)* ;
AST* parseComparison(Parser* parser, Scope* scope);

// TERM → FACTOR (('+' | '-') FACTOR)*;
AST* parseTerm(Parser* parser, Scope* scope);

// FACTOR → UNARY (('/' | '*') UNARY)*;
AST* parseFactor(Parser* parser, Scope* scope);

// UNARY → ('!' | '-')UNARY | PRIMARY
AST* parseUnary(Parser* parser, Scope* scope);

// PRIMARY → NUMBER | STRING | 'true' | 'false' | 'nil | '('EXPRESSION')';
AST* parsePrimary(Parser* parser, Scope* scope);

#endif