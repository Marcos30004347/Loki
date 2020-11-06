#include "Lexer.hpp"
#include "Lib/String.hpp"

namespace HLSL {

Lexer::Lexer(const char* source) {
    this->source = source;
    this->head = 0;
    this->line = 0;
    this->character = source[this->head];
    this->tokens = std::vector<Token*>(0);

    unsigned int eof = strlen(source);

    while(this->character != '\0' || this->head < eof) {
        this->skipWhiteSpaces();
        this->skipComments();

    
        if(isdigit(this->character)) this->collectNumberLiteral();
        if(isalnum(this->character) || this->character == '_') this->collectIdentifier();


        if(this->character == '-') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '-') {
                this->tokens.push_back(new Token(Token::TOKEN_MINUS_MINUS, "--", this->line));
            } else 
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_MINUS_EQUAL, "-=", this->line));
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_MINUS, "-", this->line));
            }
            this->advance();
        } else 
        if(this->character == '+') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '+') {
                this->tokens.push_back(new Token(Token::TOKEN_PLUS_PLUS, "++", this->line));
            } else 
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_PLUS_EQUAL, "+=", this->line));
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_PLUS, "+", this->line));
            }
            this->advance();
        } else 
        if(this->character == '=') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_EQUAL_EQUAL, "==", this->line));
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_EQUAL, "=", this->line));
            }
            this->advance();
        } else 
        if(this->character == '.') {
            this->tokens.push_back(new Token(Token::TOKEN_POINT, ".", this->line));
            this->advance();
        } else
        if(this->character == ',') {
            this->tokens.push_back(new Token(Token::TOKEN_COMMA, ",", this->line));
            this->advance();
        } else 
        if(this->character == '(') {
            this->tokens.push_back(new Token(Token::TOKEN_OPEN_PARENTESIS, "(", this->line));
            this->advance();
        } else 
        if(this->character == ')') {
            this->tokens.push_back(new Token(Token::TOKEN_CLOSE_PARENTESIS, ")", this->line));
            this->advance();
        } else 
        if(this->character == '{') {
            this->tokens.push_back(new Token(Token::TOKEN_OPEN_CURLY_BRACKETS, "{", this->line));
            this->advance();
        } else 
        if(this->character == '}') {
            this->tokens.push_back(new Token(Token::TOKEN_CLOSE_CURLY_BRACKETS, "}", this->line));
            this->advance();
        } else 
        if(this->character == '[') {
            this->tokens.push_back(new Token(Token::TOKEN_OPEN_SQUARE_BRACKETS, "[", this->line));
            this->advance();
        } else 
        if(this->character == ']') {
            this->tokens.push_back(new Token(Token::TOKEN_CLOSE_SQUARE_BRACKETS, "]", this->line));
            this->advance();
        } else 
        if(this->character == ':') {
            this->tokens.push_back(new Token(Token::TOKEN_TWO_POINTS, ":", this->line));
            this->advance();
        } else 
        if(this->character == ';') {
            this->tokens.push_back(new Token(Token::TOKEN_SEMICOLON, ";", this->line));
            this->advance();
        } else 
        if(this->character == '>') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '=', this->line) {
                this->tokens.push_back(new Token(Token::TOKEN_GREATER_OR_EQUAL, ">=", this->line));
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_GREATER, ">", this->line));
            }
            this->advance();
        } else 
        if(this->character == '<') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_LESS_OR_EQUAL, "<=", this->line));
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_LESS, "<", this->line));
            }
            this->advance();
        }
    }
}

void Lexer::collectNumberLiteral() {
    char* value = (char*)calloc(1, sizeof(char));
    value[0] = '\0';

    while(isdigit(this->character)) {
        value = (char*)realloc(value, (strlen(value) + 1)*sizeof(char));
        value[strlen(value)] = this->character;
        this->advance();
    }

    if(this->character == '.') {
        // Float literal
        value = (char*)realloc(value, (strlen(value) + 1)*sizeof(char));
        value[strlen(value)] = this->character;
        this->advance();

        while(isdigit(this->character)) {
            value = (char*)realloc(value, (strlen(value) + 1)*sizeof(char));
            value[strlen(value)] = this->character;
            this->advance();
        }
        if(this->character == 'f') {
            // 10.0f sintax
            this->advance();
        }
    
        this->tokens.push_back(new Token(Token::TOKEN_FLOAT_LITERAL, value, this->line));
    } else {
        if(this->character == 'f') {
            // 10.0f sintax
            this->advance();
            this->tokens.push_back(new Token(Token::TOKEN_FLOAT_LITERAL, value, this->line));
        }
    
        this->tokens.push_back(new Token(Token::TOKEN_INT_LITERAL, value, this->line));
    }
}

