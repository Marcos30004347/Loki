#ifndef LITERALS_H
#define LITERALS_H

#include "Parser.hpp"
#include "BaseType.hpp"

namespace HLSL {

struct Literal {
    BaseType* literal_type; // float, int, uint, bool, string
    bool bool_value;
    char* string_value;

    float float_value;
    float* float2_value;
    float* float3_value;
    float* float4_value;
    float* float3x3_value;
    float* float4x4_value;

    int int_value;
    int* int2_value;
    int* int3_value;
    int* int4_value;
    int* int3x3_value;
    int* int4x4_value;

    unsigned int uint_value;
    unsigned int* uint2_value;
    unsigned int* uint3_value;
    unsigned int* uint4_value;
    unsigned int* uint3x3_value;
    unsigned int* uint4x4_value;

    int half_value;
    int* half2_value;
    int* half3_value;
    int* half4_value;
    int* half3x3_value;
    int* half4x4_value;

};

Literal* parseLiteral(Parser* parser, BaseType* type);

Literal** parseLiteralList(Parser* parser, BaseType* type, unsigned int size);
}

#endif