#include "Lexer.hpp"

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <stdlib.h>


Lexer* initLexer(char* contents) {
    Lexer* lex = (Lexer*)calloc(1, sizeof(Lexer));
    lex->contents = contents;
    lex->i = 0;
    lex->c = lex->contents[lex->c];
    return lex;
}

Token* initToken(Token::TokenType type, char* value) {
    Token* tok = (Token*)calloc(1, sizeof(Token));
    tok->value = value;
    tok->token_type = type;
    return tok;
}

void lexerAdvance(Lexer* lex) {
    if(lex->c != '\0' && lex->i < strlen(lex->contents)) {
        lex->i +=1;
        lex->c = lex->contents[lex->i];
    }
}

void lexerSkipWhitespace(Lexer* lex) {
    while(lex->c == ' ' || lex->c == 10) {
        lexerAdvance(lex);
    }
}

Token* lexerAdvanceWithToken(Lexer* lex, Token* tok) {
    lexerAdvance(lex);
    return tok;
}

char* lexerGetCurrentCharAsString(Lexer* lex) {
    char* str = (char*)calloc(2, sizeof(char));
    str[0] = lex->c;
    str[1] = '\0';
    return str;
}

Token* lexerCollectString(Lexer* lex) {
    lexerAdvance(lex);
    char* value = (char*)calloc(1, sizeof(char));
    value[0] = '\0';
    while(lex->c != '"') {
        char* s = lexerGetCurrentCharAsString(lex);
        value = (char*)realloc(value, (strlen(value) + strlen(s) + 1)*sizeof(char));
        lexerAdvance(lex);
        strcat(value, s);
    }

    lexerAdvance(lex); // advance because of '"'
    return initToken(Token::TokenType::STRING, value);
}

Token* lexerCollectId(Lexer* lex) {

    char* value = (char*)calloc(1, sizeof(char));
    value[0] = '\0';

    while(isalnum(lex->c)) {
        char* s = lexerGetCurrentCharAsString(lex);
        value = (char*)realloc(value, (strlen(value) + strlen(s) + 1)*sizeof(char));
        strcat(value, s);
        lexerAdvance(lex);
    }


    return initToken(Token::TokenType::IDENTIFIER, value);
}


Token* lexerCollectInt(Lexer* lex) {

    char* value = (char*)calloc(1, sizeof(char));
    value[0] = '\0';

    while(isdigit(lex->c)) {
        char* s = lexerGetCurrentCharAsString(lex);
        value = (char*)realloc(value, (strlen(value) + strlen(s) + 1)*sizeof(char));
        strcat(value, s);
        lexerAdvance(lex);
    }

    return initToken(Token::TokenType::INTEGER, value);
}

Token* lexerGetNextToken(Lexer* lex) {
    unsigned int eof = strlen(lex->contents);

    while(lex->c != '\0' && lex->i < eof) {
    
        if(lex->c == ' ' || lex->c == 10) lexerSkipWhitespace(lex);
    
        if(isdigit(lex->c)) return lexerCollectInt(lex);
        if(isalnum(lex->c)) return lexerCollectId(lex);
        if(lex->c == '"') return lexerCollectString(lex);

        switch (lex->c) {
            case '=':
                if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '=')  
                return lexerAdvanceWithToken(lex, initToken(Token::TokenType::EQUALS_EQUALS, lexerGetCurrentCharAsString(lex)));
                else return lexerAdvanceWithToken(lex, initToken(Token::TokenType::EQUALS, lexerGetCurrentCharAsString(lex)));
            case '(': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::OPEN_PARENTESIS, lexerGetCurrentCharAsString(lex)));
            case '!':
                if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '=')  
                return lexerAdvanceWithToken(lex, initToken(Token::TokenType::DIFFERENT, lexerGetCurrentCharAsString(lex)));
                else return lexerAdvanceWithToken(lex, initToken(Token::TokenType::EXCLAMATION, lexerGetCurrentCharAsString(lex)));
            case ')': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::CLOSE_PARENTESIS, lexerGetCurrentCharAsString(lex)));
            case ';': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::SEMICOLON, lexerGetCurrentCharAsString(lex)));
            case '{': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::OPEN_BRACKET, lexerGetCurrentCharAsString(lex)));
            case '}': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::CLOSE_BRACKET, lexerGetCurrentCharAsString(lex)));
            case ',': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::COMMA, lexerGetCurrentCharAsString(lex)));
            case '.': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::PERIOD, lexerGetCurrentCharAsString(lex)));
            case '*': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::MULTIPLICATION, lexerGetCurrentCharAsString(lex)));
            case '/': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::DIVISION, lexerGetCurrentCharAsString(lex)));
            case '-': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::SUBTRACION, lexerGetCurrentCharAsString(lex)));
            case '+': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::ADDITION, lexerGetCurrentCharAsString(lex)));
            case '>':
                if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '=') 
                return lexerAdvanceWithToken(lex, initToken(Token::TokenType::GREATER_OR_EQUALS, lexerGetCurrentCharAsString(lex)));
                else return lexerAdvanceWithToken(lex, initToken(Token::TokenType::GREATER, lexerGetCurrentCharAsString(lex)));
            case '<':
                if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '=') 
                return lexerAdvanceWithToken(lex, initToken(Token::TokenType::LESS_OR_EQUALS, lexerGetCurrentCharAsString(lex)));
                else return lexerAdvanceWithToken(lex, initToken(Token::TokenType::LESS, lexerGetCurrentCharAsString(lex)));

            default: printf("Unknow token!\n") ;exit(-1);
        }
    }

    char* nullString = new char[1];
    nullString[0] = '\0';
    return initToken(Token::TokenType::TOKEN_EOF, nullString);
}
