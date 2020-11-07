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
        TOKEN_TYPES_START = TOKEN_FLOAT,
        TOKEN_FLOAT2,
        TOKEN_FLOAT3,
        TOKEN_FLOAT4,
        TOKEN_FLOAT1x1,
        TOKEN_FLOAT2x1,
        TOKEN_FLOAT3x1,
        TOKEN_FLOAT4x1,
        TOKEN_FLOAT1x2,
        TOKEN_FLOAT2x2,
        TOKEN_FLOAT3x2,
        TOKEN_FLOAT4x2,
        TOKEN_FLOAT1x3,
        TOKEN_FLOAT2x3,
        TOKEN_FLOAT3x3,
        TOKEN_FLOAT4x3,
        TOKEN_FLOAT1x4,
        TOKEN_FLOAT2x4,
        TOKEN_FLOAT3x4,
        TOKEN_FLOAT4x4,
    
        TOKEN_HALF,
        TOKEN_HALF2,
        TOKEN_HALF3,
        TOKEN_HALF4,

        TOKEN_HALF1x1,
        TOKEN_HALF1x2,
        TOKEN_HALF1x3,
        TOKEN_HALF1x4,
        TOKEN_HALF2x1,
        TOKEN_HALF2x2,
        TOKEN_HALF2x3,
        TOKEN_HALF2x4,
        TOKEN_HALF3x1,
        TOKEN_HALF3x2,
        TOKEN_HALF3x3,
        TOKEN_HALF3x4,
        TOKEN_HALF4x1,
        TOKEN_HALF4x2,
        TOKEN_HALF4x3,
        TOKEN_HALF4x4,
    
        TOKEN_BOOL,
    
        TOKEN_INT,
        TOKEN_INT2,
        TOKEN_INT3,
        TOKEN_INT4,
        TOKEN_INT1x1,
        TOKEN_INT1x2,
        TOKEN_INT1x3,
        TOKEN_INT1x4,
        TOKEN_INT2x1,
        TOKEN_INT2x2,
        TOKEN_INT2x3,
        TOKEN_INT2x4,
        TOKEN_INT3x1,
        TOKEN_INT3x2,
        TOKEN_INT3x3,
        TOKEN_INT3x4,
        TOKEN_INT4x1,
        TOKEN_INT4x2,
        TOKEN_INT4x3,
        TOKEN_INT4x4,
    
        TOKEN_UINT,
        TOKEN_UINT2,
        TOKEN_UINT3,
        TOKEN_UINT4,
        TOKEN_UINT1x1,
        TOKEN_UINT1x2,
        TOKEN_UINT1x3,
        TOKEN_UINT1x4,
        TOKEN_UINT2x1,
        TOKEN_UINT2x2,
        TOKEN_UINT2x3,
        TOKEN_UINT2x4,
        TOKEN_UINT3x1,
        TOKEN_UINT3x2,
        TOKEN_UINT3x3,
        TOKEN_UINT3x4,
        TOKEN_UINT4x1,
        TOKEN_UINT4x2,
        TOKEN_UINT4x3,
        TOKEN_UINT4x4,
    
        TOKEN_MATRIX,
        TOKEN_VECTOR,
    
        // Texture Objects
        TOKEN_BUFFER,
        TOKEN_TEXTURE1D,
        TOKEN_TEXTURE1D_ARRAY,
        TOKEN_TEXTURE2D,
        TOKEN_TEXTURE2D_ARRAY,
        TOKEN_TEXTURE3D,
        TOKEN_TEXTURECUBE,
        TOKEN_TEXTURECUBE_ARRAY,
        TOKEN_SAMPLER,
        TOKEN_TEXTURE2DMS,
        TOKEN_TEXTURE2DMS_ARRAY,
        TOKEN_TYPES_END = TOKEN_TEXTURE2DMS_ARRAY,
        
        // FLOW CONTROL
        TOKEN_IF,
        TOKEN_ELSE,
        TOKEN_FOR,
        TOKEN_WHILE,
        TOKEN_BREAK,
        TOKEN_DO,
        TOKEN_CASE,
        TOKEN_SWITCH,
        TOKEN_DEFAULT,
        
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
        TOKEN_OUT,
    
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
        TOKEN_EXCLAMATION,
        TOKEN_EQUAL,
        TOKEN_MINUS,
        TOKEN_PLUS,
        TOKEN_SLASH,
        TOKEN_ASTERISK,
        TOKEN_PIPE,
        TOKEN_PIPE_EQUAL,
        TOKEN_PIPE_PIPE,
        TOKEN_AMPERSAND,
        TOKEN_AMPERSAND_EQUAL,
        TOKEN_APERSAND_AMPERSAND,
        TOKEN_PERCENT,
        TOKEN_PERCENT_EQUAL,
        TOKEN_TIL,
        TOKEN_TIL_EQUAL,
        TOKEN_GREATER_GREATER,
        TOKEN_LESS_LESS,
        TOKEN_GREATER_GREATER_EQUAL,
        TOKEN_LESS_LESS_EQUAL,
        TOKEN_HAT,
        TOKEN_HAT_EQUAL,
        TOKEN_INTERROGATION,

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
    
        // STORAGE CLASS
        TOKEN_STATIC,
        TOKEN_EXTERN,
        TOKEN_NOINTERPOLATION,
        TOKEN_PRECISE,
        TOKEN_SHARED,
        TOKEN_GROUPSHARED,
        TOKEN_VOLATILE,
        TOKEN_UNIFORM,
        TOKEN_LINEAR,
        TOKEN_CENTROID,
        TOKEN_SAMPLE,
        TOKEN_INLINE,
    
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