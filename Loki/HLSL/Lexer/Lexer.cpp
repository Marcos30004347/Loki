#include "Lexer.hpp"
#include "Lib/String.hpp"
#include <cstdio>
namespace HLSL {

Lexer::Lexer(const char* source) {
    this->source = source;
    this->head = 0;
    this->line = 1;
    this->character = source[this->head];
    this->tokens = std::vector<Token*>(0);

    unsigned int eof = strlen(source);
    this->source_size = eof;
    while(this->character != '\0' || this->head < eof) {
        while(this->skipWhiteSpaces() || this->skipComments()) {}
    
        if(this->character == '.' && this->head + 1 < eof && isdigit(this->source[this->head + 1])) this->collectNumberLiteral();
        if(isdigit(this->character)) this->collectNumberLiteral();
        if(isalnum(this->character) || this->character == '_') this->collectIdentifier();
        else if(this->character == '?') {
            this->tokens.push_back(new Token(Token::TOKEN_INTERROGATION, "?", this->line));
            this->advance();
        } else
        if(this->character == '~') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_TIL_EQUAL, "~=", this->line));
                this->advance();
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_TIL, "~", this->line));
            }
            this->advance();
        } else
        if(this->character == '%') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_PERCENT_EQUAL, "%=", this->line));
                this->advance();
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_PERCENT, "%", this->line));
            }
            this->advance();
        } else
        if(this->character == '&') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_AMPERSAND_EQUAL, "&=", this->line));
                this->advance();
            } else
            if(this->head + 1 < eof && this->source[this->head + 1] == '&') {
                this->tokens.push_back(new Token(Token::TOKEN_APERSAND_AMPERSAND, "&&", this->line));
                this->advance();
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_AMPERSAND, "&", this->line));
            }
            this->advance();
        } else
        if(this->character == '|') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_PIPE_EQUAL, "|=", this->line));
                this->advance();
            } else
            if(this->head + 1 < eof && this->source[this->head + 1] == '|') {
                this->tokens.push_back(new Token(Token::TOKEN_PIPE_PIPE, "||", this->line));
                this->advance();
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_PIPE, "|", this->line));
            }
            this->advance();
        } else
        if(this->character == '*') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_TIMES_EQUAL, "*=", this->line));
                this->advance();
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_ASTERISK, "*", this->line));
            }
            this->advance();
        } else
        if(this->character == '^') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_HAT_EQUAL, "^=", this->line));
                this->advance();
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_HAT, "^", this->line));
            }
            this->advance();
        } else
        if(this->character == '/') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_DIVIDE_EQUAL, "/=", this->line));
                this->advance();
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_SLASH, "/", this->line));
            }
            this->advance();
        } else
        if(this->character == '!') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_NOT_EQUAL, "!=", this->line));
                this->advance();
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_EXCLAMATION, "!", this->line));
            }
            this->advance();
        } else
        if(this->character == '-') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '-') {
                this->tokens.push_back(new Token(Token::TOKEN_MINUS_MINUS, "--", this->line));
                this->advance();
            } else 
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_MINUS_EQUAL, "-=", this->line));
                this->advance();
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_MINUS, "-", this->line));
            }
            this->advance();
        } else 
        if(this->character == '+') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '+') {
                this->tokens.push_back(new Token(Token::TOKEN_PLUS_PLUS, "++", this->line));
                this->advance();
            } else 
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_PLUS_EQUAL, "+=", this->line));
                this->advance();
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_PLUS, "+", this->line));
            }
            this->advance();
        } else 
        if(this->character == '=') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_EQUAL_EQUAL, "==", this->line));
                this->advance();
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
            if(this->head + 1 < eof && this->source[this->head + 1] == '>') {
                if(this->head + 2 < eof && this->source[this->head + 2] == '=') {
                    this->tokens.push_back(new Token(Token::TOKEN_GREATER_GREATER_EQUAL, ">>=", this->line));
                    this->advance();
                }else {
                    this->tokens.push_back(new Token(Token::TOKEN_GREATER_GREATER, ">>", this->line));
                }
                this->advance();
            } else
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_GREATER_OR_EQUAL, ">=", this->line));
                this->advance();
            } else {
                this->tokens.push_back(new Token(Token::TOKEN_GREATER, ">", this->line));
            }
            this->advance();
        } else 
        if(this->character == '<') {
            if(this->head + 1 < eof && this->source[this->head + 1] == '<') {
                if(this->head + 2 < eof && this->source[this->head + 2] == '=') {
                    this->tokens.push_back(new Token(Token::TOKEN_LESS_LESS_EQUAL, "<<=", this->line));
                    this->advance();
                }else {
                    this->tokens.push_back(new Token(Token::TOKEN_LESS_LESS, "<<", this->line));
                }
                this->advance();
            } else
            if(this->head + 1 < eof && this->source[this->head + 1] == '=') {
                this->tokens.push_back(new Token(Token::TOKEN_LESS_OR_EQUAL, "<=", this->line));
                this->advance();
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
    if(strcmp(value, "else") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ELSE, value, this->line));
    if(strcmp(value, "default") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DEFAULT, value, this->line));
    if(strcmp(value, "const") == 0) return this->tokens.push_back(new Token(Token::TOKEN_CONST, value, this->line));
    if(strcmp(value, "case") == 0) return this->tokens.push_back(new Token(Token::TOKEN_CASE, value, this->line));
    if(strcmp(value, "switch") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SWITCH, value, this->line));
    if(strcmp(value, "register") == 0) return this->tokens.push_back(new Token(Token::TOKEN_REGISTER, value, this->line));
    if(strcmp(value, "static") == 0) return this->tokens.push_back(new Token(Token::TOKEN_STATIC, value, this->line));
    if(strcmp(value, "extern") == 0) return this->tokens.push_back(new Token(Token::TOKEN_EXTERN, value, this->line));
    if(strcmp(value, "cbuffer") == 0) return this->tokens.push_back(new Token(Token::TOKEN_CBUFFER, value, this->line));
    if(strcmp(value, "tbuffer") == 0) return this->tokens.push_back(new Token(Token::TOKEN_TBUFFER, value, this->line));
    if(strcmp(value, "in") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IN, value, this->line));
    if(strcmp(value, "inout") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INOUT, value, this->line));
    if(strcmp(value, "out") == 0) return this->tokens.push_back(new Token(Token::TOKEN_OUT, value, this->line));
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
    if(strcmp(value, "inline") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INLINE, value, this->line));
    if(strcmp(value, "packoffset") == 0) return this->tokens.push_back(new Token(Token::TOKEN_PACKOFFSET, value, this->line));
    if(strcmp(value, "sampler") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLER, value, this->line));
    if(strcmp(value, "Buffer") == 0) return this->tokens.push_back(new Token(Token::TOKEN_BUFFER, value, this->line));
    if(strcmp(value, "Texture1D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_TEXTURE1D, value, this->line));
    if(strcmp(value, "Texture2D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_TEXTURE2D, value, this->line));
    if(strcmp(value, "Texture3D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_TEXTURE3D, value, this->line));
    if(strcmp(value, "TextureCUBE") == 0) return this->tokens.push_back(new Token(Token::TOKEN_TEXTURECUBE, value, this->line));
    if(strcmp(value, "TextureCUBEArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_TEXTURECUBE_ARRAY, value, this->line));
    if(strcmp(value, "Texture1DArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_TEXTURE1D_ARRAY, value, this->line));
    if(strcmp(value, "Texture2DArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_TEXTURE2D_ARRAY, value, this->line));
    if(strcmp(value, "Texture2DMS") == 0) return this->tokens.push_back(new Token(Token::TOKEN_TEXTURE2D_ARRAY, value, this->line));
    if(strcmp(value, "Texture2DMS_ARRAY") == 0) return this->tokens.push_back(new Token(Token::TOKEN_TEXTURE2D_ARRAY, value, this->line));

    // STORAGE_CLASS
    if(strcmp(value, "uniform") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UNIFORM, value, this->line));
    if(strcmp(value, "extern") == 0) return this->tokens.push_back(new Token(Token::TOKEN_EXTERN, value, this->line));
    if(strcmp(value, "nointerpolation") == 0) return this->tokens.push_back(new Token(Token::TOKEN_NOINTERPOLATION, value, this->line));
    if(strcmp(value, "precise") == 0) return this->tokens.push_back(new Token(Token::TOKEN_PRECISE, value, this->line));
    if(strcmp(value, "shared") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SHARED, value, this->line));
    if(strcmp(value, "groupshared") == 0) return this->tokens.push_back(new Token(Token::TOKEN_GROUPSHARED, value, this->line));
    if(strcmp(value, "volatile") == 0) return this->tokens.push_back(new Token(Token::TOKEN_VOLATILE, value, this->line));
    if(strcmp(value, "static") == 0) return this->tokens.push_back(new Token(Token::TOKEN_STATIC, value, this->line));
    if(strcmp(value, "linear") == 0) return this->tokens.push_back(new Token(Token::TOKEN_LINEAR, value, this->line));
    if(strcmp(value, "centroid") == 0) return this->tokens.push_back(new Token(Token::TOKEN_CENTROID, value, this->line));
    if(strcmp(value, "sample") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLE, value, this->line));

    // TYPES
    if(strcmp(value, "string") == 0) return this->tokens.push_back(new Token(Token::TOKEN_STRING, value, this->line));
    if(strcmp(value, "void") == 0) return this->tokens.push_back(new Token(Token::TOKEN_VOID, value, this->line));

    if(strcmp(value, "half1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF, value, this->line));
    if(strcmp(value, "half") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF, value, this->line));
    if(strcmp(value, "half2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF2, value, this->line));
    if(strcmp(value, "half3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF3, value, this->line));
    if(strcmp(value, "half4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF4, value, this->line));
    if(strcmp(value, "half1x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF1x1, value, this->line));
    if(strcmp(value, "half1x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF1x2, value, this->line));
    if(strcmp(value, "half1x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF1x3, value, this->line));
    if(strcmp(value, "half1x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF1x4, value, this->line));
    if(strcmp(value, "half2x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF2x1, value, this->line));
    if(strcmp(value, "half2x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF2x2, value, this->line));
    if(strcmp(value, "half2x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF2x3, value, this->line));
    if(strcmp(value, "half2x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF2x4, value, this->line));
    if(strcmp(value, "half3x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF3x1, value, this->line));
    if(strcmp(value, "half3x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF3x2, value, this->line));
    if(strcmp(value, "half3x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF3x3, value, this->line));
    if(strcmp(value, "half3x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF3x4, value, this->line));
    if(strcmp(value, "half4x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF4x1, value, this->line));
    if(strcmp(value, "half4x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF4x2, value, this->line));
    if(strcmp(value, "half4x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF4x3, value, this->line));
    if(strcmp(value, "half4x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HALF4x4, value, this->line));


    if(strcmp(value, "bool") == 0) return this->tokens.push_back(new Token(Token::TOKEN_BOOL, value, this->line));
    if(strcmp(value, "bool1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_BOOL, value, this->line));
    if(strcmp(value, "int") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT, value, this->line));

    if(strcmp(value, "float1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT, value, this->line));
    if(strcmp(value, "float") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT, value, this->line));
    if(strcmp(value, "float") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT, value, this->line));
    if(strcmp(value, "float2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT2, value, this->line));
    if(strcmp(value, "float3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT3, value, this->line));
    if(strcmp(value, "float4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT4, value, this->line));
    if(strcmp(value, "float1x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT1x1, value, this->line));
    if(strcmp(value, "float1x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT1x2, value, this->line));
    if(strcmp(value, "float1x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT1x3, value, this->line));
    if(strcmp(value, "float1x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT1x4, value, this->line));
    if(strcmp(value, "float2x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT2x1, value, this->line));
    if(strcmp(value, "float2x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT2x2, value, this->line));
    if(strcmp(value, "float2x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT2x3, value, this->line));
    if(strcmp(value, "float2x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT2x4, value, this->line));
    if(strcmp(value, "float3x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT3x1, value, this->line));
    if(strcmp(value, "float3x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT3x2, value, this->line));
    if(strcmp(value, "float3x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT3x3, value, this->line));
    if(strcmp(value, "float3x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT3x4, value, this->line));
    if(strcmp(value, "float4x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT4x1, value, this->line));
    if(strcmp(value, "float4x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT4x2, value, this->line));
    if(strcmp(value, "float4x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT4x3, value, this->line));
    if(strcmp(value, "float4x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT4x4, value, this->line));




    if(strcmp(value, "int1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT, value, this->line));
    if(strcmp(value, "int2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT2, value, this->line));
    if(strcmp(value, "int3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT3, value, this->line));
    if(strcmp(value, "int4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT4, value, this->line));
    if(strcmp(value, "int1x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT1x1, value, this->line));
    if(strcmp(value, "int1x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT1x2, value, this->line));
    if(strcmp(value, "int1x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT1x3, value, this->line));
    if(strcmp(value, "int1x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT1x4, value, this->line));
    if(strcmp(value, "int2x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT2x1, value, this->line));
    if(strcmp(value, "int2x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT2x2, value, this->line));
    if(strcmp(value, "int2x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT2x3, value, this->line));
    if(strcmp(value, "int2x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT2x4, value, this->line));
    if(strcmp(value, "int3x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT3x1, value, this->line));
    if(strcmp(value, "int3x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT3x2, value, this->line));
    if(strcmp(value, "int3x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT3x3, value, this->line));
    if(strcmp(value, "int3x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT3x4, value, this->line));
    if(strcmp(value, "int4x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT4x1, value, this->line));
    if(strcmp(value, "int4x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT4x2, value, this->line));
    if(strcmp(value, "int4x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT4x3, value, this->line));
    if(strcmp(value, "int4x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT4x4, value, this->line));




    if(strcmp(value, "double1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT, value, this->line));
    if(strcmp(value, "double") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT, value, this->line));
    if(strcmp(value, "double") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT, value, this->line));
    if(strcmp(value, "double2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT2, value, this->line));
    if(strcmp(value, "double3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT3, value, this->line));
    if(strcmp(value, "double4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT4, value, this->line));
    if(strcmp(value, "double1x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT1x1, value, this->line));
    if(strcmp(value, "double1x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT1x2, value, this->line));
    if(strcmp(value, "double1x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT1x3, value, this->line));
    if(strcmp(value, "double1x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT1x4, value, this->line));
    if(strcmp(value, "double2x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT2x1, value, this->line));
    if(strcmp(value, "double2x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT2x2, value, this->line));
    if(strcmp(value, "double2x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT2x3, value, this->line));
    if(strcmp(value, "double2x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT2x4, value, this->line));
    if(strcmp(value, "double3x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT3x1, value, this->line));
    if(strcmp(value, "double3x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT3x2, value, this->line));
    if(strcmp(value, "double3x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT3x3, value, this->line));
    if(strcmp(value, "double3x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT3x4, value, this->line));
    if(strcmp(value, "double4x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT4x1, value, this->line));
    if(strcmp(value, "double4x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT4x2, value, this->line));
    if(strcmp(value, "double4x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT4x3, value, this->line));
    if(strcmp(value, "double4x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT4x4, value, this->line));



    if(strcmp(value, "uint1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT, value, this->line));
    if(strcmp(value, "uint") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT, value, this->line));
    if(strcmp(value, "uint2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT2, value, this->line));
    if(strcmp(value, "uint3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT3, value, this->line));
    if(strcmp(value, "uint4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT4, value, this->line));
    if(strcmp(value, "uint1x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT1x1, value, this->line));
    if(strcmp(value, "uint1x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT1x2, value, this->line));
    if(strcmp(value, "uint1x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT1x3, value, this->line));
    if(strcmp(value, "uint1x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT1x4, value, this->line));
    if(strcmp(value, "uint2x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT2x1, value, this->line));
    if(strcmp(value, "uint2x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT2x2, value, this->line));
    if(strcmp(value, "uint2x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT2x3, value, this->line));
    if(strcmp(value, "uint2x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT2x4, value, this->line));
    if(strcmp(value, "uint3x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT3x1, value, this->line));
    if(strcmp(value, "uint3x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT3x2, value, this->line));
    if(strcmp(value, "uint3x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT3x3, value, this->line));
    if(strcmp(value, "uint3x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT3x4, value, this->line));
    if(strcmp(value, "uint4x1") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT4x1, value, this->line));
    if(strcmp(value, "uint4x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT4x2, value, this->line));
    if(strcmp(value, "uint4x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT4x3, value, this->line));
    if(strcmp(value, "uint4x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT4x4, value, this->line));


    if(strcmp(value, "dword") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT, value, this->line));
    if(strcmp(value, "matrix") == 0) return this->tokens.push_back(new Token(Token::TOKEN_MATRIX, value, this->line));
    if(strcmp(value, "vector") == 0) return this->tokens.push_back(new Token(Token::TOKEN_VECTOR, value, this->line));

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


bool Lexer::skipWhiteSpaces() {
    bool result = false;
    while(this->character == ' ' || this->character == 10) {
        if(this->character == 10) this->line++;
        result = true;
        this->advance();
    }
    return result;
}

void Lexer::advance() {
    this->head = this->head + 1;
    this->character = this->source[this->head];
}

bool Lexer::skipComments() {

    bool result = false;
    if(this->character == '/' ) {
        if(this->head < this->source_size - 1 && this->source[this->head + 1] == '/') {
            result = true;
            // Single line comment
            while(this->character != 10) {
                this->advance();
            }
            this->line ++;
            this->advance();

        } else if(this->head < this->source_size - 1 && this->source[this->head + 1] == '*') {
            result = true;
            // Multi line comment
            while(!(this->character == '*' && (this->head < this->source_size - 1 && this->source[this->head + 1] == '/'))) {
                if(this->character == 10) {
                    this->line ++;
                }
                this->advance();
            }
            this->advance();
            this->advance();
        }
    }
    return result;
}

unsigned int Lexer::getTokensCount() {
    return this->tokens.size();
}

Token* Lexer::getToken(unsigned int index) {
    return this->tokens[index];
}

}