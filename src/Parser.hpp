
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

// START → PROGRAM* EOF
AST* parseStart(Parser* parser);

// PROGRAM → FUNC_DECL | VAR_DECL 
AST* parseProgram(Parser* parser);

// DECLARATION →  VAR_DECL | STATEMENT
AST* parseDeclaration(Parser* parser);

// RETURN → 'return' EXPRESSION? ';'
AST* parseReturn(Parser* parser);

// FUNC_DECL → IDENTIFIER IDENTIFIER'('( IDENTIFIER IDENTIFIER ( "," IDENTIFIER IDENTIFIER )*')' BLOCK
AST* parseFunctionDeclaration(Parser* parser);

// STATEMENT → EXPRESSION';' | IF | FOR | BLOCK | RETURN
AST* parseStatement(Parser* parser);

// FOR → 'for' '('(EXPRESSION | VAR_DECL)?';' EXPRESSION? ';' EXPRESSION? ')' STATEMENT 
AST* parseFor(Parser* parser);

// IF → 'if' '(' EXPRESSION ')' STATEMENT (else STATEMENT)? 
AST* parseIf(Parser* parser);

// WHILE  → 'while' '(' EXPRESSION ')' STATEMENT; 
AST* parseWhile(Parser* parser);

// DO_WHILE → 'do' '(' EXPRESSION ')' STATEMENT 'while'('EXPRESSION')'';' 
AST* parseDoWhile(Parser* parser);

// BLOCK → '{' DECLARATION* '}'
AST* parseBlock(Parser* parser);

// VAR_DECL → IDENTIFIER (IDENTIFIER ('=' EXPRESSION)?) (IDENTIFIER ('=' EXPRESSION)?,)* ';'
AST* parseVariableDeclaration(Parser* parser);

// EXPRESSION → ASSIGNMENT
AST* parseExpression(Parser* parser);

// ASSIGNMENT → IDENTIFIER '=' ASSIGNMENT | EQUALITY
AST* parseAssignment(Parser* parser);

// EQUALITY → COMPARISON (('!=' | '==') COMPARISON)*
AST* parseEquality(Parser* parser);

// COMPARISON → TERM (('>' | '>=' | '<' | '<=') TERM)* 
AST* parseComparison(Parser* parser);

// TERM → FACTOR (('+' | '-') FACTOR)*
AST* parseTerm(Parser* parser);

// FACTOR → UNARY (('/' | '*') UNARY)*
AST* parseFactor(Parser* parser);

// UNARY → ('!' | '-')UNARY | CALL
AST* parseUnary(Parser* parser);

// CALL → PRIMARY('('ARGUMENTS?')')?
AST* parseCall(Parser* parser);

// ARGUMENTS → EXPRESSION (','EXPRESSION)*
AST* parseArguments(Parser* parser);

// PRIMARY → NUMBER | IDENTIFIER | STRING | 'true' | 'false' | 'nil | '('EXPRESSION')'
AST* parsePrimary(Parser* parser);


#endif