#ifndef LITERALS_H
#define LITERALS_H

#include "Parser.hpp"
#include "BaseType.hpp"
#include "AST.hpp"

namespace HLSL {

struct Literal {
    BaseType::Type literal_type;

    bool bool_value;

    char* string_value;

    float float_value;
    float* float2_value;
    float* float3_value;
    float* float4_value;
    float* float1x1_value;
    float* float1x2_value;
    float* float1x3_value;
    float* float1x4_value;
    float* float2x1_value;
    float* float2x2_value;
    float* float2x3_value;
    float* float2x4_value;
    float* float3x1_value;
    float* float3x2_value;
    float* float3x3_value;
    float* float3x4_value;
    float* float4x1_value;
    float* float4x2_value;
    float* float4x3_value;
    float* float4x4_value;

    int int_value;
    int* int2_value;
    int* int3_value;
    int* int4_value;
    int* int1x1_value;
    int* int1x2_value;
    int* int1x3_value;
    int* int1x4_value;
    int* int2x1_value;
    int* int2x2_value;
    int* int2x3_value;
    int* int2x4_value;
    int* int3x1_value;
    int* int3x2_value;
    int* int3x3_value;
    int* int3x4_value;
    int* int4x1_value;
    int* int4x2_value;
    int* int4x3_value;
    int* int4x4_value;

    unsigned int uint_value;
    unsigned int* uint2_value;
    unsigned int* uint3_value;
    unsigned int* uint4_value;
    unsigned int* uint1x1_value;
    unsigned int* uint1x2_value;
    unsigned int* uint1x3_value;
    unsigned int* uint1x4_value;
    unsigned int* uint2x1_value;
    unsigned int* uint2x2_value;
    unsigned int* uint2x3_value;
    unsigned int* uint2x4_value;
    unsigned int* uint3x1_value;
    unsigned int* uint3x2_value;
    unsigned int* uint3x3_value;
    unsigned int* uint3x4_value;
    unsigned int* uint4x1_value;
    unsigned int* uint4x2_value;
    unsigned int* uint4x3_value;
    unsigned int* uint4x4_value;

    int half_value;
    int* half2_value;
    int* half3_value;
    int* half4_value;
    int* half1x1_value;
    int* half1x2_value;
    int* half1x3_value;
    int* half1x4_value;
    int* half2x1_value;
    int* half2x2_value;
    int* half2x3_value;
    int* half2x4_value;
    int* half3x1_value;
    int* half3x2_value;
    int* half3x3_value;
    int* half3x4_value;
    int* half4x1_value;
    int* half4x2_value;
    int* half4x3_value;
    int* half4x4_value;
};

struct ASTLiteral: AST {
    explicit ASTLiteral();

    std::vector<ASTLiteral*> initialization_list_values;
    Literal* value;
    bool is_initialization_list;
};



ASTLiteral* parseLiteral(Parser* parser);

ASTLiteral** parseLiteralList(Parser* parser, unsigned int size);
bool isLiteralCastableTo(Literal* literal, BaseType::Type type);
bool isValidInitializationListForType(ASTLiteral* literal, BaseType::Type type, bool is_array, unsigned int array_size);

}

#endif