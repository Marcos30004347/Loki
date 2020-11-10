#include "Lexer.hpp"
#include "Lib/String.hpp"

#include <cstdio>

namespace GLSL {

Lexer::Lexer(const char* source) {
    printf("Lexing...\n");
    this->source = source;
    this->head = 0;
    this->line = 1;
    this->character = source[this->head];
    this->tokens = std::vector<Token*>(0);

    unsigned int eof = strlen(source);

    this->source_size = eof;

    while(this->character != '\0' || this->head < eof) {
        while(this->skipWhiteSpaces() || this->skipComments()) {}

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
    if(strcmp(value, "string") == 0) return this->tokens.push_back(new Token(Token::TOKEN_STRING, value, this->line));
    if(strcmp(value, "attribute") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ATTRIBUTE, value, this->line));
    if(strcmp(value, "const") == 0) return this->tokens.push_back(new Token(Token::TOKEN_CONST, value, this->line));
    if(strcmp(value, "uniform") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UNIFORM, value, this->line));
    if(strcmp(value, "varying") == 0) return this->tokens.push_back(new Token(Token::TOKEN_VARYING, value, this->line));
    if(strcmp(value, "buffer") == 0) return this->tokens.push_back(new Token(Token::TOKEN_BUFFER, value, this->line));
    if(strcmp(value, "shared") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SHARED, value, this->line));
    if(strcmp(value, "coherent") == 0) return this->tokens.push_back(new Token(Token::TOKEN_COHERENT, value, this->line));
    if(strcmp(value, "volatile") == 0) return this->tokens.push_back(new Token(Token::TOKEN_VOLATILE, value, this->line));
    if(strcmp(value, "restrict") == 0) return this->tokens.push_back(new Token(Token::TOKEN_RESTRICT, value, this->line));
    if(strcmp(value, "readonly") == 0) return this->tokens.push_back(new Token(Token::TOKEN_READONLY, value, this->line));
    if(strcmp(value, "writeonly") == 0) return this->tokens.push_back(new Token(Token::TOKEN_WRITEONLY, value, this->line));
    if(strcmp(value, "atomic_uint") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ATOMIC_UINT, value, this->line));
    if(strcmp(value, "layout") == 0) return this->tokens.push_back(new Token(Token::TOKEN_LAYOUT, value, this->line));
    if(strcmp(value, "centroid") == 0) return this->tokens.push_back(new Token(Token::TOKEN_CENTROID, value, this->line));
    if(strcmp(value, "flat") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLAT, value, this->line));
    if(strcmp(value, "smooth") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SMOOTH, value, this->line));
    if(strcmp(value, "noperspective") == 0) return this->tokens.push_back(new Token(Token::TOKEN_NOPERSPECTIVE, value, this->line));
    if(strcmp(value, "patch") == 0) return this->tokens.push_back(new Token(Token::TOKEN_PATCH, value, this->line));
    if(strcmp(value, "sample") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLE, value, this->line));
    if(strcmp(value, "break") == 0) return this->tokens.push_back(new Token(Token::TOKEN_BREAK, value, this->line));
    if(strcmp(value, "continue") == 0) return this->tokens.push_back(new Token(Token::TOKEN_CONTINUE, value, this->line));
    if(strcmp(value, "do") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DO, value, this->line));
    if(strcmp(value, "for") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FOR, value, this->line));
    if(strcmp(value, "while") == 0) return this->tokens.push_back(new Token(Token::TOKEN_WHILE, value, this->line));
    if(strcmp(value, "switch") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SWITCH, value, this->line));
    if(strcmp(value, "case") == 0) return this->tokens.push_back(new Token(Token::TOKEN_CASE, value, this->line));
    if(strcmp(value, "default") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DEFAULT, value, this->line));
    if(strcmp(value, "if") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IF, value, this->line));
    if(strcmp(value, "else") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ELSE, value, this->line));
    if(strcmp(value, "subroutin") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SUBROUTINE, value, this->line));
    if(strcmp(value, "in") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IN, value, this->line));
    if(strcmp(value, "out") == 0) return this->tokens.push_back(new Token(Token::TOKEN_OUT, value, this->line));
    if(strcmp(value, "inout") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INOUT, value, this->line));
    if(strcmp(value, "float") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FLOAT, value, this->line));
    if(strcmp(value, "double") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DOUBLE, value, this->line));
    if(strcmp(value, "int") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INT, value, this->line));
    if(strcmp(value, "void") == 0) return this->tokens.push_back(new Token(Token::TOKEN_VOID, value, this->line));
    if(strcmp(value, "bool") == 0) return this->tokens.push_back(new Token(Token::TOKEN_BOOL, value, this->line));
    if(strcmp(value, "true") == 0) return this->tokens.push_back(new Token(Token::TOKEN_TRUE, value, this->line));
    if(strcmp(value, "false") == 0) return this->tokens.push_back(new Token(Token::TOKEN_FALSE, value, this->line));
    if(strcmp(value, "invariant") == 0) return this->tokens.push_back(new Token(Token::TOKEN_INVARIANT, value, this->line));
    if(strcmp(value, "precise") == 0) return this->tokens.push_back(new Token(Token::TOKEN_PRECISE, value, this->line));
    if(strcmp(value, "discard") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DISCARD, value, this->line));
    if(strcmp(value, "return") == 0) return this->tokens.push_back(new Token(Token::TOKEN_RETURN, value, this->line));
    if(strcmp(value, "mat2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_MAT2, value, this->line));
    if(strcmp(value, "mat3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_MAT3, value, this->line));
    if(strcmp(value, "mat4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_MAT4, value, this->line));
    if(strcmp(value, "dmat2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DMAT2, value, this->line));
    if(strcmp(value, "dmat3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DMAT3, value, this->line));
    if(strcmp(value, "dmat4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DMAT4, value, this->line));
    if(strcmp(value, "mat2x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_MAT2X2, value, this->line));
    if(strcmp(value, "mat2x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_MAT2X3, value, this->line));
    if(strcmp(value, "mat2x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_MAT2X4, value, this->line));
    if(strcmp(value, "dmat2x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DMAT2X2, value, this->line));
    if(strcmp(value, "dmat2x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DMAT2X3, value, this->line));
    if(strcmp(value, "dmat2x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DMAT2X4, value, this->line));
    if(strcmp(value, "mat3x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_MAT3X2, value, this->line));
    if(strcmp(value, "mat3x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_MAT3X3, value, this->line));
    if(strcmp(value, "mat3x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_MAT3X4, value, this->line));
    if(strcmp(value, "dmat3x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DMAT3X2, value, this->line));
    if(strcmp(value, "dmat3x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DMAT3X3, value, this->line));
    if(strcmp(value, "dmat3x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DMAT3X4, value, this->line));
    if(strcmp(value, "mat4x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_MAT4X2, value, this->line));
    if(strcmp(value, "mat4x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_MAT4X3, value, this->line));
    if(strcmp(value, "mat4x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_MAT4X4, value, this->line));
    if(strcmp(value, "dmat4x2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DMAT4X2, value, this->line));
    if(strcmp(value, "dmat4x3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DMAT4X3, value, this->line));
    if(strcmp(value, "dmat4x4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DMAT4X4, value, this->line));
    if(strcmp(value, "vec2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_VEC2, value, this->line));
    if(strcmp(value, "vec3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_VEC3, value, this->line));
    if(strcmp(value, "vec4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_VEC4, value, this->line));
    if(strcmp(value, "ivec2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IVEC2, value, this->line));
    if(strcmp(value, "ivec3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IVEC3, value, this->line));
    if(strcmp(value, "ivec4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IVEC4, value, this->line));
    if(strcmp(value, "bvec2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_BVEC2, value, this->line));
    if(strcmp(value, "bvec3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_BVEC3, value, this->line));
    if(strcmp(value, "bvec4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_BVEC4, value, this->line));
    if(strcmp(value, "dvec2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DVEC2, value, this->line));
    if(strcmp(value, "dvec3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DVEC3, value, this->line));
    if(strcmp(value, "dvec4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_DVEC4, value, this->line));
    if(strcmp(value, "uint") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UINT, value, this->line));
    if(strcmp(value, "uvec2") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UVEC2, value, this->line));
    if(strcmp(value, "uvec3") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UVEC3, value, this->line));
    if(strcmp(value, "uvec4") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UVEC3, value, this->line));
    if(strcmp(value, "lowp") == 0) return this->tokens.push_back(new Token(Token::TOKEN_LOWP, value, this->line));
    if(strcmp(value, "mediump") == 0) return this->tokens.push_back(new Token(Token::TOKEN_MEDIUMP, value, this->line));
    if(strcmp(value, "highp") == 0) return this->tokens.push_back(new Token(Token::TOKEN_HIGHP, value, this->line));
    if(strcmp(value, "precision") == 0) return this->tokens.push_back(new Token(Token::TOKEN_PRECISION, value, this->line));
    if(strcmp(value, "sampler1D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLER1D, value, this->line));
    if(strcmp(value, "sampler2D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLER2D, value, this->line));
    if(strcmp(value, "sampler3D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLER3D, value, this->line));
    if(strcmp(value, "samplerCube") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLERCUBE, value, this->line));
    if(strcmp(value, "sampler1DShadow") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLER1DSHADOW, value, this->line));
    if(strcmp(value, "sampler2DShadow") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLER2DSHADOW, value, this->line));
    if(strcmp(value, "samplerCubeShadow") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLERCUBESHADOW, value, this->line));
    if(strcmp(value, "sampler1DArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLER1DARRAY, value, this->line));
    if(strcmp(value, "sampler2DArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLER2DARRAY, value, this->line));
    if(strcmp(value, "sampler1DArrayShadow") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLER1DARRAYSHADOW, value, this->line));
    if(strcmp(value, "sampler2DArrayShadow") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLER2DARRAYSHADOW, value, this->line));
    if(strcmp(value, "isampler1D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ISAMPLER1D, value, this->line));
    if(strcmp(value, "isampler2D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ISAMPLER2D, value, this->line));
    if(strcmp(value, "isampler3D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ISAMPLER3D, value, this->line));
    if(strcmp(value, "isamplerCube") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ISAMPLERCUBE, value, this->line));
    if(strcmp(value, "isampler1DArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ISAMPLER1DARRAY, value, this->line));
    if(strcmp(value, "isampler2DArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ISAMPLER2DARRAY, value, this->line));
    if(strcmp(value, "usampler1D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_USAMPLER1D, value, this->line));
    if(strcmp(value, "usampler2D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_USAMPLER2D, value, this->line));
    if(strcmp(value, "usampler3D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_USAMPLER3D, value, this->line));
    if(strcmp(value, "usamplerCube") == 0) return this->tokens.push_back(new Token(Token::TOKEN_USAMPLERCUBE, value, this->line));
    if(strcmp(value, "usampler1DArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_USAMPLER1DARRAY, value, this->line));
    if(strcmp(value, "usampler2DArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_USAMPLER2DARRAY, value, this->line));
    if(strcmp(value, "sampler2DRect") == 0) return this->tokens.push_back(new Token(Token::TOKEN_USAMPLER2DRECT, value, this->line));
    if(strcmp(value, "sampler2DRectShadow") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLER2DRECTSHADOW, value, this->line));
    if(strcmp(value, "isampler2DRect") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ISAMPLER2DRECT, value, this->line));
    if(strcmp(value, "usampler2DRect") == 0) return this->tokens.push_back(new Token(Token::TOKEN_USAMPLER2DRECT, value, this->line));
    if(strcmp(value, "samplerBuffer") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLERBUFFER, value, this->line));
    if(strcmp(value, "isamplerBuffer") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ISAMPLERBUFFER, value, this->line));
    if(strcmp(value, "usamplerBuffer") == 0) return this->tokens.push_back(new Token(Token::TOKEN_USAMPLERBUFFER, value, this->line));
    if(strcmp(value, "sampler2DMS") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLER2DMS, value, this->line));
    if(strcmp(value, "isampler2DMS") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ISAMPLER2DMS, value, this->line));
    if(strcmp(value, "usampler2DMS") == 0) return this->tokens.push_back(new Token(Token::TOKEN_USAMPLER2DMS, value, this->line));
    if(strcmp(value, "sampler2DMSArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLER2DMSARRAY, value, this->line));
    if(strcmp(value, "isampler2DMSArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ISAMPLER2DMSARRAY, value, this->line));
    if(strcmp(value, "usampler2DMSArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_USAMPLER2DMSARRAY, value, this->line));
    if(strcmp(value, "samplerCubeArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLERCUBEARRAY, value, this->line));
    if(strcmp(value, "samplerCubeArrayShadow") == 0) return this->tokens.push_back(new Token(Token::TOKEN_SAMPLERCUBEARRAY, value, this->line));
    if(strcmp(value, "isamplerCubeArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ISAMPLERCUBEARRAY, value, this->line));
    if(strcmp(value, "usamplerCubeArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_ISAMPLERCUBEARRAY, value, this->line));
    if(strcmp(value, "image1D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IMAGE1D, value, this->line));
    if(strcmp(value, "iimage1D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IIMAGE1D, value, this->line));
    if(strcmp(value, "uimage1D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UIMAGE1D, value, this->line));
    if(strcmp(value, "image2D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IMAGE2D, value, this->line));
    if(strcmp(value, "iimage2D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IIMAGE2D, value, this->line));
    if(strcmp(value, "uimage2D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UIMAGE2D, value, this->line));
    if(strcmp(value, "image3D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IMAGE3D, value, this->line));
    if(strcmp(value, "iimage3D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IIMAGE3D, value, this->line));
    if(strcmp(value, "uimage3D") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UIMAGE3D, value, this->line));
    if(strcmp(value, "image2DRect") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IMAGE2DRECT, value, this->line));
    if(strcmp(value, "iimage2DRect") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IIMAGE2DRECT, value, this->line));
    if(strcmp(value, "uimage2DRect") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UIMAGE2DRECT, value, this->line));
    if(strcmp(value, "imageCube") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IMAGECUBE, value, this->line));
    if(strcmp(value, "iimageCube") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IIMAGECUBE, value, this->line));
    if(strcmp(value, "uimageCube") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UIMAGECUBE, value, this->line));
    if(strcmp(value, "imageBuffer") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IMAGEBUFFER, value, this->line));
    if(strcmp(value, "iimageBuffer") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IIMAGEBUFFER, value, this->line));
    if(strcmp(value, "uimageBuffer") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UIMAGEBUFFER, value, this->line));
    if(strcmp(value, "image1DArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IMAGE1DARRAY, value, this->line));
    if(strcmp(value, "iimage1DArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IIMAGE1DARRAY, value, this->line));
    if(strcmp(value, "uimage1DArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UIMAGE1DARRAY, value, this->line));
    if(strcmp(value, "image2DArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IMAGE2DARRAY, value, this->line));
    if(strcmp(value, "iimage2DArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IIMAGE2DARRAY, value, this->line));
    if(strcmp(value, "uimage2DArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UIMAGE2DARRAY, value, this->line));
    if(strcmp(value, "imageCubeArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UIMAGECUBEARRAY, value, this->line));
    if(strcmp(value, "iimageCubeArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IIMAGECUBEARRAY, value, this->line));
    if(strcmp(value, "uimageCubeArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UIMAGECUBEARRAY, value, this->line));
    if(strcmp(value, "image2DMS") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IMAGE2DMS, value, this->line));
    if(strcmp(value, "iimage2DMS") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IIMAGE2DMS, value, this->line));
    if(strcmp(value, "uimage2DMS") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UIMAGE2DMS, value, this->line));
    if(strcmp(value, "image2DMSArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IMAGE2DMSARRAY, value, this->line));
    if(strcmp(value, "iimage2DMSArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_IIMAGE2DMSARRAY, value, this->line));
    if(strcmp(value, "uimage2DMSArray") == 0) return this->tokens.push_back(new Token(Token::TOKEN_UIMAGE2DMSARRAY, value, this->line));
    if(strcmp(value, "struct") == 0) return this->tokens.push_back(new Token(Token::TOKEN_STRUCT, value, this->line));

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

unsigned int Lexer::getTokensCount(){
    return this->tokens.size();
}

Token* Lexer::getToken(unsigned int index){
    return this->tokens[index];
}

}