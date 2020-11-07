#include "BaseType.hpp"
#include <cstdlib>
#include <cctype>

namespace HLSL {

void parseTexture(BaseType* type, Parser* parser) {
    switch(parser->currentToken()->type) {
        case Token::Type::TOKEN_BUFFER:    
            parser->readToken(Token::Type::TOKEN_BUFFER);
            type->type = BaseType::BASE_TYPE_BUFFER;
            if(parser->currentToken()->type == Token::TOKEN_GREATER) {
                parser->readToken(Token::TOKEN_GREATER);
                type->texture_sample_type = parseDeclarationBaseType(parser);
                parser->readToken(Token::TOKEN_LESS);
            }
            break;
        case Token::Type::TOKEN_TEXTURE1D:    
            parser->readToken(Token::Type::TOKEN_TEXTURE1D);
            type->type = BaseType::BASE_TYPE_TEXTURE1D;
            if(parser->currentToken()->type == Token::TOKEN_GREATER) {
                parser->readToken(Token::TOKEN_GREATER);
                type->texture_sample_type = parseDeclarationBaseType(parser);
                parser->readToken(Token::TOKEN_LESS);
            }
            break;

        case Token::Type::TOKEN_TEXTURE1D_ARRAY:    
            parser->readToken(Token::Type::TOKEN_TEXTURE1D_ARRAY);
            type->type = BaseType::BASE_TYPE_TEXTURE1D_ARRAY;
            if(parser->currentToken()->type == Token::TOKEN_GREATER) {
                parser->readToken(Token::TOKEN_GREATER);
                type->texture_sample_type = parseDeclarationBaseType(parser);
                parser->readToken(Token::TOKEN_LESS);
            }
            break;

        case Token::Type::TOKEN_TEXTURE2D:    
            parser->readToken(Token::Type::TOKEN_TEXTURE2D);
            type->type = BaseType::BASE_TYPE_TEXTURE2D;
            if(parser->currentToken()->type == Token::TOKEN_GREATER) {
                parser->readToken(Token::TOKEN_GREATER);
                type->texture_sample_type = parseDeclarationBaseType(parser);
                parser->readToken(Token::TOKEN_LESS);
            }
            break;
        case Token::Type::TOKEN_TEXTURE2D_ARRAY:    
            parser->readToken(Token::Type::TOKEN_TEXTURE2D_ARRAY);
            type->type = BaseType::BASE_TYPE_TEXTURE2D_ARRAY;
            if(parser->currentToken()->type == Token::TOKEN_GREATER) {
                parser->readToken(Token::TOKEN_GREATER);
                type->texture_sample_type = parseDeclarationBaseType(parser);
                parser->readToken(Token::TOKEN_LESS);
            }
            break;
        case Token::Type::TOKEN_TEXTURE3D:    
            parser->readToken(Token::Type::TOKEN_TEXTURE3D);
            type->type = BaseType::BASE_TYPE_TEXTURE3D;
            if(parser->currentToken()->type == Token::TOKEN_GREATER) {
                parser->readToken(Token::TOKEN_GREATER);
                type->texture_sample_type = parseDeclarationBaseType(parser);
                parser->readToken(Token::TOKEN_LESS);
            }
            break;
        case Token::Type::TOKEN_TEXTURECUBE:    
            parser->readToken(Token::Type::TOKEN_TEXTURECUBE);
            type->type = BaseType::BASE_TYPE_TEXTURECUBE;
            if(parser->currentToken()->type == Token::TOKEN_GREATER) {
                parser->readToken(Token::TOKEN_GREATER);
                type->texture_sample_type = parseDeclarationBaseType(parser);
                parser->readToken(Token::TOKEN_LESS);
            }
            break;
        case Token::Type::TOKEN_TEXTURECUBE_ARRAY:    
            parser->readToken(Token::Type::TOKEN_TEXTURECUBE_ARRAY);
            type->type = BaseType::BASE_TYPE_TEXTURECUBE_ARRAY;
            if(parser->currentToken()->type == Token::TOKEN_GREATER) {
                parser->readToken(Token::TOKEN_GREATER);
                type->texture_sample_type = parseDeclarationBaseType(parser);
                parser->readToken(Token::TOKEN_LESS);
            }
            break;
        case Token::Type::TOKEN_TEXTURE2DMS:    
            parser->readToken(Token::Type::TOKEN_TEXTURE2DMS);
            type->type = BaseType::BASE_TYPE_TEXTURE2DMS;
            if(parser->currentToken()->type == Token::TOKEN_GREATER) {
                parser->readToken(Token::TOKEN_GREATER);
                type->texture_sample_type = parseDeclarationBaseType(parser);
                parser->readToken(Token::TOKEN_COMMA);
                type->texture_samples = atoi(parser->currentToken()->value);
                parser->readToken(Token::TOKEN_INT_LITERAL);
                parser->readToken(Token::TOKEN_LESS);
            }
            break;
        case Token::Type::TOKEN_TEXTURE2DMS_ARRAY:    
            parser->readToken(Token::Type::TOKEN_TEXTURE2DMS_ARRAY);
            type->type = BaseType::BASE_TYPE_TEXTURE2DMS_ARRAY;
            if(parser->currentToken()->type == Token::TOKEN_GREATER) {
                parser->readToken(Token::TOKEN_GREATER);
                type->texture_sample_type = parseDeclarationBaseType(parser);
                parser->readToken(Token::TOKEN_COMMA);
                type->texture_samples = atoi(parser->currentToken()->value);
                parser->readToken(Token::TOKEN_INT_LITERAL);
                parser->readToken(Token::TOKEN_LESS);
            }
            break;
    }
}

BaseType* parseDeclarationBaseType(Parser* parser) {
    BaseType* type = new BaseType();
    type->name = parser->currentToken()->value;

    switch(parser->currentToken()->type) {
        case Token::Type::TOKEN_MATRIX:
            type->is_matrix = true;
            parser->readToken(Token::TOKEN_MATRIX);
            if(parser->currentToken()->type == Token::TOKEN_LESS) {
                parser->readToken(Token::TOKEN_LESS);
                BaseType* t = parseDeclarationBaseType(parser);
                type->type = t->type;
                delete t;
                parser->readToken(Token::TOKEN_COMMA);
                type->rows = atoi(parser->currentToken()->value);
                parser->readToken(Token::TOKEN_COMMA);
                type->cols = atoi(parser->currentToken()->value);
                parser->readToken(Token::TOKEN_GREATER);
            } else {
                type->type = BaseType::BASE_TYPE_FLOAT;
                type->rows = 4;
                type->cols = 4;
            }
            break;
        case Token::Type::TOKEN_VECTOR:
            type->is_vector = true;
            parser->readToken(Token::TOKEN_VECTOR);
            if(parser->currentToken()->type == Token::TOKEN_LESS) {
                parser->readToken(Token::TOKEN_LESS);
                BaseType* t = parseDeclarationBaseType(parser);
                type->type = t->type;
                delete t;
                parser->readToken(Token::TOKEN_COMMA);
                type->rows = atoi(parser->currentToken()->value);
                type->cols = 1;
                parser->readToken(Token::TOKEN_GREATER);
            } else {
                type->type = BaseType::BASE_TYPE_FLOAT;
                type->rows = 4;
                type->cols = 1;
            }
            break;            
        case Token::Type::TOKEN_VOID:    
            parser->readToken(Token::Type::TOKEN_VOID);
            type->type = BaseType::BASE_TYPE_VOID;
            break;
        case Token::Type::TOKEN_HALF:    
            parser->readToken(Token::Type::TOKEN_HALF);
            type->type = BaseType::BASE_TYPE_HALF;
            break;
        case Token::Type::TOKEN_HALF2:    
            parser->readToken(Token::Type::TOKEN_HALF2);
            type->type = BaseType::BASE_TYPE_HALF2;
            break;
        case Token::Type::TOKEN_HALF3:    
            parser->readToken(Token::Type::TOKEN_HALF3);
            type->type = BaseType::BASE_TYPE_HALF3;
            break;
        case Token::Type::TOKEN_HALF4:    
            parser->readToken(Token::Type::TOKEN_HALF4);
            type->type = BaseType::BASE_TYPE_HALF4;
            break;
        case Token::Type::TOKEN_INT:    
            parser->readToken(Token::Type::TOKEN_INT);
            type->type = BaseType::BASE_TYPE_INT;
            break;
        case Token::Type::TOKEN_INT2:    
            parser->readToken(Token::Type::TOKEN_INT2);
            type->type = BaseType::BASE_TYPE_INT2;
            break;
        case Token::Type::TOKEN_INT3:    
            parser->readToken(Token::Type::TOKEN_INT3);
            type->type = BaseType::BASE_TYPE_INT3;
            break;
        case Token::Type::TOKEN_INT4:    
            parser->readToken(Token::Type::TOKEN_INT4);
            type->type = BaseType::BASE_TYPE_INT4;
            break;

    
        case Token::Type::TOKEN_INT1x1:    
            parser->readToken(Token::Type::TOKEN_INT1x1);
            type->type = BaseType::BASE_TYPE_INT1X1;
            break;
        case Token::Type::TOKEN_INT1x2:    
            parser->readToken(Token::Type::TOKEN_INT1x2);
            type->type = BaseType::BASE_TYPE_INT1X2;
            break;
        case Token::Type::TOKEN_INT1x3:    
            parser->readToken(Token::Type::TOKEN_INT1x3);
            type->type = BaseType::BASE_TYPE_INT1X3;
            break;
        case Token::Type::TOKEN_INT1x4:    
            parser->readToken(Token::Type::TOKEN_INT1x4);
            type->type = BaseType::BASE_TYPE_INT1X4;
            break;
        case Token::Type::TOKEN_INT2x1:    
            parser->readToken(Token::Type::TOKEN_INT2x1);
            type->type = BaseType::BASE_TYPE_INT2X1;
            break;
        case Token::Type::TOKEN_INT2x2:    
            parser->readToken(Token::Type::TOKEN_INT2x2);
            type->type = BaseType::BASE_TYPE_INT2X2;
            break;
        case Token::Type::TOKEN_INT2x3:    
            parser->readToken(Token::Type::TOKEN_INT2x3);
            type->type = BaseType::BASE_TYPE_INT2X3;
            break;
        case Token::Type::TOKEN_INT2x4:    
            parser->readToken(Token::Type::TOKEN_INT2x4);
            type->type = BaseType::BASE_TYPE_INT2X4;
            break;
        case Token::Type::TOKEN_INT3x1:    
            parser->readToken(Token::Type::TOKEN_INT3x1);
            type->type = BaseType::BASE_TYPE_INT3X1;
            break;
        case Token::Type::TOKEN_INT3x2:    
            parser->readToken(Token::Type::TOKEN_INT3x2);
            type->type = BaseType::BASE_TYPE_INT3X2;
            break;
        case Token::Type::TOKEN_INT3x3:    
            parser->readToken(Token::Type::TOKEN_INT3x3);
            type->type = BaseType::BASE_TYPE_INT3X3;
            break;
        case Token::Type::TOKEN_INT3x4:    
            parser->readToken(Token::Type::TOKEN_INT3x4);
            type->type = BaseType::BASE_TYPE_INT3X4;
            break;
        case Token::Type::TOKEN_INT4x1:    
            parser->readToken(Token::Type::TOKEN_INT4x1);
            type->type = BaseType::BASE_TYPE_INT4X1;
            break;
        case Token::Type::TOKEN_INT4x2:    
            parser->readToken(Token::Type::TOKEN_INT4x2);
            type->type = BaseType::BASE_TYPE_INT4X2;
            break;
        case Token::Type::TOKEN_INT4x3:    
            parser->readToken(Token::Type::TOKEN_INT4x3);
            type->type = BaseType::BASE_TYPE_INT4X3;
            break;
        case Token::Type::TOKEN_INT4x4:    
            parser->readToken(Token::Type::TOKEN_INT4x4);
            type->type = BaseType::BASE_TYPE_INT4X4;
            break;


        case Token::Type::TOKEN_UINT1x1:    
            parser->readToken(Token::Type::TOKEN_UINT1x1);
            type->type = BaseType::BASE_TYPE_UINT1X1;
            break;
        case Token::Type::TOKEN_UINT1x2:    
            parser->readToken(Token::Type::TOKEN_UINT1x2);
            type->type = BaseType::BASE_TYPE_UINT1X2;
            break;
        case Token::Type::TOKEN_UINT1x3:    
            parser->readToken(Token::Type::TOKEN_UINT1x3);
            type->type = BaseType::BASE_TYPE_UINT1X3;
            break;
        case Token::Type::TOKEN_UINT1x4:    
            parser->readToken(Token::Type::TOKEN_UINT1x4);
            type->type = BaseType::BASE_TYPE_UINT1X4;
            break;
        case Token::Type::TOKEN_UINT2x1:    
            parser->readToken(Token::Type::TOKEN_UINT2x1);
            type->type = BaseType::BASE_TYPE_UINT2X1;
            break;
        case Token::Type::TOKEN_UINT2x2:    
            parser->readToken(Token::Type::TOKEN_UINT2x2);
            type->type = BaseType::BASE_TYPE_UINT2X2;
            break;
        case Token::Type::TOKEN_UINT2x3:    
            parser->readToken(Token::Type::TOKEN_UINT2x3);
            type->type = BaseType::BASE_TYPE_UINT2X3;
            break;
        case Token::Type::TOKEN_UINT2x4:    
            parser->readToken(Token::Type::TOKEN_UINT2x4);
            type->type = BaseType::BASE_TYPE_UINT2X4;
            break;
        case Token::Type::TOKEN_UINT3x1:    
            parser->readToken(Token::Type::TOKEN_UINT3x1);
            type->type = BaseType::BASE_TYPE_UINT3X1;
            break;
        case Token::Type::TOKEN_UINT3x2:    
            parser->readToken(Token::Type::TOKEN_UINT3x2);
            type->type = BaseType::BASE_TYPE_UINT3X2;
            break;
        case Token::Type::TOKEN_UINT3x3:    
            parser->readToken(Token::Type::TOKEN_UINT3x3);
            type->type = BaseType::BASE_TYPE_UINT3X3;
            break;
        case Token::Type::TOKEN_UINT3x4:    
            parser->readToken(Token::Type::TOKEN_UINT3x4);
            type->type = BaseType::BASE_TYPE_UINT3X4;
            break;
        case Token::Type::TOKEN_UINT4x1:    
            parser->readToken(Token::Type::TOKEN_UINT4x1);
            type->type = BaseType::BASE_TYPE_UINT4X1;
            break;
        case Token::Type::TOKEN_UINT4x2:    
            parser->readToken(Token::Type::TOKEN_UINT4x2);
            type->type = BaseType::BASE_TYPE_UINT4X2;
            break;
        case Token::Type::TOKEN_UINT4x3:    
            parser->readToken(Token::Type::TOKEN_UINT4x3);
            type->type = BaseType::BASE_TYPE_UINT4X3;
            break;
        case Token::Type::TOKEN_UINT4x4:    
            parser->readToken(Token::Type::TOKEN_UINT4x4);
            type->type = BaseType::BASE_TYPE_UINT4X4;
            break;


        case Token::Type::TOKEN_HALF1x1:    
            parser->readToken(Token::Type::TOKEN_HALF1x1);
            type->type = BaseType::BASE_TYPE_HALF1X1;
            break;
        case Token::Type::TOKEN_HALF1x2:    
            parser->readToken(Token::Type::TOKEN_HALF1x2);
            type->type = BaseType::BASE_TYPE_HALF1X2;
            break;
        case Token::Type::TOKEN_HALF1x3:    
            parser->readToken(Token::Type::TOKEN_HALF1x3);
            type->type = BaseType::BASE_TYPE_HALF1X3;
            break;
        case Token::Type::TOKEN_HALF1x4:    
            parser->readToken(Token::Type::TOKEN_HALF1x4);
            type->type = BaseType::BASE_TYPE_HALF1X4;
            break;
        case Token::Type::TOKEN_HALF2x1:    
            parser->readToken(Token::Type::TOKEN_HALF2x1);
            type->type = BaseType::BASE_TYPE_HALF2X1;
            break;
        case Token::Type::TOKEN_HALF2x2:    
            parser->readToken(Token::Type::TOKEN_HALF2x2);
            type->type = BaseType::BASE_TYPE_HALF2X2;
            break;
        case Token::Type::TOKEN_HALF2x3:    
            parser->readToken(Token::Type::TOKEN_HALF2x3);
            type->type = BaseType::BASE_TYPE_HALF2X3;
            break;
        case Token::Type::TOKEN_HALF2x4:    
            parser->readToken(Token::Type::TOKEN_HALF2x4);
            type->type = BaseType::BASE_TYPE_HALF2X4;
            break;
        case Token::Type::TOKEN_HALF3x1:    
            parser->readToken(Token::Type::TOKEN_HALF3x1);
            type->type = BaseType::BASE_TYPE_HALF3X1;
            break;
        case Token::Type::TOKEN_HALF3x2:    
            parser->readToken(Token::Type::TOKEN_HALF3x2);
            type->type = BaseType::BASE_TYPE_HALF3X2;
            break;
        case Token::Type::TOKEN_HALF3x3:    
            parser->readToken(Token::Type::TOKEN_HALF3x3);
            type->type = BaseType::BASE_TYPE_HALF3X3;
            break;
        case Token::Type::TOKEN_HALF3x4:    
            parser->readToken(Token::Type::TOKEN_HALF3x4);
            type->type = BaseType::BASE_TYPE_HALF3X4;
            break;
        case Token::Type::TOKEN_HALF4x1:    
            parser->readToken(Token::Type::TOKEN_HALF4x1);
            type->type = BaseType::BASE_TYPE_HALF4X1;
            break;
        case Token::Type::TOKEN_HALF4x2:    
            parser->readToken(Token::Type::TOKEN_HALF4x2);
            type->type = BaseType::BASE_TYPE_HALF4X2;
            break;
        case Token::Type::TOKEN_HALF4x3:    
            parser->readToken(Token::Type::TOKEN_HALF4x3);
            type->type = BaseType::BASE_TYPE_HALF4X3;
            break;
        case Token::Type::TOKEN_HALF4x4:    
            parser->readToken(Token::Type::TOKEN_HALF4x4);
            type->type = BaseType::BASE_TYPE_HALF4X4;
            break;


        case Token::Type::TOKEN_FLOAT1x1:    
            parser->readToken(Token::Type::TOKEN_FLOAT1x1);
            type->type = BaseType::BASE_TYPE_FLOAT1X1;
            break;
        case Token::Type::TOKEN_FLOAT1x2:    
            parser->readToken(Token::Type::TOKEN_FLOAT1x2);
            type->type = BaseType::BASE_TYPE_FLOAT1X2;
            break;
        case Token::Type::TOKEN_FLOAT1x3:    
            parser->readToken(Token::Type::TOKEN_FLOAT1x3);
            type->type = BaseType::BASE_TYPE_FLOAT1X3;
            break;
        case Token::Type::TOKEN_FLOAT1x4:    
            parser->readToken(Token::Type::TOKEN_FLOAT1x4);
            type->type = BaseType::BASE_TYPE_FLOAT1X4;
            break;
        case Token::Type::TOKEN_FLOAT2x1:    
            parser->readToken(Token::Type::TOKEN_FLOAT2x1);
            type->type = BaseType::BASE_TYPE_FLOAT2X1;
            break;
        case Token::Type::TOKEN_FLOAT2x2:    
            parser->readToken(Token::Type::TOKEN_FLOAT2x2);
            type->type = BaseType::BASE_TYPE_FLOAT2X2;
            break;
        case Token::Type::TOKEN_FLOAT2x3:    
            parser->readToken(Token::Type::TOKEN_FLOAT2x3);
            type->type = BaseType::BASE_TYPE_FLOAT2X3;
            break;
        case Token::Type::TOKEN_FLOAT2x4:    
            parser->readToken(Token::Type::TOKEN_FLOAT2x4);
            type->type = BaseType::BASE_TYPE_FLOAT2X4;
            break;
        case Token::Type::TOKEN_FLOAT3x1:    
            parser->readToken(Token::Type::TOKEN_FLOAT3x1);
            type->type = BaseType::BASE_TYPE_FLOAT3X1;
            break;
        case Token::Type::TOKEN_FLOAT3x2:    
            parser->readToken(Token::Type::TOKEN_FLOAT3x2);
            type->type = BaseType::BASE_TYPE_FLOAT3X2;
            break;
        case Token::Type::TOKEN_FLOAT3x3:    
            parser->readToken(Token::Type::TOKEN_FLOAT3x3);
            type->type = BaseType::BASE_TYPE_FLOAT3X3;
            break;
        case Token::Type::TOKEN_FLOAT3x4:    
            parser->readToken(Token::Type::TOKEN_FLOAT3x4);
            type->type = BaseType::BASE_TYPE_FLOAT3X4;
            break;
        case Token::Type::TOKEN_FLOAT4x1:    
            parser->readToken(Token::Type::TOKEN_FLOAT4x1);
            type->type = BaseType::BASE_TYPE_FLOAT4X1;
            break;
        case Token::Type::TOKEN_FLOAT4x2:    
            parser->readToken(Token::Type::TOKEN_FLOAT4x2);
            type->type = BaseType::BASE_TYPE_FLOAT4X2;
            break;
        case Token::Type::TOKEN_FLOAT4x3:    
            parser->readToken(Token::Type::TOKEN_FLOAT4x3);
            type->type = BaseType::BASE_TYPE_FLOAT4X3;
            break;
        case Token::Type::TOKEN_FLOAT4x4:    
            parser->readToken(Token::Type::TOKEN_FLOAT4x4);
            type->type = BaseType::BASE_TYPE_FLOAT4X4;
            break;


        case Token::Type::TOKEN_UINT:    
            parser->readToken(Token::Type::TOKEN_UINT);
            type->type = BaseType::BASE_TYPE_UINT;
            break;
        case Token::Type::TOKEN_UINT2:    
            parser->readToken(Token::Type::TOKEN_UINT2);
            type->type = BaseType::BASE_TYPE_UINT2;
            break;
        case Token::Type::TOKEN_UINT3:    
            parser->readToken(Token::Type::TOKEN_UINT3);
            type->type = BaseType::BASE_TYPE_UINT3;
            break;
        case Token::Type::TOKEN_UINT4:    
            parser->readToken(Token::Type::TOKEN_UINT4);
            type->type = BaseType::BASE_TYPE_UINT4;
            break;

        case Token::Type::TOKEN_FLOAT:    
            parser->readToken(Token::Type::TOKEN_FLOAT);
            type->type = BaseType::BASE_TYPE_FLOAT;
            break;
        case Token::Type::TOKEN_FLOAT2:    
            parser->readToken(Token::Type::TOKEN_FLOAT2);
            type->type = BaseType::BASE_TYPE_FLOAT2;
            break;
        case Token::Type::TOKEN_FLOAT3:    
            parser->readToken(Token::Type::TOKEN_FLOAT3);
            type->type = BaseType::BASE_TYPE_FLOAT3;
            break;
        case Token::Type::TOKEN_FLOAT4:    
            parser->readToken(Token::Type::TOKEN_FLOAT4);
            type->type = BaseType::BASE_TYPE_FLOAT4;
            break;
        case Token::Type::TOKEN_BOOL:    
            parser->readToken(Token::Type::TOKEN_BOOL);
            type->type = BaseType::BASE_TYPE_BOOL;
            break;
        case Token::Type::TOKEN_STRING:    
            parser->readToken(Token::Type::TOKEN_STRING);
            type->type = BaseType::BASE_TYPE_STRING;
            break;


        // Texture Buffer Objects
        case Token::Type::TOKEN_BUFFER:    
        case Token::Type::TOKEN_TEXTURE1D:    
        case Token::Type::TOKEN_TEXTURE1D_ARRAY:    
        case Token::Type::TOKEN_TEXTURE2D:    
        case Token::Type::TOKEN_TEXTURE3D:    
        case Token::Type::TOKEN_TEXTURECUBE:    
        case Token::Type::TOKEN_TEXTURECUBE_ARRAY:    
        case Token::Type::TOKEN_TEXTURE2DMS:    
        case Token::Type::TOKEN_TEXTURE2DMS_ARRAY:  
            parseTexture(type, parser);  
            break;
        default:
            parser->readToken(Token::Type::TOKEN_IDENTIFIER);
            type->type = BaseType::BASE_TYPE_USER_DEFINED;
            break;
    }

    return type;
}

bool isDeclaration(Parser* parser) {
    return parser->currentToken()->type == Token::TOKEN_IDENTIFIER || 
    (parser->currentToken()->type >= Token::TOKEN_TYPES_START
        && parser->currentToken()->type <= Token::TOKEN_TYPES_END);
}

}

