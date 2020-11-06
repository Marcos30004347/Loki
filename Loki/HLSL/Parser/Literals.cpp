#include "Literals.hpp"
#include "Lib/String.hpp"
#include <stdio.h>
#include <vector>
namespace HLSL {

ASTLiteral::ASTLiteral(): AST{NodeType::NODE_TYPE_LITERAL} {}

bool isLiteralCastableTo(Literal* literal, BaseType::Type type) {
    if(literal->literal_type == type) return true;

    if(literal->literal_type >= BaseType::BASE_TYPE_SCALARS_START && literal->literal_type <= BaseType::BASE_TYPE_SCALARS_END)
            return type >= BaseType::BASE_TYPE_SCALARS_START && type <= BaseType::BASE_TYPE_SCALARS_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_SCALARS2_START && literal->literal_type <= BaseType::BASE_TYPE_SCALARS2_END)
            return type >= BaseType::BASE_TYPE_SCALARS2_START && type <= BaseType::BASE_TYPE_SCALARS2_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_SCALARS3_START && literal->literal_type <= BaseType::BASE_TYPE_SCALARS3_END)
            return type >= BaseType::BASE_TYPE_SCALARS3_START && type <= BaseType::BASE_TYPE_SCALARS3_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_SCALARS4_START && literal->literal_type <= BaseType::BASE_TYPE_SCALARS4_END)
            return type >= BaseType::BASE_TYPE_SCALARS4_START && type <= BaseType::BASE_TYPE_SCALARS4_END;
        
    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES1X1_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES1X1_END)
            return type >= BaseType::BASE_TYPE_MATRICES1X1_START && type <= BaseType::BASE_TYPE_MATRICES1X1_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES1X2_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES1X2_END)
            return type >= BaseType::BASE_TYPE_MATRICES1X2_START && type <= BaseType::BASE_TYPE_MATRICES1X2_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES1X3_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES1X3_END)
            return type >= BaseType::BASE_TYPE_MATRICES1X3_START && type <= BaseType::BASE_TYPE_MATRICES1X3_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES1X4_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES1X4_END)
            return type >= BaseType::BASE_TYPE_MATRICES1X4_START && type <= BaseType::BASE_TYPE_MATRICES1X4_END;

    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES2X1_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES2X1_END)
            return type >= BaseType::BASE_TYPE_MATRICES2X1_START && type <= BaseType::BASE_TYPE_MATRICES2X1_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES2X2_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES2X2_END)
            return type >= BaseType::BASE_TYPE_MATRICES2X2_START && type <= BaseType::BASE_TYPE_MATRICES2X2_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES2X3_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES2X3_END)
            return type >= BaseType::BASE_TYPE_MATRICES2X3_START && type <= BaseType::BASE_TYPE_MATRICES2X3_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES2X4_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES2X4_END)
            return type >= BaseType::BASE_TYPE_MATRICES2X4_START && type <= BaseType::BASE_TYPE_MATRICES2X4_END;

    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES3X1_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES3X1_END)
            return type >= BaseType::BASE_TYPE_MATRICES3X1_START && type <= BaseType::BASE_TYPE_MATRICES3X1_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES3X2_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES3X2_END)
            return type >= BaseType::BASE_TYPE_MATRICES3X2_START && type <= BaseType::BASE_TYPE_MATRICES3X2_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES3X3_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES3X3_END)
            return type >= BaseType::BASE_TYPE_MATRICES3X3_START && type <= BaseType::BASE_TYPE_MATRICES3X3_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES3X4_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES3X4_END)
            return type >= BaseType::BASE_TYPE_MATRICES3X4_START && type <= BaseType::BASE_TYPE_MATRICES3X4_END;

    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES4X1_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES4X1_END)
            return type >= BaseType::BASE_TYPE_MATRICES4X1_START && type <= BaseType::BASE_TYPE_MATRICES4X1_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES4X2_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES4X2_END)
            return type >= BaseType::BASE_TYPE_MATRICES4X2_START && type <= BaseType::BASE_TYPE_MATRICES4X2_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES4X3_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES4X3_END)
            return type >= BaseType::BASE_TYPE_MATRICES4X3_START && type <= BaseType::BASE_TYPE_MATRICES4X3_END;
    if(literal->literal_type >= BaseType::BASE_TYPE_MATRICES4X4_START && literal->literal_type <= BaseType::BASE_TYPE_MATRICES4X4_END)
            return type >= BaseType::BASE_TYPE_MATRICES4X4_START && type <= BaseType::BASE_TYPE_MATRICES4X4_END;

    return false;
}


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

