
#ifndef PARSER
#define PARSER

#include "AST.hpp"
#include "Lexer.hpp"

struct Parser {
    Lexer* lexer;

    //State
    Token* current_token;
    Token* previous_token;
    bool is_parsing_loop;
};

Parser* initParser(Lexer* lexer);

void parserReadToken(Parser* parser, Token::TokenType type);

// TYPE → TYPEID | IDENTIFIER
AST* parseType(Parser* parser);

// DECLARATIONS → (DECLARATION | CONTEXT | EXPORT)* EOF
AST* parseStart(Parser* parser);

// FUNC_VAR_DECL → FUNC_DECL | VAR_DECL
AST* parseFuncVarDecl(Parser* parser);

// CONTEXT → 'context' IDENTIFIER '{' DECLARATION* '}'';'
AST* parseContext(Parser* parser);

// EXPORT → 'export' '{'IDENTIFIER: IDENTIFIER (',' IDENTIFIER: IDENTIFIER)+'}'';'
AST* parseExport(Parser* parser);

// UNIFORM → 'uniform' TYPE IDENTIFIER ';'
AST* parseUniform(Parser* parser);

// DECLARATION → FUNC_VAR_DECL | STRUCT_DECL | UNIFORM
AST* parseDeclaration(Parser* parser);

// STRUCT_DECL → 'struct' IDENTIFIER '{' VAR_DECL '}'';'
AST* parseStruct(Parser* parser);

// RETURN → 'return' EXPRESSION? ';'
AST* parseReturn(Parser* parser);

// FUNC_DECL → TYPE IDENTIFIER'('( TYPE IDENTIFIER ( "," TYPE IDENTIFIER )*')' BLOCK
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

// VAR_DECL → TYPE IDENTIFIER CHANNEL? ('=' EXPRESSION)? (','IDENTIFIER CHANNEL? ('=' EXPRESSION)?)* ';'
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

// PRIMARY → INTEGER | FLOAT | 'true' | 'false' | IDENTIFIER | '('EXPRESSION')'
AST* parsePrimary(Parser* parser);


#endif