// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-data-types
#ifndef BASE_TYPE_H
#define BASE_TYPE_H

#include "Parser.hpp"

namespace HLSL {

struct BaseType {
    enum Type {
        BASE_TYPE_UNKNOWN,
        BASE_TYPE_VOID,   
     
        BASE_TYPE_FLOAT,
        BASE_TYPE_FLOAT2,
        BASE_TYPE_FLOAT3,
        BASE_TYPE_FLOAT4,
        BASE_TYPE_FLOAT3x3,
        BASE_TYPE_FLOAT4x4,
    
        BASE_TYPE_HALF,
        BASE_TYPE_HALF2,
        BASE_TYPE_HALF3,
        BASE_TYPE_HALF4,
        BASE_TYPE_HALF3x3,
        BASE_TYPE_HALF4X4,
    
        BASE_TYPE_INT,
        BASE_TYPE_INT2,
        BASE_TYPE_INT3,
        BASE_TYPE_INT4,
        BASE_TYPE_INT3X3,
        BASE_TYPE_INT4X4,

        BASE_TYPE_BOOL,
        
        BASE_TYPE_UINT,
        BASE_TYPE_UINT2,
        BASE_TYPE_UINT3,
        BASE_TYPE_UINT4,
        BASE_TYPE_UINT3X3,
        BASE_TYPE_UINT4X4,

        BASE_TYPE_TEXTURE,
        BASE_TYPE_SAMPLER2D,
        BASE_TYPE_SAMPLER_CUBE,

        BASE_TYPE_STRING,

        BASE_TYPE_USER_DEFINED,       // struct
    };

    char* name;
    Type type;
};

BaseType* parseBaseType(Parser* parser);

}

#endif
