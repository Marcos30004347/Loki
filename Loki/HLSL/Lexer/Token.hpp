#ifndef TOKEN_H
#define TOKEN_H

namespace HLSL {

class Token {
public:
    enum Type {
        TOKEN_NONE,
        TOKEN_IDENTIFIER,
        
        //TYPES
        TOKEN_VOID,
        TOKEN_STRING,
        TOKEN_FLOAT,
        TOKEN_FLOAT2,
        TOKEN_FLOAT3,
        TOKEN_FLOAT4,
        TOKEN_FLOAT3x3,
        TOKEN_FLOAT4x4,
        TOKEN_HALF,
        TOKEN_HALF2,
        TOKEN_HALF3,
        TOKEN_HALF4,
        TOKEN_HALF3x3,
        TOKEN_HALF4x4,
        TOKEN_BOOL,
        TOKEN_INT,
        TOKEN_INT2,
        TOKEN_INT3,
        TOKEN_INT4,
        TOKEN_INT3X3,
        TOKEN_INT4X4,
        TOKEN_UINT,
        TOKEN_UINT2,
        TOKEN_UINT3,
        TOKEN_UINT4,
        TOKEN_UINT3X3,
        TOKEN_UINT4X4,
        TOKEN_TEXTURE,
        TOKEN_SAMPLER2D,
        TOKEN_SAMPLERCUBE,

        // FLOW CONTROL
        TOKEN_IF,
        TOKEN_ELSE,
        TOKEN_FOR,
        TOKEN_WHILE,
        TOKEN_BREAK,
        TOKEN_DO,

        TOKEN_TRUE,
        TOKEN_FALSE,
        TOKEN_STRUCT,
        TOKEN_CBUFFER,
        TOKEN_TBUFFER,
        TOKEN_REGISTER,
        TOKEN_RETURN,
        TOKEN_CONTINUE,
        TOKEN_DISCARD,
        TOKEN_IN,
        TOKEN_INOUT,
        TOKEN_TWO_POINTS,
    
        // OPERATORS
        TOKEN_LESS,
        TOKEN_LESS_OR_EQUAL,
        TOKEN_GREATER_OR_EQUAL,
        TOKEN_GREATER,
        TOKEN_EQUAL_EQUAL,
        TOKEN_NOT_EQUAL,
        TOKEN_PLUS_PLUS,
        TOKEN_MINUS_MINUS,
        TOKEN_PLUS_EQUAL,
        TOKEN_MINUS_EQUAL,
        TOKEN_TIMES_EQUAL,
        TOKEN_DIVIDE_EQUAL,
        TOKEN_AND_AND,
        TOKEN_BAR_BAR,
    
        // LITERALS
        TOKEN_FLOAT_LITERAL,
        TOKEN_INT_LITERAL,
        TOKEN_STRING_LITERAL,
    
        // SYMBOLS  
        TOKEN_OPEN_PARENTESIS,
        TOKEN_CLOSE_PARENTESIS,
        TOKEN_OPEN_SQUARE_BRACKETS,
        TOKEN_CLOSE_SQUARE_BRACKETS,
        TOKEN_OPEN_CURLY_BRACKETS,
        TOKEN_CLOSE_CURLY_BRACKETS,
        TOKEN_SEMICOLON,
        TOKEN_COMMA,
        TOKEN_POINT,
        TOKEN_EQUAL,
        TOKEN_MINUS,
        TOKEN_PLUS,
    
        // STORAGE CLASS
        TOKEN_STATIC,
        TOKEN_EXTERN,
        TOKEN_NOINTERPOLATION,
        TOKEN_PRECISE,
        TOKEN_SHARED,
        TOKEN_GROUPSHARED,
        TOKEN_VOLATILE,
        TOKEN_UNIFORM,
        
        // TYPE_MODIFIER
        TOKEN_CONST,
        TOKEN_ROW_MAJOR,
        TOKEN_COLUMN_MAJORM,

        // PACK_OFFSET
        TOKEN_PACKOFFSET,

        TOKEN_EOF,
    };

    Type type;
    char* value;
    unsigned int line;
    Token(Token::Type type, char* value, unsigned int line);
    Token(Token::Type type, const char* value, unsigned int line);
};


}

#endif