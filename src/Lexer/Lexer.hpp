
#ifndef LEXER_H
#define LEXER_H


struct Lexer {
    char* contents;
    unsigned int i;
    char c;
    unsigned int line;
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
        PLUS,
        DIVISION,
        MULTIPLICATION,
        MULTIPLICATION_EQUALS,
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
        STRUCT,
        TWO_POINTS,
        PLUSS_EQUALS,
        MINUS_EQUALS,
        DIVIDE_EQUALS,
        PLUSS_PLUSS,
        MINUS_MINUS,
        PIPE,
        PIPE_EQUALS,
        PIPE_PIPE,
        AMPERSAND,
        AMPERSAND_EQUALS,
        AMPERSAND_AMPERSAND,
        FORWARD_ARROW,
        BACKWARD_ARROW,
        FLOATING,
        EXPORT,
        TRUE,
        FALSE,
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
