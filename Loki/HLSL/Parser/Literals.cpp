#include "Literals.hpp"
#include "Lib/String.hpp"
#include <stdio.h>
namespace HLSL {


float parseSingleFloat(Parser* parser) {
    float value;
    if(
        parser->currentToken()->type == Token::TOKEN_FLOAT 
    ) {
        parser->readToken(Token::TOKEN_FLOAT);
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        value = atof(parser->currentToken()->value);
        parser->readNumeric();
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    } else {
        value = strToDouble(parser->currentToken()->value, nullptr);
        parser->readNumeric();
    }
    return value;
}

float* parseSingleFloatX(Parser* parser, unsigned int x) {
    float* value = new float[x];

    if(
        parser->currentToken()->type == Token::TOKEN_FLOAT 
        || parser->currentToken()->type == Token::TOKEN_FLOAT2
        || parser->currentToken()->type == Token::TOKEN_FLOAT3
        || parser->currentToken()->type == Token::TOKEN_FLOAT4
        || parser->currentToken()->type == Token::TOKEN_FLOAT3x3
        || parser->currentToken()->type == Token::TOKEN_FLOAT4x4
    ) {
        parser->readToken(parser->currentToken()->type);
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        if(parser->currentToken()->type != Token::TOKEN_CLOSE_PARENTESIS) {
            int i=0;
            value[i] = parseSingleFloat(parser);
            i++;
            while(parser->currentToken()->type == Token::TOKEN_COMMA) {
                i++;
                parser->readToken(Token::TOKEN_COMMA);
                value[i] = parseSingleFloat(parser);
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    } else {
        parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);
        if(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
            int i=0;
            value[i] = parseSingleFloat(parser);
            i++;
            while(parser->currentToken()->type == Token::TOKEN_COMMA) {
                i++;
                parser->readToken(Token::TOKEN_COMMA);
                value[i] = parseSingleFloat(parser);
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);
    }
    return value;
}



int parseSingleInt(Parser* parser) {
    int value;
    if(
        parser->currentToken()->type == Token::TOKEN_INT 
    ) {
        parser->readToken(parser->currentToken()->type);
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        value = atoi(parser->currentToken()->value);
        parser->readNumeric();
        parser->readToken(Token::TOKEN_INT_LITERAL);
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    } else {
        value = atoi(parser->currentToken()->value);
        parser->readToken(Token::TOKEN_INT_LITERAL);
    }

    return value;
}

int parseSingleHalf(Parser* parser) {
    int value;
    if(
        parser->currentToken()->type == Token::TOKEN_HALF 
    ) {
        parser->readToken(parser->currentToken()->type);
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        value = atoi(parser->currentToken()->value);
        parser->readNumeric();
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    } else {
        value = atoi(parser->currentToken()->value);
        parser->readNumeric();
    }

    return value;
}

int* parseSingleHalfX(Parser* parser, unsigned int x) {
    int* value = new int[x];
    if(
        parser->currentToken()->type == Token::TOKEN_HALF 
        || parser->currentToken()->type == Token::TOKEN_HALF2
        || parser->currentToken()->type == Token::TOKEN_HALF3
        || parser->currentToken()->type == Token::TOKEN_HALF4
        || parser->currentToken()->type == Token::TOKEN_HALF3x3
        || parser->currentToken()->type == Token::TOKEN_HALF4x4
    ) {
        parser->readToken(parser->currentToken()->type);
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        if(parser->currentToken()->type != Token::TOKEN_CLOSE_PARENTESIS) {
            int i=0;
            value[i] = parseSingleHalf(parser);
            i++;
            while(parser->currentToken()->type == Token::TOKEN_COMMA) {
                i++;
                parser->readToken(Token::TOKEN_COMMA);
                value[i] = parseSingleHalf(parser);
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    } else {
        parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);
        if(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
            int i=0;
            value[i] = parseSingleHalf(parser);
            i++;
            while(parser->currentToken()->type == Token::TOKEN_COMMA) {
                i++;
                parser->readToken(Token::TOKEN_COMMA);
                value[i] = parseSingleHalf(parser);
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);
    }
    return value;
}


int* parseSingleIntX(Parser* parser, unsigned int x) {
    int* value = new int[x];
    if(
        parser->currentToken()->type == Token::TOKEN_INT 
        || parser->currentToken()->type == Token::TOKEN_INT2
        || parser->currentToken()->type == Token::TOKEN_INT3
        || parser->currentToken()->type == Token::TOKEN_INT4
        || parser->currentToken()->type == Token::TOKEN_INT3X3
        || parser->currentToken()->type == Token::TOKEN_INT4X4
    ) {
        parser->readToken(parser->currentToken()->type);
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        if(parser->currentToken()->type != Token::TOKEN_CLOSE_PARENTESIS) {
            int i=0;
            value[i] = parseSingleInt(parser);
            i++;
            while(parser->currentToken()->type == Token::TOKEN_COMMA) {
                i++;
                parser->readToken(Token::TOKEN_COMMA);
                value[i] = parseSingleInt(parser);
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    } else {
        parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);
        if(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
            int i=0;
            value[i] = parseSingleInt(parser);
            i++;
            while(parser->currentToken()->type == Token::TOKEN_COMMA) {
                i++;
                parser->readToken(Token::TOKEN_COMMA);
                value[i] = parseSingleInt(parser);
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);
    }
    return value;
}

unsigned int parseSingleUInt(Parser* parser) {
    unsigned int value;
    if(
        parser->currentToken()->type == Token::TOKEN_UINT 
    ) {
        parser->readToken(Token::TOKEN_UINT);
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        value = atoi(parser->currentToken()->value);
        parser->readNumeric();
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    } else {
        value = atoi(parser->currentToken()->value);
        parser->readToken(Token::TOKEN_INT_LITERAL);
    }

    return value;
}

unsigned int* parseSingleUIntX(Parser* parser, unsigned int x) {
    unsigned int* value = new unsigned int[x];
    if(
        parser->currentToken()->type == Token::TOKEN_UINT 
        || parser->currentToken()->type == Token::TOKEN_UINT2
        || parser->currentToken()->type == Token::TOKEN_UINT3
        || parser->currentToken()->type == Token::TOKEN_UINT4
        || parser->currentToken()->type == Token::TOKEN_UINT3X3
        || parser->currentToken()->type == Token::TOKEN_UINT4X4
    ) {
        parser->readToken(parser->currentToken()->type);
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        if(parser->currentToken()->type != Token::TOKEN_CLOSE_PARENTESIS) {
            int i=0;
            value[i] = parseSingleInt(parser);
            i++;
            while(parser->currentToken()->type == Token::TOKEN_COMMA) {
                i++;
                parser->readToken(Token::TOKEN_COMMA);
                value[i] = parseSingleInt(parser);
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    } else {
        parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);
        if(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
            int i=0;
            value[i] = parseSingleInt(parser);
            i++;
            while(parser->currentToken()->type == Token::TOKEN_COMMA) {
                i++;
                parser->readToken(Token::TOKEN_COMMA);
                value[i] = parseSingleInt(parser);
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);
    }
    return value;
}

float parseSingleBool(Parser* parser) {
    bool value;
    if(
        parser->currentToken()->type == Token::TOKEN_BOOL 
    ) {
        parser->readToken(Token::TOKEN_BOOL);
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
    
        if(parser->currentToken()->type == Token::TOKEN_TRUE) {
            parser->readToken(Token::TOKEN_TRUE);
            value = true;
        } else 
        if(parser->currentToken()->type == Token::TOKEN_FALSE) {
            parser->readToken(Token::TOKEN_FALSE);
            value = false;
        } else
        if(parser->currentToken()->type == Token::TOKEN_INT_LITERAL) {
            parser->readToken(Token::TOKEN_INT_LITERAL);
            value = atoi(parser->currentToken()->value) > 0;
        }
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    } else {
        if(parser->currentToken()->type == Token::TOKEN_TRUE) {
            parser->readToken(Token::TOKEN_TRUE);
            value = true;
        } else 
        if(parser->currentToken()->type == Token::TOKEN_FALSE) {
            parser->readToken(Token::TOKEN_FALSE);
            value = false;
        } else
        if(parser->currentToken()->type == Token::TOKEN_INT_LITERAL) {
            parser->readToken(Token::TOKEN_INT_LITERAL);
            value = atoi(parser->currentToken()->value) > 0;
        }
    }

    return value;
}

Literal* parseLiteral(Parser* parser, BaseType* type) {
    Token* token = parser->currentToken();
    Literal* literal = new Literal();
    literal->literal_type = type;

    switch(type->type) {
        case BaseType::BASE_TYPE_FLOAT:
        literal->float_value = parseSingleFloat(parser);
        break;
        case BaseType::BASE_TYPE_FLOAT2:
        literal->float2_value = parseSingleFloatX(parser, 2);
        break;
        case BaseType::BASE_TYPE_FLOAT3:
        literal->float3_value = parseSingleFloatX(parser, 3);
        break;
        case BaseType::BASE_TYPE_FLOAT4:
        literal->float4_value = parseSingleFloatX(parser, 4);
        break;
        case BaseType::BASE_TYPE_FLOAT3x3:
        literal->float3x3_value = parseSingleFloatX(parser, 3*3);
        break;
        case BaseType::BASE_TYPE_FLOAT4x4:
        literal->float4x4_value = parseSingleFloatX(parser, 4*4);
        break;
        case BaseType::BASE_TYPE_INT:
        literal->int_value = parseSingleInt(parser);
        break;
        case BaseType::BASE_TYPE_HALF:
        literal->half_value = parseSingleHalf(parser);
        break;
        case BaseType::BASE_TYPE_UINT:
        literal->uint_value = parseSingleUInt(parser);
        break;
        case BaseType::BASE_TYPE_INT2:
        literal->int2_value = parseSingleIntX(parser, 2);
        break;
        case BaseType::BASE_TYPE_HALF2:
        literal->half2_value = parseSingleHalfX(parser, 2);
        break;
        case BaseType::BASE_TYPE_UINT2:
        literal->uint2_value = parseSingleUIntX(parser, 2);
        break;
        case BaseType::BASE_TYPE_INT3:
        literal->int3_value = parseSingleIntX(parser, 2);
        break;
        case BaseType::BASE_TYPE_HALF3:
        literal->half3_value = parseSingleHalfX(parser, 3);
        break;
        case BaseType::BASE_TYPE_UINT3:
        literal->uint3_value = parseSingleUIntX(parser, 3);
        break;
        case BaseType::BASE_TYPE_INT4:
        literal->int4_value = parseSingleIntX(parser, 4);
        break;
        case BaseType::BASE_TYPE_HALF4:
        literal->half4_value = parseSingleHalfX(parser, 4);
        break;
        case BaseType::BASE_TYPE_UINT4:
        literal->uint4_value = parseSingleUIntX(parser, 4);
        break;
        case BaseType::BASE_TYPE_INT3X3:
        literal->int3x3_value = parseSingleIntX(parser, 3*3);
        break;
        case BaseType::BASE_TYPE_HALF3x3:
        literal->half3x3_value = parseSingleHalfX(parser, 3*3);
        break;
        case BaseType::BASE_TYPE_UINT3X3:
        literal->uint3x3_value = parseSingleUIntX(parser, 3*3);
        break;
        case BaseType::BASE_TYPE_INT4X4:
        literal->int4x4_value = parseSingleIntX(parser, 4*4);
        break;
        case BaseType::BASE_TYPE_HALF4X4:
        literal->half4x4_value = parseSingleHalfX(parser, 4*4);
        break;
        case BaseType::BASE_TYPE_UINT4X4:
        literal->uint4x4_value = parseSingleUIntX(parser, 4*4);
        break;
        case BaseType::BASE_TYPE_BOOL:
        literal->bool_value = parseSingleBool(parser);
        break;
        case BaseType::BASE_TYPE_STRING:
        literal->string_value = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_STRING_LITERAL);
        break;
    }

    return literal;
}

Literal** parseLiteralList(Parser* parser, BaseType* type, unsigned int size) {
    Literal** literals = (Literal**)malloc(sizeof(Literal*) * size);
    parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);
    for(int i=0; i< size; i++) {
        literals[i] = parseLiteral(parser, type);
        if(i < size - 1) {
            parser->readToken(Token::TOKEN_COMMA);
        }
    }
    parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);
    
    return literals;
}

}

