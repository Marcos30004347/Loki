
#ifndef PARSER
#define PARSER

#include "AST.hpp"
#include "Scope.hpp"
#include "Lexer.hpp"

struct Parser {
    Scope* scope;
    Lexer* lexer;
    Token* current_token;
    Token* previous_token;
};

Parser* initParser(Lexer* lexer, Scope* scope);

void parserReadToken(Parser* parser, Token::TokenType type);

// PROGRAM → STATEMENT* EOF
AST* parseStart(Parser* parser);

// STATEMENT → VAR_DECL | EXPRESSION_STATEMENT
AST* parseStatement(Parser* parser, Scope* scope);

// VAR_DECL → IDENTIFIER (IDENTIFIER ('=' EXPRESSION)?) (IDENTIFIER ('=' EXPRESSION)?,)* ';'
AST* parseVariableDeclaration(Parser* parser, Scope* scope);

// EXPRESSION_STATEMENT → EXPRESSION';'
AST* parseExpressionStatement(Parser* parser, Scope* scope);

// EXPRESSION → ASSIGNMENT
AST* parseExpression(Parser* parser, Scope* scope);

// ASSIGNMENT → IDENTIFIER '=' ASSIGNMENT | EQUALITY
AST* parseAssignment(Parser* parser, Scope* scope);

// EQUALITY → COMPARISON (('!=' | '==') COMPARISON)*      ex: 1 == 1 != 3 == 3;
AST* parseEquality(Parser* parser, Scope* scope);

// COMPARISON → TERM (('>' | '>=' | '<' | '<=') TERM)* 
AST* parseComparison(Parser* parser, Scope* scope);

// TERM → FACTOR (('+' | '-') FACTOR)*
AST* parseTerm(Parser* parser, Scope* scope);

// FACTOR → UNARY (('/' | '*') UNARY)*
AST* parseFactor(Parser* parser, Scope* scope);

// UNARY → ('!' | '-')UNARY | PRIMARY
AST* parseUnary(Parser* parser, Scope* scope);

// PRIMARY → NUMBER | STRING | 'true' | 'false' | 'nil | '('EXPRESSION')'
AST* parsePrimary(Parser* parser, Scope* scope);


#endif