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
    lex->line = 0;
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
        if(lex->c == 10) lex->line++;

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

    if(strcmp(value, "for") == 0)       return initToken(Token::TokenType::FOR, value);
    if(strcmp(value, "if") == 0)        return initToken(Token::TokenType::IF, value);
    if(strcmp(value, "else") == 0)      return initToken(Token::TokenType::ELSE, value);
    if(strcmp(value, "do") == 0)        return initToken(Token::TokenType::DO, value);
    if(strcmp(value, "while") == 0)     return initToken(Token::TokenType::WHILE, value);
    if(strcmp(value, "return") == 0)    return initToken(Token::TokenType::RETURN, value);
    if(strcmp(value, "switch") == 0)    return initToken(Token::TokenType::SWITCH, value);
    if(strcmp(value, "break") == 0)     return initToken(Token::TokenType::BREAK, value);
    if(strcmp(value, "default") == 0)   return initToken(Token::TokenType::DEFAULT, value);
    if(strcmp(value, "struct") == 0)    return initToken(Token::TokenType::STRUCT, value);
    if(strcmp(value, "case") == 0)      return initToken(Token::TokenType::CASE, value);
    if(strcmp(value, "export") == 0)    return initToken(Token::TokenType::EXPORT, value);
    if(strcmp(value, "true") == 0)      return initToken(Token::TokenType::TRUE, value);
    if(strcmp(value, "false") == 0)     return initToken(Token::TokenType::FALSE, value);
    if(strcmp(value, "void") == 0)      return initToken(Token::TokenType::VOID, value); 
    if(strcmp(value, "int") == 0)       return initToken(Token::TokenType::INT, value);
    if(strcmp(value, "uint") == 0)      return initToken(Token::TokenType::UINT, value); 
    if(strcmp(value, "float") == 0)     return initToken(Token::TokenType::FLOAT, value);
    if(strcmp(value, "bool") == 0)      return initToken(Token::TokenType::BOOL, value); 
    if(strcmp(value, "vec2") == 0)      return initToken(Token::TokenType::VEC2, value); 
    if(strcmp(value, "vec3") == 0)      return initToken(Token::TokenType::VEC3, value);
    if(strcmp(value, "vec4") == 0)      return initToken(Token::TokenType::VEC4, value);
    if(strcmp(value, "mat2") == 0)      return initToken(Token::TokenType::MAT2, value);
    if(strcmp(value, "mat2x2") == 0)    return initToken(Token::TokenType::MAT2X2, value);
    if(strcmp(value, "mat2x3") == 0)    return initToken(Token::TokenType::MAT2X3, value);
    if(strcmp(value, "mat2x4") == 0)    return initToken(Token::TokenType::MAT2X4, value);
    if(strcmp(value, "mat3") == 0)      return initToken(Token::TokenType::MAT3, value);
    if(strcmp(value, "mat3x2") == 0)    return initToken(Token::TokenType::MAT3X2, value);
    if(strcmp(value, "mat3x3") == 0)    return initToken(Token::TokenType::MAT3X3, value);
    if(strcmp(value, "mat3x4") == 0)    return initToken(Token::TokenType::MAT3X4, value);
    if(strcmp(value, "mat4") == 0)      return initToken(Token::TokenType::MAT4, value);
    if(strcmp(value, "mat4x2") == 0)    return initToken(Token::TokenType::MAT4X2, value);
    if(strcmp(value, "mat4x3") == 0)    return initToken(Token::TokenType::MAT4X3, value);
    if(strcmp(value, "mat4x4") == 0)    return initToken(Token::TokenType::MAT4X4, value);

    return initToken(Token::TokenType::IDENTIFIER, value);
}


