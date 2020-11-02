
#ifndef LEXER_H
#define LEXER_H


struct Lexer {
    char* contents;
    unsigned int i;
    char c;
};


struct Token {

    enum TokenType {
        IDENTIFIER,
        EQUALS,
        STRING,
        SEMICOLON,
        OPEN_PARENTESIS,
        CLOSE_PARENTESIS,
        OPEN_BRACKET,
        CLOSE_BRACKET,
        COMMA,
        PERIOD,
        INTEGER,
        ADDITION,
        SUBTRACION,
        DIVISION,
        MULTIPLICATION,
        DIFFERENT,
        EQUALS_EQUALS,
        GREATER,
        GREATER_OR_EQUALS,
        LESS,
        LESS_OR_EQUALS,
        EXCLAMATION,
        MINUS,
        TOKEN_EOF,
        IF,
        WHILE,
        DO,
        SWITCH,
        CASE,
        DEFAULT,
        BREAK,
        ELSE,
        FOR,
        RETURN,
    };

    TokenType token_type;
    char* value;
};



void lexerAdvance(Lexer* lex);
void lexerSkipWhitespace(Lexer* lex);

char* lexerGetCurrentCharAsString(Lexer* lex);

Lexer* initLexer(char* contents);

Token* initToken(Token::TokenType type, char* value);
Token* lexerAdvanceWithToken(Lexer* lex, Token* tok);
Token* lexerCollectString(Lexer* lex);
Token* lexerCollectId(Lexer* lex);
Token* lexerGetNextToken(Lexer* lex);

#endif