void Lexer::collectIdentifier() {
    char* value = (char*)calloc(1, sizeof(char));
    value[0] = '\0';

    while(isalnum(this->character) || isdigit(this->character) || this->character == '_') {
        value = (char*)realloc(value, (strlen(value) + 1)*sizeof(char));
        value[strlen(value)] = this->character;
        this->advance();
    }

    // Reserved keywords
    if(strcmp(value, "register") == 0) return this->tokens.push_back(new Token(Token::TOKEN_REGISTER, value, this->line));
    if(strcmp(value, "static") == 0) return this->tokens.push_back(new Token(Token::TOKEN_STATIC, value, this->line));
    if(strcmp(value, "extern") == 0) return this->tokens.push_back(new Token(Token::TOKEN_EXTERN, value, this->line));
    if(strcmp(value, "cbuffer") == 0) return this->tokens.push_back(new Token(Token::TOKEN_CBUFFER, value, this->line));
    if(strcmp(value, "tbuffer") == 0) return this->tokens.push_back(new Token(Token::TOKEN_TBUFFER, value, this->line));
    if(strcmp(value, "in") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IN, value, this->line));
    if(strcmp(value, "inout") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INOUT, value, this->line));
    if(strcmp(value, "false") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FALSE, value, this->line));
    if(strcmp(value, "true") == 0) return this->tokens.push_back(new Token(Token::TOKEN_TRUE, value, this->line));
    if(strcmp(value, "if") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IF, value, this->line));
    if(strcmp(value, "while") == 0) return this->tokens.push_back(new Token(Token::TOKEN_WHILE, value, this->line));
    if(strcmp(value, "do") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DO, value, this->line));
    if(strcmp(value, "break") == 0) return this->tokens.push_back(new Token(Token::TOKEN_BREAK, value, this->line));
    if(strcmp(value, "for") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FOR, value, this->line));
    if(strcmp(value, "continue") == 0) return this->tokens.push_back(new Token(Token::TOKEN_CONTINUE, value, this->line));
    if(strcmp(value, "discard") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DISCARD, value, this->line));
    if(strcmp(value, "struct") == 0) return this->tokens.push_back(new Token(Token::TOKEN_STRUCT, value, this->line));
    if(strcmp(value, "return") == 0) return this->tokens.push_back(new Token(Token::TOKEN_RETURN, value, this->line));

    // STORAGE_CLASS
    if(strcmp(value, "uniform") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UNIFORM, value, this->line));
    if(strcmp(value, "extern") == 0) return this->tokens.push_back(new Token(Token::TOKEN_EXTERN, value, this->line));
    if(strcmp(value, "nointerpolation") == 0) return this->tokens.push_back(new Token(Token::TOKEN_NOINTERPOLATION, value, this->line));
    if(strcmp(value, "precise") == 0) return this->tokens.push_back(new Token(Token::TOKEN_PRECISE, value, this->line));
    if(strcmp(value, "shared") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SHARED, value, this->line));
    if(strcmp(value, "groupshared") == 0) return this->tokens.push_back(new Token(Token::TOKEN_GROUPSHARED, value, this->line));
    if(strcmp(value, "volatile") == 0) return this->tokens.push_back(new Token(Token::TOKEN_VOLATILE, value, this->line));
    if(strcmp(value, "static") == 0) return this->tokens.push_back(new Token(Token::TOKEN_STATIC, value, this->line));

    // TYPES
    if(strcmp(value, "string") == 0) return this->tokens.push_back(new Token(Token::TOKEN_STRING, value, this->line));
    if(strcmp(value, "void") == 0) return this->tokens.push_back(new Token(Token::TOKEN_VOID, value, this->line));
    if(strcmp(value, "float1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT, value, this->line));
    if(strcmp(value, "float") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT, value, this->line));
    if(strcmp(value, "float") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT, value, this->line));
    if(strcmp(value, "float2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT2, value, this->line));
    if(strcmp(value, "float3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT3, value, this->line));
    if(strcmp(value, "float4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT4, value, this->line));
    if(strcmp(value, "float3x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT3x3, value, this->line));
    if(strcmp(value, "float4x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT4x4, value, this->line));
    if(strcmp(value, "half1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF, value, this->line));
    if(strcmp(value, "half") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF, value, this->line));
    if(strcmp(value, "half2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF2, value, this->line));
    if(strcmp(value, "half3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF3, value, this->line));
    if(strcmp(value, "half4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF4, value, this->line));
    if(strcmp(value, "half3x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF3x3, value, this->line));
    if(strcmp(value, "half4x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF4x4, value, this->line));
    if(strcmp(value, "bool") == 0) return this->tokens.push_back(new Token(Token::TOKEN_BOOL, value, this->line));
    if(strcmp(value, "bool1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_BOOL, value, this->line));
    if(strcmp(value, "int") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT, value, this->line));
    if(strcmp(value, "int1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT, value, this->line));
    if(strcmp(value, "int2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT2, value, this->line));
    if(strcmp(value, "int3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT3, value, this->line));
    if(strcmp(value, "int4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT4, value, this->line));
    if(strcmp(value, "int3x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT3X3, value, this->line));
    if(strcmp(value, "int4x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT4X4, value, this->line));
    if(strcmp(value, "uint1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT, value, this->line));
    if(strcmp(value, "uint") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT, value, this->line));
    if(strcmp(value, "uint2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT2, value, this->line));
    if(strcmp(value, "uint3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT3, value, this->line));
    if(strcmp(value, "uint4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT4, value, this->line));
    if(strcmp(value, "uint3x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT3X3, value, this->line));
    if(strcmp(value, "uint4x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT4X4, value, this->line));
    if(strcmp(value, "texture") == 0) return this->tokens.push_back(new Token(Token::TOKEN_TEXTURE, value, this->line));
    if(strcmp(value, "sampler2d") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLER2D, value, this->line));
    if(strcmp(value, "samplerCUBE") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLERCUBE, value, this->line));


    // Type modifier
    if(strcmp(value, "row_major") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ROW_MAJOR, value, this->line));
    if(strcmp(value, "column_major") == 0) return this->tokens.push_back(new Token(Token::TOKEN_COLUMN_MAJORM, value, this->line));

    return this->tokens.push_back(new Token(Token::TOKEN_IDENTIFIER, value, this->line));
}

void Lexer::collectStringLiteral() {
    if(this->character == '"') {
        this->advance();
        char* value = (char*)calloc(1, sizeof(char));
        value[0] = '\0';

        while(this->character != '"') {
            value = (char*)realloc(value, (strlen(value) + 1)*sizeof(char));
            value[strlen(value)] = this->character;
            this->advance();
        }
        return this->tokens.push_back(new Token(Token::TOKEN_STRING_LITERAL, value, this->line));
    }

}


void Lexer::skipWhiteSpaces() {
    while(this->character == ' ' || this->character == 10) {
        if(this->character == 10) this->line++;
    
        this->advance();
    }
}

void Lexer::advance() {
    this->head = this->head + 1;
    this->character = this->source[this->head];
}

void Lexer::skipComments() {
    if(this->character == '/') {

        this->advance();

        if(this->character == '/') {
            // Single line comment
            while(this->character != 10) {
                this->advance();
            }
            if(this->character == 10) {
                this->line ++;
            }

            this->advance();
    
        } else if(this->character == '*') {
            // Multi line comment
            while(this->character != '*' && this->source[this->head+1] != '/') {
                this->advance();
                if(this->character == 10) {
                    this->line ++;
                }
            }
        }
    }
}

unsigned int Lexer::getTokensCount() {
    return this->tokens.size();
}

Token* Lexer::getToken(unsigned int index) {
    return this->tokens[index];
}

}