Token* lexerCollectInt(Lexer* lex) {

    char* value = (char*)calloc(1, sizeof(char));
    value[0] = '\0';

    if(isdigit(lex->c)) {
        while(isdigit(lex->c)) {
            char* s = lexerGetCurrentCharAsString(lex);
            value = (char*)realloc(value, (strlen(value) + strlen(s) + 1)*sizeof(char));
            strcat(value, s);
            lexerAdvance(lex);
        }
        if(lex->c == '.') {
            char* s = lexerGetCurrentCharAsString(lex);
            value = (char*)realloc(value, (strlen(value) + strlen(s) + 1)*sizeof(char));
            strcat(value, s);
            lexerAdvance(lex);
            while(isdigit(lex->c)) {
                char* s = lexerGetCurrentCharAsString(lex);
                value = (char*)realloc(value, (strlen(value) + strlen(s) + 1)*sizeof(char));
                strcat(value, s);
                lexerAdvance(lex);
            }
            return initToken(Token::TokenType::FLOATING, value);
        }
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
                if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '=')  {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::EQUALS_EQUALS, (char*)"=="));
                }
                else return lexerAdvanceWithToken(lex, initToken(Token::TokenType::EQUALS, lexerGetCurrentCharAsString(lex)));
            case '(': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::OPEN_PARENTESIS, lexerGetCurrentCharAsString(lex)));
            case '!':
                if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '=') {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::DIFFERENT, (char*)"!="));
                }
                else return lexerAdvanceWithToken(lex, initToken(Token::TokenType::EXCLAMATION, lexerGetCurrentCharAsString(lex)));
            case ')': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::CLOSE_PARENTESIS, lexerGetCurrentCharAsString(lex)));
            case ';': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::SEMICOLON, lexerGetCurrentCharAsString(lex)));
            case '{': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::OPEN_BRACKET, lexerGetCurrentCharAsString(lex)));
            case '}': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::CLOSE_BRACKET, lexerGetCurrentCharAsString(lex)));
            case ',': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::COMMA, lexerGetCurrentCharAsString(lex)));
            case '.': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::PERIOD, lexerGetCurrentCharAsString(lex)));
            case '*':
                if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '=') {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::MULTIPLICATION_EQUALS, (char*)"*="));
                } 
                else return lexerAdvanceWithToken(lex, initToken(Token::TokenType::MULTIPLICATION, lexerGetCurrentCharAsString(lex)));
            case '/':
                if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '=') {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::DIVIDE_EQUALS, (char*)"/-"));
                } 
                else return lexerAdvanceWithToken(lex, initToken(Token::TokenType::DIVISION, lexerGetCurrentCharAsString(lex)));
            case '-':
                if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '-') {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::MINUS_MINUS, (char*)"--"));
                } else if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '=') {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::MINUS_EQUALS, (char*)"-="));
                } else if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '>') {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::FORWARD_ARROW, (char*)"->"));
                }
                else return lexerAdvanceWithToken(lex, initToken(Token::TokenType::MINUS, lexerGetCurrentCharAsString(lex)));
            case '+': 
                if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '+') {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::PLUSS_PLUSS, (char*)"++"));
                } else if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '=') {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::PLUSS_EQUALS, (char*)"+="));
                }
                else return lexerAdvanceWithToken(lex, initToken(Token::TokenType::PLUS, lexerGetCurrentCharAsString(lex)));
            case ':': return lexerAdvanceWithToken(lex, initToken(Token::TokenType::TWO_POINTS, lexerGetCurrentCharAsString(lex)));
            case '>':
                if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '=') {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::GREATER_OR_EQUALS, (char*)">="));
                }
                else return lexerAdvanceWithToken(lex, initToken(Token::TokenType::GREATER, lexerGetCurrentCharAsString(lex)));
            case '<':
                if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '=')  {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::LESS_OR_EQUALS, (char*)"<="));
                }else if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '-') {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::BACKWARD_ARROW, (char*)"<-"));
                }
                else return lexerAdvanceWithToken(lex, initToken(Token::TokenType::LESS, lexerGetCurrentCharAsString(lex)));
            case '|':
                if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '=')  {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::PIPE_EQUALS, (char*)"|="));
                } else if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '|')  {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::PIPE_PIPE, (char*)"||"));
                }
                else return lexerAdvanceWithToken(lex, initToken(Token::TokenType::PIPE, lexerGetCurrentCharAsString(lex)));
            case '&':
                if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '=')  {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::AMPERSAND_EQUALS, (char*)"&="));
                } else if(lex->i + 1 != eof && lex->contents[lex->i + 1] == '&')  {
                    lex->i++;
                    lex->i++;
                    return lexerAdvanceWithToken(lex, initToken(Token::TokenType::AMPERSAND_AMPERSAND, (char*)"&&"));
                }
                else return lexerAdvanceWithToken(lex, initToken(Token::TokenType::AMPERSAND, lexerGetCurrentCharAsString(lex)));

            default: printf("Unknow token!\n") ;exit(-1);
        }
    }

    char* nullString = new char[1];
    nullString[0] = '\0';
    return initToken(Token::TokenType::TOKEN_EOF, nullString);
}
