#ifndef HLSL_BUILD_IN_TYPES 
#define HLSL_BUILD_IN_TYPES

#include "Types.hpp"
#include "Parser.hpp"

namespace HLSL {

// Scalars
static ASTType* int_type = nullptr;
static ASTType* void_type = nullptr;
static ASTType* float_type = nullptr;
static ASTType* half_type = nullptr;
static ASTType* double_type = nullptr;
static ASTType* uint_type = nullptr;
static ASTType* bool_type = nullptr;
static ASTType* string_type = nullptr;

// Vectors2
static ASTType* float2_type = nullptr;
static ASTType* int2_type = nullptr;
static ASTType* double2_type = nullptr;
static ASTType* half2_type = nullptr;
static ASTType* uint2_type = nullptr;

// Vectors3
static ASTType* float3_type = nullptr;
static ASTType* int3_type = nullptr;
static ASTType* double3_type = nullptr;
static ASTType* half3_type = nullptr;
static ASTType* uint3_type = nullptr;

// Vectors4
static ASTType* float4_type = nullptr;
static ASTType* int4_type = nullptr;
static ASTType* double4_type = nullptr;
static ASTType* half4_type = nullptr;
static ASTType* uint4_type = nullptr;

// Matrices2x2
static ASTType* float2x2_type = nullptr;
static ASTType* int2x2_type = nullptr;
static ASTType* double2x2_type = nullptr;
static ASTType* half2x2_type = nullptr;
static ASTType* uint2x2_type = nullptr;

// Matrices3x2
static ASTType* float3x2_type = nullptr;
static ASTType* int3x2_type = nullptr;
static ASTType* double3x2_type = nullptr;
static ASTType* half3x2_type = nullptr;
static ASTType* uint3x2_type = nullptr;

// Matrices4x2
static ASTType* float4x2_type = nullptr;
static ASTType* int4x2_type = nullptr;
static ASTType* double4x2_type = nullptr;
static ASTType* half4x2_type = nullptr;
static ASTType* uint4x2_type = nullptr;

// Matrices2x3
static ASTType* float2x3_type = nullptr;
static ASTType* int2x3_type = nullptr;
static ASTType* double2x3_type = nullptr;
static ASTType* half2x3_type = nullptr;
static ASTType* uint2x3_type = nullptr;

// Matrices3x3
static ASTType* float3x3_type = nullptr;
static ASTType* int3x3_type = nullptr;
static ASTType* double3x3_type = nullptr;
static ASTType* half3x3_type = nullptr;
static ASTType* uint3x3_type = nullptr;

// Matrices4x3
static ASTType* float4x3_type = nullptr;
static ASTType* int4x3_type = nullptr;
static ASTType* double4x3_type = nullptr;
static ASTType* half4x3_type = nullptr;
static ASTType* uint4x3_type = nullptr;

// Matrices2x4
static ASTType* float2x4_type = nullptr;
static ASTType* int2x4_type = nullptr;
static ASTType* double2x4_type = nullptr;
static ASTType* half2x4_type = nullptr;
static ASTType* uint2x4_type = nullptr;

// Matrices3x4
static ASTType* float3x4_type = nullptr;
static ASTType* int3x4_type = nullptr;
static ASTType* double3x4_type = nullptr;
static ASTType* half3x4_type = nullptr;
static ASTType* uint3x4_type = nullptr;

// Matrices4x4
static ASTType* float4x4_type = nullptr;
static ASTType* int4x4_type = nullptr;
static ASTType* double4x4_type = nullptr;
static ASTType* half4x4_type = nullptr;
static ASTType* uint4x4_type = nullptr;

// sampler
static ASTType* sampler_type = nullptr;
static ASTType* sampler1D_type = nullptr;
static ASTType* sampler2D_type = nullptr;
static ASTType* sampler3D_type = nullptr;
static ASTType* samplerCUBE_type = nullptr;
static ASTType* sampler_state_type = nullptr;
static ASTType* SamplerState_type = nullptr;

// Texture
static ASTType* texture1D_type = nullptr;
static ASTType* texture1DArray_type = nullptr;
static ASTType* texture2D_type = nullptr;
static ASTType* texture2DArray_type = nullptr;
static ASTType* texture3D_type = nullptr;
static ASTType* texture3DArray_type = nullptr;
static ASTType* textureCube_type = nullptr;


void addBuiltInTypesToScope(Parser* parser);

};

#endif
//