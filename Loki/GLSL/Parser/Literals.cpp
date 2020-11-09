#include "Literals.hpp"
#include "Lib/String.hpp"
#include <stdio.h>
#include <vector>

namespace GLSL {

ASTLiteral::ASTLiteral(): AST{NodeType::AST_LITERAL} {}

bool isValidInitializationListForType(ASTLiteral* literal, BaseType::Type type, bool is_array, unsigned int array_size) {
    if(is_array) {
        return literal->initialization_list_values.size() == array_size;
    }
    switch(type) {
        case BaseType::Type::BASE_TYPE_FLOAT:
        case BaseType::Type::BASE_TYPE_INT:
        case BaseType::Type::BASE_TYPE_FLOAT1X1:
        case BaseType::Type::BASE_TYPE_UINT1X1:
        case BaseType::Type::BASE_TYPE_INT1X1:
        case BaseType::Type::BASE_TYPE_HALF1X1:
        if(literal->initialization_list_values.size() > 1) { return false; }
        break;
    
    
        // Float Matrices
        case BaseType::Type::BASE_TYPE_FLOAT2:
        case BaseType::Type::BASE_TYPE_INT2:
        case BaseType::Type::BASE_TYPE_UINT2:
        case BaseType::Type::BASE_TYPE_HALF2:
        case BaseType::Type::BASE_TYPE_FLOAT1X2:
        case BaseType::Type::BASE_TYPE_FLOAT2X1:
        case BaseType::Type::BASE_TYPE_UINT1X2:
        case BaseType::Type::BASE_TYPE_UINT2X1:
        case BaseType::Type::BASE_TYPE_INT1X2:
        case BaseType::Type::BASE_TYPE_INT2X1:
        case BaseType::Type::BASE_TYPE_HALF1X2:
        case BaseType::Type::BASE_TYPE_HALF2X1:
        if(literal->initialization_list_values.size() > 2) { return false; }
        break;
    
        case BaseType::Type::BASE_TYPE_FLOAT3:
        case BaseType::Type::BASE_TYPE_INT3:
        case BaseType::Type::BASE_TYPE_UINT3:
        case BaseType::Type::BASE_TYPE_HALF3:
        case BaseType::Type::BASE_TYPE_FLOAT1X3:
        case BaseType::Type::BASE_TYPE_FLOAT3X1:
        case BaseType::Type::BASE_TYPE_UINT1X3:
        case BaseType::Type::BASE_TYPE_UINT3X1:
        case BaseType::Type::BASE_TYPE_INT1X3:
        case BaseType::Type::BASE_TYPE_INT3X1:
        case BaseType::Type::BASE_TYPE_HALF1X3:
        case BaseType::Type::BASE_TYPE_HALF3X1:
        if(literal->initialization_list_values.size() > 3) { return false; }
        break;
    
        case BaseType::Type::BASE_TYPE_FLOAT1X4:
        case BaseType::Type::BASE_TYPE_FLOAT4X1:
        case BaseType::Type::BASE_TYPE_UINT1X4:
        case BaseType::Type::BASE_TYPE_UINT4X1:
        case BaseType::Type::BASE_TYPE_INT1X4:
        case BaseType::Type::BASE_TYPE_INT4X1:
        case BaseType::Type::BASE_TYPE_HALF1X4:
        case BaseType::Type::BASE_TYPE_HALF4X1:
        if(literal->initialization_list_values.size() > 4) { return false; }
        break;

        case BaseType::Type::BASE_TYPE_FLOAT2X3:
        case BaseType::Type::BASE_TYPE_FLOAT3X2:
        case BaseType::Type::BASE_TYPE_UINT2X3:
        case BaseType::Type::BASE_TYPE_UINT3X2:
        case BaseType::Type::BASE_TYPE_INT2X3:
        case BaseType::Type::BASE_TYPE_INT3X2:
        case BaseType::Type::BASE_TYPE_HALF2X3:
        case BaseType::Type::BASE_TYPE_HALF3X2:
        if(literal->initialization_list_values.size() > 6) { return false; }
        break;

        case BaseType::Type::BASE_TYPE_FLOAT2X4:
        case BaseType::Type::BASE_TYPE_FLOAT4X2:
        case BaseType::Type::BASE_TYPE_UINT2X4:
        case BaseType::Type::BASE_TYPE_UINT4X2:
        case BaseType::Type::BASE_TYPE_INT2X4:
        case BaseType::Type::BASE_TYPE_INT4X2:
        case BaseType::Type::BASE_TYPE_HALF2X4:
        case BaseType::Type::BASE_TYPE_HALF4X2:
        if(literal->initialization_list_values.size() > 8) { return false; }
        break;

        case BaseType::Type::BASE_TYPE_FLOAT3X4:
        case BaseType::Type::BASE_TYPE_FLOAT4X3:
        case BaseType::Type::BASE_TYPE_UINT3X4:
        case BaseType::Type::BASE_TYPE_UINT4X3:
        case BaseType::Type::BASE_TYPE_INT3X4:
        case BaseType::Type::BASE_TYPE_INT4X3:
        case BaseType::Type::BASE_TYPE_HALF3X4:
        case BaseType::Type::BASE_TYPE_HALF4X3:
        if(literal->initialization_list_values.size() > 12) { return false; }
        break;

        case BaseType::Type::BASE_TYPE_FLOAT4:
        case BaseType::Type::BASE_TYPE_UINT4:
        case BaseType::Type::BASE_TYPE_INT4:
        case BaseType::Type::BASE_TYPE_HALF4:
        case BaseType::Type::BASE_TYPE_FLOAT4X4:
        case BaseType::Type::BASE_TYPE_UINT4X4:
        case BaseType::Type::BASE_TYPE_INT4X4:
        case BaseType::Type::BASE_TYPE_HALF4X4:
        if(literal->initialization_list_values.size() > 16) { return false; }
        break;
    
        default: {
            printf("Check struct initialization list validation");
            return true;
        }
    }
    return true;
}

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
        || parser->currentToken()->type == Token::TOKEN_DOUBLE 
        || parser->currentToken()->type == Token::TOKEN_DVEC2
        || parser->currentToken()->type == Token::TOKEN_DVEC3
        || parser->currentToken()->type == Token::TOKEN_DVEC4
        || parser->currentToken()->type == Token::TOKEN_DMAT2X2
        || parser->currentToken()->type == Token::TOKEN_DMAT2X3
        || parser->currentToken()->type == Token::TOKEN_DMAT2X4
        || parser->currentToken()->type == Token::TOKEN_DMAT3X2
        || parser->currentToken()->type == Token::TOKEN_DMAT3X3
        || parser->currentToken()->type == Token::TOKEN_DMAT3X4
        || parser->currentToken()->type == Token::TOKEN_DMAT4X2
        || parser->currentToken()->type == Token::TOKEN_DMAT4X3
        || parser->currentToken()->type == Token::TOKEN_DMAT4X4
        || parser->currentToken()->type == Token::TOKEN_VEC2
        || parser->currentToken()->type == Token::TOKEN_VEC3
        || parser->currentToken()->type == Token::TOKEN_VEC4
        || parser->currentToken()->type == Token::TOKEN_MAT2X2
        || parser->currentToken()->type == Token::TOKEN_MAT2X3
        || parser->currentToken()->type == Token::TOKEN_MAT2X4
        || parser->currentToken()->type == Token::TOKEN_MAT3X2
        || parser->currentToken()->type == Token::TOKEN_MAT3X3
        || parser->currentToken()->type == Token::TOKEN_MAT3X4
        || parser->currentToken()->type == Token::TOKEN_MAT4X2
        || parser->currentToken()->type == Token::TOKEN_MAT4X3
        || parser->currentToken()->type == Token::TOKEN_MAT4X4
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

char* parseSingleString(Parser* parser) {
    char* value = nullptr;
    if(parser->currentToken()->type == Token::TOKEN_STRING) {
        parser->readToken(Token::TOKEN_STRING);
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        value = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_STRING_LITERAL);
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    } else {
        value = parser->currentToken()->value;
        parser->readToken(Token::TOKEN_STRING_LITERAL);
    }
    return value;
}