float* parseSingleFloatx(Parser* parser, unsigned int x) {
    float* value = new float[x];

    if(
        parser->currentToken()->type == Token::TOKEN_FLOAT 
        || parser->currentToken()->type == Token::TOKEN_FLOAT2
        || parser->currentToken()->type == Token::TOKEN_FLOAT3
        || parser->currentToken()->type == Token::TOKEN_FLOAT4
        || parser->currentToken()->type == Token::TOKEN_FLOAT1x1
        || parser->currentToken()->type == Token::TOKEN_FLOAT1x2
        || parser->currentToken()->type == Token::TOKEN_FLOAT1x3
        || parser->currentToken()->type == Token::TOKEN_FLOAT1x4
        || parser->currentToken()->type == Token::TOKEN_FLOAT2x1
        || parser->currentToken()->type == Token::TOKEN_FLOAT2x2
        || parser->currentToken()->type == Token::TOKEN_FLOAT2x3
        || parser->currentToken()->type == Token::TOKEN_FLOAT2x4
        || parser->currentToken()->type == Token::TOKEN_FLOAT3x1
        || parser->currentToken()->type == Token::TOKEN_FLOAT3x2
        || parser->currentToken()->type == Token::TOKEN_FLOAT3x3
        || parser->currentToken()->type == Token::TOKEN_FLOAT3x4
        || parser->currentToken()->type == Token::TOKEN_FLOAT4x1
        || parser->currentToken()->type == Token::TOKEN_FLOAT4x2
        || parser->currentToken()->type == Token::TOKEN_FLOAT4x3
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

int* parseSingleHalfx(Parser* parser, unsigned int x) {
    int* value = new int[x];
    if(
        parser->currentToken()->type == Token::TOKEN_HALF 
        || parser->currentToken()->type == Token::TOKEN_HALF2
        || parser->currentToken()->type == Token::TOKEN_HALF3
        || parser->currentToken()->type == Token::TOKEN_HALF4
        || parser->currentToken()->type == Token::TOKEN_HALF1x1
        || parser->currentToken()->type == Token::TOKEN_HALF1x2
        || parser->currentToken()->type == Token::TOKEN_HALF1x3
        || parser->currentToken()->type == Token::TOKEN_HALF1x4
        || parser->currentToken()->type == Token::TOKEN_HALF2x1
        || parser->currentToken()->type == Token::TOKEN_HALF2x2
        || parser->currentToken()->type == Token::TOKEN_HALF2x3
        || parser->currentToken()->type == Token::TOKEN_HALF2x4
        || parser->currentToken()->type == Token::TOKEN_HALF3x1
        || parser->currentToken()->type == Token::TOKEN_HALF3x2
        || parser->currentToken()->type == Token::TOKEN_HALF3x3
        || parser->currentToken()->type == Token::TOKEN_HALF3x4
        || parser->currentToken()->type == Token::TOKEN_HALF4x1
        || parser->currentToken()->type == Token::TOKEN_HALF4x2
        || parser->currentToken()->type == Token::TOKEN_HALF4x3
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


int* parseSingleIntx(Parser* parser, unsigned int x) {
    int* value = new int[x];
    if(
        parser->currentToken()->type == Token::TOKEN_INT 
        || parser->currentToken()->type == Token::TOKEN_INT2
        || parser->currentToken()->type == Token::TOKEN_INT3
        || parser->currentToken()->type == Token::TOKEN_INT4
        || parser->currentToken()->type == Token::TOKEN_INT1x1
        || parser->currentToken()->type == Token::TOKEN_INT1x2
        || parser->currentToken()->type == Token::TOKEN_INT1x3
        || parser->currentToken()->type == Token::TOKEN_INT1x4
        || parser->currentToken()->type == Token::TOKEN_INT2x1
        || parser->currentToken()->type == Token::TOKEN_INT2x2
        || parser->currentToken()->type == Token::TOKEN_INT2x3
        || parser->currentToken()->type == Token::TOKEN_INT2x4
        || parser->currentToken()->type == Token::TOKEN_INT3x1
        || parser->currentToken()->type == Token::TOKEN_INT3x2
        || parser->currentToken()->type == Token::TOKEN_INT3x3
        || parser->currentToken()->type == Token::TOKEN_INT3x4
        || parser->currentToken()->type == Token::TOKEN_INT4x1
        || parser->currentToken()->type == Token::TOKEN_INT4x2
        || parser->currentToken()->type == Token::TOKEN_INT4x3
        || parser->currentToken()->type == Token::TOKEN_INT4x4
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

unsigned int* parseSingleUIntx(Parser* parser, unsigned int x) {
    unsigned int* value = new unsigned int[x];
    if(
        parser->currentToken()->type == Token::TOKEN_UINT 
        || parser->currentToken()->type == Token::TOKEN_UINT2
        || parser->currentToken()->type == Token::TOKEN_UINT3
        || parser->currentToken()->type == Token::TOKEN_UINT4
        || parser->currentToken()->type == Token::TOKEN_UINT1x1
        || parser->currentToken()->type == Token::TOKEN_UINT1x2
        || parser->currentToken()->type == Token::TOKEN_UINT1x3
        || parser->currentToken()->type == Token::TOKEN_UINT1x4
        || parser->currentToken()->type == Token::TOKEN_UINT2x1
        || parser->currentToken()->type == Token::TOKEN_UINT2x2
        || parser->currentToken()->type == Token::TOKEN_UINT2x3
        || parser->currentToken()->type == Token::TOKEN_UINT2x4
        || parser->currentToken()->type == Token::TOKEN_UINT3x1
        || parser->currentToken()->type == Token::TOKEN_UINT3x2
        || parser->currentToken()->type == Token::TOKEN_UINT3x3
        || parser->currentToken()->type == Token::TOKEN_UINT3x4
        || parser->currentToken()->type == Token::TOKEN_UINT4x1
        || parser->currentToken()->type == Token::TOKEN_UINT4x2
        || parser->currentToken()->type == Token::TOKEN_UINT4x3
        || parser->currentToken()->type == Token::TOKEN_UINT4x4
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


Literal* parseLiteralValue(Parser* parser) {
    Token* token = parser->currentToken();
    Literal* literal = new Literal();

    switch(parser->currentToken()->type) {
        case Token::Type::TOKEN_FLOAT:
        case Token::Type::TOKEN_FLOAT_LITERAL:
        literal->float_value = parseSingleFloat(parser);
        break;
        case Token::Type::TOKEN_FLOAT2:
        literal->float2_value = parseSingleFloatx(parser, 2);
        break;
        case Token::Type::TOKEN_FLOAT3:
        literal->float3_value = parseSingleFloatx(parser, 3);
        break;
        case Token::Type::TOKEN_FLOAT4:
        literal->float4_value = parseSingleFloatx(parser, 4);
        break;
    
        // Float Matrices
        case Token::Type::TOKEN_FLOAT1x1:
        literal->float1x1_value = parseSingleFloatx(parser, 1*1);
        break;
        case Token::Type::TOKEN_FLOAT1x2:
        literal->float1x2_value = parseSingleFloatx(parser, 1*2);
        break;
        case Token::Type::TOKEN_FLOAT1x3:
        literal->float1x3_value = parseSingleFloatx(parser, 1*3);
        break;
        case Token::Type::TOKEN_FLOAT1x4:
        literal->float1x4_value = parseSingleFloatx(parser, 1*4);
        break;
        case Token::Type::TOKEN_FLOAT2x1:
        literal->float2x1_value = parseSingleFloatx(parser, 2*1);
        break;
        case Token::Type::TOKEN_FLOAT2x2:
        literal->float2x2_value = parseSingleFloatx(parser, 2*2);
        break;
        case Token::Type::TOKEN_FLOAT2x3:
        literal->float2x3_value = parseSingleFloatx(parser, 2*3);
        break;
        case Token::Type::TOKEN_FLOAT2x4:
        literal->float2x4_value = parseSingleFloatx(parser, 2*4);
        break;
        case Token::Type::TOKEN_FLOAT3x1:
        literal->float3x1_value = parseSingleFloatx(parser, 3*1);
        break;
        case Token::Type::TOKEN_FLOAT3x2:
        literal->float3x2_value = parseSingleFloatx(parser, 3*2);
        break;
        case Token::Type::TOKEN_FLOAT3x3:
        literal->float3x3_value = parseSingleFloatx(parser, 3*3);
        break;
        case Token::Type::TOKEN_FLOAT3x4:
        literal->float3x4_value = parseSingleFloatx(parser, 3*4);
        break;
        case Token::Type::TOKEN_FLOAT4x1:
        literal->float4x1_value = parseSingleFloatx(parser, 4*1);
        break;
        case Token::Type::TOKEN_FLOAT4x2:
        literal->float4x2_value = parseSingleFloatx(parser, 4*2);
        break;
        case Token::Type::TOKEN_FLOAT4x3:
        literal->float4x3_value = parseSingleFloatx(parser, 4*3);
        break;
        case Token::Type::TOKEN_FLOAT4x4:
        literal->float4x4_value = parseSingleFloatx(parser, 4*4);
        break;

        // UInt Matrices
        case Token::Type::TOKEN_UINT1x1:
        literal->uint1x1_value = parseSingleUIntx(parser, 1*1);
        break;
        case Token::Type::TOKEN_UINT1x2:
        literal->uint1x2_value = parseSingleUIntx(parser, 1*2);
        break;
        case Token::Type::TOKEN_UINT1x3:
        literal->uint1x3_value = parseSingleUIntx(parser, 1*3);
        break;
        case Token::Type::TOKEN_UINT1x4:
        literal->uint1x4_value = parseSingleUIntx(parser, 1*4);
        break;
        case Token::Type::TOKEN_UINT2x1:
        literal->uint2x1_value = parseSingleUIntx(parser, 2*1);
        break;
        case Token::Type::TOKEN_UINT2x2:
        literal->uint2x2_value = parseSingleUIntx(parser, 2*2);
        break;
        case Token::Type::TOKEN_UINT2x3:
        literal->uint2x3_value = parseSingleUIntx(parser, 2*3);
        break;
        case Token::Type::TOKEN_UINT2x4:
        literal->uint2x4_value = parseSingleUIntx(parser, 2*4);
        break;
        case Token::Type::TOKEN_UINT3x1:
        literal->uint3x1_value = parseSingleUIntx(parser, 3*1);
        break;
        case Token::Type::TOKEN_UINT3x2:
        literal->uint3x2_value = parseSingleUIntx(parser, 3*2);
        break;
        case Token::Type::TOKEN_UINT3x3:
        literal->uint3x3_value = parseSingleUIntx(parser, 3*3);
        break;
        case Token::Type::TOKEN_UINT3x4:
        literal->uint3x4_value = parseSingleUIntx(parser, 3*4);
        break;
        case Token::Type::TOKEN_UINT4x1:
        literal->uint4x1_value = parseSingleUIntx(parser, 4*1);
        break;
        case Token::Type::TOKEN_UINT4x2:
        literal->uint3x3_value = parseSingleUIntx(parser, 4*2);
        break;
        case Token::Type::TOKEN_UINT4x3:
        literal->uint4x3_value = parseSingleUIntx(parser, 4*3);
        break;
        case Token::Type::TOKEN_UINT4x4:
        literal->uint4x4_value = parseSingleUIntx(parser, 4*4);
        break;

        // Int Matrices
        case Token::Type::TOKEN_INT1x1:
        literal->int1x1_value = parseSingleIntx(parser, 1*1);
        break;
        case Token::Type::TOKEN_INT1x2:
        literal->int1x2_value = parseSingleIntx(parser, 1*2);
        break;
        case Token::Type::TOKEN_INT1x3:
        literal->int1x3_value = parseSingleIntx(parser, 1*3);
        break;
        case Token::Type::TOKEN_INT1x4:
        literal->int1x4_value = parseSingleIntx(parser, 1*4);
        break;
        case Token::Type::TOKEN_INT2x1:
        literal->int2x1_value = parseSingleIntx(parser, 2*1);
        break;
        case Token::Type::TOKEN_INT2x2:
        literal->int2x2_value = parseSingleIntx(parser, 2*2);
        break;
        case Token::Type::TOKEN_INT2x3:
        literal->int2x3_value = parseSingleIntx(parser, 2*3);
        break;
        case Token::Type::TOKEN_INT2x4:
        literal->int2x4_value = parseSingleIntx(parser, 2*4);
        break;
        case Token::Type::TOKEN_INT3x1:
        literal->int3x1_value = parseSingleIntx(parser, 3*1);
        break;
        case Token::Type::TOKEN_INT3x2:
        literal->int3x2_value = parseSingleIntx(parser, 3*2);
        break;
        case Token::Type::TOKEN_INT3x3:
        literal->int3x3_value = parseSingleIntx(parser, 3*3);
        break;
        case Token::Type::TOKEN_INT3x4:
        literal->int3x4_value = parseSingleIntx(parser, 3*4);
        break;
        case Token::Type::TOKEN_INT4x1:
        literal->int4x1_value = parseSingleIntx(parser, 4*1);
        break;
        case Token::Type::TOKEN_INT4x2:
        literal->int4x2_value = parseSingleIntx(parser, 4*2);
        break;
        case Token::Type::TOKEN_INT4x3:
        literal->int4x3_value = parseSingleIntx(parser, 4*3);
        break;
        case Token::Type::TOKEN_INT4x4:
        literal->int4x4_value = parseSingleIntx(parser, 4*4);
        break;

        // Half Matrices
        case Token::Type::TOKEN_HALF1x1:
        literal->half1x1_value = parseSingleIntx(parser, 1*1);
        break;
        case Token::Type::TOKEN_HALF1x2:
        literal->half1x2_value = parseSingleHalfx(parser, 1*2);
        break;
        case Token::Type::TOKEN_HALF1x3:
        literal->half1x3_value = parseSingleHalfx(parser, 1*3);
        break;
        case Token::Type::TOKEN_HALF1x4:
        literal->half1x4_value = parseSingleHalfx(parser, 1*4);
        break;
        case Token::Type::TOKEN_HALF2x1:
        literal->half2x1_value = parseSingleHalfx(parser, 2*1);
        break;
        case Token::Type::TOKEN_HALF2x2:
        literal->half2x2_value = parseSingleHalfx(parser, 2*2);
        break;
        case Token::Type::TOKEN_HALF2x3:
        literal->half2x3_value = parseSingleHalfx(parser, 2*3);
        break;
        case Token::Type::TOKEN_HALF2x4:
        literal->half2x4_value = parseSingleHalfx(parser, 2*4);
        break;
        case Token::Type::TOKEN_HALF3x1:
        literal->half3x1_value = parseSingleHalfx(parser, 3*1);
        break;
        case Token::Type::TOKEN_HALF3x2:
        literal->half3x2_value = parseSingleHalfx(parser, 3*2);
        break;
        case Token::Type::TOKEN_HALF3x3:
        literal->half3x3_value = parseSingleHalfx(parser, 3*3);
        break;
        case Token::Type::TOKEN_HALF3x4:
        literal->half3x4_value = parseSingleHalfx(parser, 3*4);
        break;
        case Token::Type::TOKEN_HALF4x1:
        literal->half4x1_value = parseSingleHalfx(parser, 4*1);
        break;
        case Token::Type::TOKEN_HALF4x2:
        literal->half4x2_value = parseSingleHalfx(parser, 4*2);
        break;
        case Token::Type::TOKEN_HALF4x3:
        literal->half4x3_value = parseSingleHalfx(parser, 4*3);
        break;
        case Token::Type::TOKEN_HALF4x4:
        literal->half4x4_value = parseSingleHalfx(parser, 4*4);
        break;

        break;
        case Token::Type::TOKEN_INT:
        case Token::Type::TOKEN_INT_LITERAL:
        literal->int_value = parseSingleInt(parser);
        break;
        case Token::Type::TOKEN_HALF:
        literal->half_value = parseSingleHalf(parser);
        break;
        case Token::Type::TOKEN_UINT:
        literal->uint_value = parseSingleUInt(parser);
        break;
        case Token::Type::TOKEN_INT2:
        literal->int2_value = parseSingleIntx(parser, 2);
        break;
        case Token::Type::TOKEN_HALF2:
        literal->half2_value = parseSingleHalfx(parser, 2);
        break;
        case Token::Type::TOKEN_UINT2:
        literal->uint2_value = parseSingleUIntx(parser, 2);
        break;
        case Token::Type::TOKEN_INT3:
        literal->int3_value = parseSingleIntx(parser, 2);
        break;
        case Token::Type::TOKEN_HALF3:
        literal->half3_value = parseSingleHalfx(parser, 3);
        break;
        case Token::Type::TOKEN_UINT3:
        literal->uint3_value = parseSingleUIntx(parser, 3);
        break;
        case Token::Type::TOKEN_INT4:
        literal->int4_value = parseSingleIntx(parser, 4);
        break;
        case Token::Type::TOKEN_HALF4:
        literal->half4_value = parseSingleHalfx(parser, 4);
        break;
        case Token::Type::TOKEN_UINT4:
        literal->uint4_value = parseSingleUIntx(parser, 4);
        break;
        case Token::Type::TOKEN_BOOL:
        literal->bool_value = parseSingleBool(parser);
        break;
        case Token::Type::TOKEN_STRING:
        literal->string_value = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_STRING_LITERAL);
        break;
    }
    return literal;
}



ASTLiteral* parseLiteral(Parser* parser) {
    ASTLiteral* literal = new ASTLiteral();
    literal->is_initialization_list = false;
    literal->value = nullptr;
    if(parser->currentToken()->type == Token::TOKEN_CLOSE_CURLY_BRACKETS) {
        parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);

        if(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
            literal->is_initialization_list = true;

            parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);
            literal->initialization_list_values.push_back(parseLiteral(parser));
            while(parser->currentToken()->type == Token::TOKEN_COMMA) {
                parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);
                literal->initialization_list_values.push_back(parseLiteral(parser));
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_CURLY_BRACKETS);
    } else {
        literal->value = parseLiteralValue(parser);
    }

    return literal;
}


}


