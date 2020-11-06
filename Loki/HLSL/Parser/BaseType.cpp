#include "BaseType.hpp"
#include <cstdlib>
#include <cctype>

namespace HLSL {

BaseType* parseBaseType(Parser* parser) {
    BaseType* type = new BaseType();
    type->name = parser->currentToken()->value;

    switch(parser->currentToken()->type) {
        case Token::Type::TOKEN_MATRIX:
            type->is_matrix = true;
            parser->readToken(Token::TOKEN_MATRIX);
            if(parser->currentToken()->type == Token::TOKEN_LESS) {
                parser->readToken(Token::TOKEN_LESS);
                BaseType* t = parseBaseType(parser);
                type->type = t->type;
                delete t;
                parser->readToken(Token::TOKEN_COMMA);
                type->rows = atoi(parser->currentToken()->value);
                parser->readToken(Token::TOKEN_COMMA);
                type->rows = atoi(parser->currentToken()->value);
                parser->readToken(Token::TOKEN_GREATER);
            } else {
                type->type = BaseType::BASE_TYPE_FLOAT;
                type->rows = 4;
                type->cols = 4;
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
        case Token::Type::TOKEN_HALF4x4:    
            parser->readToken(Token::Type::TOKEN_HALF4x4);
            type->type = BaseType::BASE_TYPE_HALF4X4;
            break;
        case Token::Type::TOKEN_HALF3x3:    
            parser->readToken(Token::Type::TOKEN_HALF3x3);
            type->type = BaseType::BASE_TYPE_HALF3x3;
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
        case Token::Type::TOKEN_INT3X3:    
            parser->readToken(Token::Type::TOKEN_INT3X3);
            type->type = BaseType::BASE_TYPE_INT3X3;
            break;
        case Token::Type::TOKEN_INT4X4:    
            parser->readToken(Token::Type::TOKEN_INT4X4);
            type->type = BaseType::BASE_TYPE_INT4X4;
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
        case Token::Type::TOKEN_UINT3X3:    
            parser->readToken(Token::Type::TOKEN_UINT3X3);
            type->type = BaseType::BASE_TYPE_UINT3X3;
            break;
        case Token::Type::TOKEN_UINT4X4:    
            parser->readToken(Token::Type::TOKEN_UINT4X4);
            type->type = BaseType::BASE_TYPE_UINT4X4;
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
        case Token::Type::TOKEN_FLOAT4x4:    
            parser->readToken(Token::Type::TOKEN_FLOAT4x4);
            type->type = BaseType::BASE_TYPE_FLOAT4x4;
            break;
        case Token::Type::TOKEN_FLOAT3x3:    
            parser->readToken(Token::Type::TOKEN_FLOAT3x3);
            type->type = BaseType::BASE_TYPE_FLOAT3x3;
            break;
        case Token::Type::TOKEN_BOOL:    
            parser->readToken(Token::Type::TOKEN_BOOL);
            type->type = BaseType::BASE_TYPE_BOOL;
            break;
        case Token::Type::TOKEN_STRING:    
            parser->readToken(Token::Type::TOKEN_STRING);
            type->type = BaseType::BASE_TYPE_STRING;
            break;
        default:
            parser->readToken(Token::Type::TOKEN_IDENTIFIER);
            type->type = BaseType::BASE_TYPE_USER_DEFINED;
            break;
    }

    return type;
}

}