int* parseSingleIntx(Parser* parser, unsigned int x) {
    int* value = new int[x];
    if(
        parser->currentToken()->type == Token::TOKEN_INT 
        || parser->currentToken()->type == Token::TOKEN_IVEC2
        || parser->currentToken()->type == Token::TOKEN_IVEC3
        || parser->currentToken()->type == Token::TOKEN_IVEC4
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



bool* parseSingleBoolx(Parser* parser, unsigned int x) {
    bool* value = new bool[x];
    if(
        parser->currentToken()->type == Token::TOKEN_BOOL 
        || parser->currentToken()->type == Token::TOKEN_BVEC2
        || parser->currentToken()->type == Token::TOKEN_BVEC3
        || parser->currentToken()->type == Token::TOKEN_BVEC4
    ) {
        parser->readToken(parser->currentToken()->type);
        parser->readToken(Token::TOKEN_OPEN_PARENTESIS);
        if(parser->currentToken()->type != Token::TOKEN_CLOSE_PARENTESIS) {
            int i=0;
            value[i] = parseSingleBool(parser);
            i++;
            while(parser->currentToken()->type == Token::TOKEN_COMMA) {
                i++;
                parser->readToken(Token::TOKEN_COMMA);
                value[i] = parseSingleBool(parser);
            }
        }
        parser->readToken(Token::TOKEN_CLOSE_PARENTESIS);
    } else {
        parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);
        if(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
            int i=0;
            value[i] = parseSingleBool(parser);
            i++;
            while(parser->currentToken()->type == Token::TOKEN_COMMA) {
                i++;
                parser->readToken(Token::TOKEN_COMMA);
                value[i] = parseSingleBool(parser);
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
        || parser->currentToken()->type == Token::TOKEN_UVEC2
        || parser->currentToken()->type == Token::TOKEN_UVEC3
        || parser->currentToken()->type == Token::TOKEN_UVEC4
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
        literal->literal_type = BaseType::BASE_TYPE_FLOAT;
        literal->float_value = parseSingleFloat(parser);
        break;
        case Token::Type::TOKEN_VEC2:
        case Token::Type::TOKEN_DVEC2:
        literal->literal_type = BaseType::BASE_TYPE_FLOAT2;
        literal->float2_value = parseSingleFloatx(parser, 2);
        break;
        case Token::Type::TOKEN_VEC3:
        case Token::Type::TOKEN_DVEC3:
        literal->literal_type = BaseType::BASE_TYPE_FLOAT3;
        literal->float3_value = parseSingleFloatx(parser, 3);
        break;
        case Token::Type::TOKEN_VEC4:
        case Token::Type::TOKEN_DVEC4:
        literal->literal_type = BaseType::BASE_TYPE_FLOAT4;
        literal->float4_value = parseSingleFloatx(parser, 4);
        break;
    
        // Float Matrices
        case Token::Type::TOKEN_MAT2X2:
        case Token::Type::TOKEN_DMAT2X2:
        literal->literal_type = BaseType::BASE_TYPE_FLOAT2X2;
        literal->float2x2_value = parseSingleFloatx(parser, 2*2);
        break;
        case Token::Type::TOKEN_MAT2X3:
        case Token::Type::TOKEN_DMAT2X3:
        literal->literal_type = BaseType::BASE_TYPE_FLOAT2X3;
        literal->float2x3_value = parseSingleFloatx(parser, 2*3);
        break;
        case Token::Type::TOKEN_MAT2X4:
        case Token::Type::TOKEN_DMAT2X4:
        literal->literal_type = BaseType::BASE_TYPE_FLOAT2X4;
        literal->float2x4_value = parseSingleFloatx(parser, 2*4);
        break;
        case Token::Type::TOKEN_MAT3X2:
        case Token::Type::TOKEN_DMAT3X2:
        literal->literal_type = BaseType::BASE_TYPE_FLOAT3X2;
        literal->float3x2_value = parseSingleFloatx(parser, 3*2);
        break;
        case Token::Type::TOKEN_MAT3X3:
        case Token::Type::TOKEN_DMAT3X3:
        literal->literal_type = BaseType::BASE_TYPE_FLOAT3X3;
        literal->float3x3_value = parseSingleFloatx(parser, 3*3);
        break;
        case Token::Type::TOKEN_MAT3X4:
        case Token::Type::TOKEN_DMAT3X4:
        literal->literal_type = BaseType::BASE_TYPE_FLOAT3X4;
        literal->float3x4_value = parseSingleFloatx(parser, 3*4);
        break;
        case Token::Type::TOKEN_MAT4X2:
        case Token::Type::TOKEN_DMAT4X2:
        literal->literal_type = BaseType::BASE_TYPE_FLOAT4X2;
        literal->float4x2_value = parseSingleFloatx(parser, 4*2);
        break;
        case Token::Type::TOKEN_MAT4X3:
        case Token::Type::TOKEN_DMAT4X3:
        literal->literal_type = BaseType::BASE_TYPE_FLOAT4X3;
        literal->float4x3_value = parseSingleFloatx(parser, 4*3);
        break;
        case Token::Type::TOKEN_MAT4X4:
        case Token::Type::TOKEN_DMAT4X4:
        literal->literal_type = BaseType::BASE_TYPE_FLOAT4X4;
        literal->float4x4_value = parseSingleFloatx(parser, 4*4);
        break;

        case Token::Type::TOKEN_INT:
        case Token::Type::TOKEN_INT_LITERAL:
        literal->literal_type = BaseType::BASE_TYPE_INT;
        literal->int_value = parseSingleInt(parser);
        break;
        case Token::Type::TOKEN_UINT:
        literal->literal_type = BaseType::BASE_TYPE_UINT;
        literal->uint_value = parseSingleUInt(parser);
        break;
        case Token::Type::TOKEN_IVEC2:
        literal->literal_type = BaseType::BASE_TYPE_INT2;
        literal->int2_value = parseSingleIntx(parser, 2);
        break;
        case Token::Type::TOKEN_UVEC2:
        literal->literal_type = BaseType::BASE_TYPE_UINT2;
        literal->uint2_value = parseSingleUIntx(parser, 2);
        break;
        case Token::Type::TOKEN_IVEC3:
        literal->literal_type = BaseType::BASE_TYPE_INT3;
        literal->int3_value = parseSingleIntx(parser, 2);
        break;
        case Token::Type::TOKEN_UVEC3:
        literal->literal_type = BaseType::BASE_TYPE_UINT3;
        literal->uint3_value = parseSingleUIntx(parser, 3);
        break;
        case Token::Type::TOKEN_IVEC4:
        literal->literal_type = BaseType::BASE_TYPE_INT3;
        literal->int4_value = parseSingleIntx(parser, 4);
        break;
        case Token::Type::TOKEN_UVEC4:
        literal->literal_type = BaseType::BASE_TYPE_UINT4;
        literal->uint4_value = parseSingleUIntx(parser, 4);
        break;
        case Token::Type::TOKEN_BOOL:
        literal->literal_type = BaseType::BASE_TYPE_BOOL;
        literal->bool_value = parseSingleBool(parser);
        break;

        case Token::Type::TOKEN_BVEC2:
        literal->literal_type = BaseType::BASE_TYPE_BOOL2;
        literal->bool2_value = parseSingleBoolx(parser, 2);
        break;

        case Token::Type::TOKEN_BVEC3:
        literal->literal_type = BaseType::BASE_TYPE_BOOL3;
        literal->bool3_value = parseSingleBoolx(parser, 3);
        break;

        case Token::Type::TOKEN_BVEC4:
        literal->literal_type = BaseType::BASE_TYPE_BOOL4;
        literal->bool4_value = parseSingleBoolx(parser, 4);
        break;

        case Token::Type::TOKEN_STRING:
        case Token::Type::TOKEN_STRING_LITERAL:
        literal->literal_type = BaseType::BASE_TYPE_STRING;
        literal->string_value = parseSingleString(parser);
        break;
    }
    return literal;
}



ASTLiteral* parseLiteral(Parser* parser) {
    ASTLiteral* literal = new ASTLiteral();
    literal->is_initialization_list = false;
    literal->value = nullptr;
    if(parser->currentToken()->type == Token::TOKEN_OPEN_CURLY_BRACKETS) {
        parser->readToken(Token::TOKEN_OPEN_CURLY_BRACKETS);

        if(parser->currentToken()->type != Token::TOKEN_CLOSE_CURLY_BRACKETS) {
            literal->is_initialization_list = true;
            literal->initialization_list_values.push_back(parseLiteral(parser));
            while(parser->currentToken()->type == Token::TOKEN_COMMA) {
                parser->readToken(Token::TOKEN_COMMA);
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


