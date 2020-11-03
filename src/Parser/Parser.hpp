
#ifndef PARSER
#define PARSER

#include "AST/AST.hpp"
#include "Lexer/Lexer.hpp"

struct Parser {
    Lexer* lexer;
    Token* current_token;
    Token* previous_token;
};

Parser* initParser(Lexer* lexer);

void parserReadToken(Parser* parser, Token::TokenType type);

// START → DECLARATIONS* EOF
AST* parseStart(Parser* parser);

// FUNC_VAR_DECL → FUNC_DECL | VAR_DECL
AST* parseFuncVarDecl(Parser* parser);

// DECLARATION → FUNC_VAR_DECL | STRUCT_DECL
AST* parseDeclaration(Parser* parser);

// STRUCT_DECL → 'struct' IDENTIFIER '{' FUNC_VAR_DECL '}'';'
AST* parseStruct(Parser* parser);

// RETURN → 'return' EXPRESSION? ';'
AST* parseReturn(Parser* parser);

// FUNC_DECL → IDENTIFIER IDENTIFIER'('( IDENTIFIER IDENTIFIER CHANNEL? ( "," IDENTIFIER IDENTIFIER CHANNEL? )*')' BLOCK
AST* parseFunctionDeclaration(Parser* parser);

//CHANNEL → ('<-' | '->') IDENTIFIER
AST* parseChannel(Parser* parser);

// STATEMENT → VAR_DECL';' | EXPRESSION | IF | WHILE | DO_WHILE | FOR |  BLOCK | RETURN | BREAK | SWITCH
AST* parseStatement(Parser* parser);

// FOR → 'for' '('(EXPRESSION | VAR_DECL)?';' EXPRESSION? ';' EXPRESSION? ')' STATEMENT 
AST* parseFor(Parser* parser);

// IF → 'if' '(' EXPRESSION ')' STATEMENT (else STATEMENT)? 
AST* parseIf(Parser* parser);

// WHILE  → 'while' '(' EXPRESSION ')' STATEMENT; 
AST* parseWhile(Parser* parser);

// SWITCH  → 'switch' '(' EXPRESSION ')' '{' ('case' expression ':' STATEMENT? 'break'? )* ('default'':' STATEMENT? 'break'?)'}'; 
AST* parseSwitch(Parser* parser);

// DO_WHILE → 'do' '(' EXPRESSION ')' STATEMENT 'while'('EXPRESSION')'';' 
AST* parseDoWhile(Parser* parser);

// BLOCK → '{' STATEMENT* '}'
AST* parseBlock(Parser* parser);

// VAR_DECL → IDENTIFIER IDENTIFIER CHANNEL? ('=' EXPRESSION)? (','IDENTIFIER CHANNEL? ('=' EXPRESSION)?)* ';'
AST* parseVariableDeclaration(Parser* parser);

// EXPRESSION → IDENTIFIER ('=' | '|=' | '&=' | '+=' | '-=' ) ASSIGNMENT | EQUALITY
AST* parseExpression(Parser* parser);

// EQUALITY → COMPARISON (('!=' | '==') COMPARISON)*
AST* parseEquality(Parser* parser);

// COMPARISON → TERM (('>' | '>=' | '<' | '<=' | '|' | '&' | '&&' | '||' ) TERM)* 
AST* parseComparison(Parser* parser);

// TERM → FACTOR (('+' | '-') FACTOR)*
AST* parseTerm(Parser* parser);

// FACTOR → UNARY (('/' | '*') UNARY)*
AST* parseFactor(Parser* parser);

// UNARY → ('!' | '-' | '++' | '--')UNARY | UNARY('++' | '--') | PRIMARY
AST* parseUnary(Parser* parser);

// CALL → PRIMARY('('ARGUMENTS?')')?
AST* parseCall(Parser* parser);

// ARGUMENTS → EXPRESSION (','EXPRESSION)*
AST* parseArguments(Parser* parser);

// PRIMARY → INTEGER | FLOAT | 'true' | 'false' | IDENTIFIER | '('EXPRESSION')'
AST* parsePrimary(Parser* parser);

#endif