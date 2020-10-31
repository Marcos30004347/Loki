
#ifndef PARSER
#define PARSER

#include "AST.hpp"
#include "Lexer.hpp"

struct Parser {
    Lexer* lexer;
    Token* current_token;
    Token* previous_token;
};

Parser* initParser(Lexer* lexer);

void parserReadToken(Parser* parser, Token::TokenType type);

// PROGRAM → DECLARATION* EOF
AST* parseStart(Parser* parser);

// DECLARATION → VAR_DECL | STATEMENT;
AST* parseDeclaration(Parser* parser);

// STATEMENT → EXPRESSION_STATEMENT | IF | BLOCK
AST* parseStatement(Parser* parser);

// IF → 'if' '(' EXPRESSION ')' STATEMENT (else STATEMENT)? 
AST* parseIf(Parser* parser);

// WHILE  → 'while' '(' EXPRESSION ')' STATEMENT; 
AST* parseWhile(Parser* parser);

// DO_WHILE → 'do' '(' EXPRESSION ')' STATEMENT 'while'('EXPRESSION')'';' 
AST* parseDoWhile(Parser* parser);

// BLOCK → '{' DECLARATION '}'
AST* parseBlock(Parser* parser);

// VAR_DECL → IDENTIFIER (IDENTIFIER ('=' EXPRESSION)?) (IDENTIFIER ('=' EXPRESSION)?,)* ';'
AST* parseVariableDeclaration(Parser* parser);

// EXPRESSION_STATEMENT → EXPRESSION';'
AST* parseExpressionStatement(Parser* parser);

// EXPRESSION → ASSIGNMENT
AST* parseExpression(Parser* parser);

// ASSIGNMENT → IDENTIFIER '=' ASSIGNMENT | EQUALITY
AST* parseAssignment(Parser* parser);

// EQUALITY → COMPARISON (('!=' | '==') COMPARISON)*      ex: 1 == 1 != 3 == 3;
AST* parseEquality(Parser* parser);

// COMPARISON → TERM (('>' | '>=' | '<' | '<=') TERM)* 
AST* parseComparison(Parser* parser);

// TERM → FACTOR (('+' | '-') FACTOR)*
AST* parseTerm(Parser* parser);

// FACTOR → UNARY (('/' | '*') UNARY)*
AST* parseFactor(Parser* parser);

// UNARY → ('!' | '-')UNARY | PRIMARY
AST* parseUnary(Parser* parser);

// PRIMARY → NUMBER | STRING | 'true' | 'false' | 'nil | '('EXPRESSION')'
AST* parsePrimary(Parser* parser);


#endif