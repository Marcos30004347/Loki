#ifndef HLSL_BUILD_IN_TYPES 
#define HLSL_BUILD_IN_TYPES

#include "Types.hpp"
#include "Parser.hpp"

namespace HLSL {

// Scalars
static ASTTypeDecl* int_type = nullptr;
static ASTTypeDecl* void_type = nullptr;
static ASTTypeDecl* float_type = nullptr;
static ASTTypeDecl* half_type = nullptr;
static ASTTypeDecl* double_type = nullptr;
static ASTTypeDecl* uint_type = nullptr;
static ASTTypeDecl* bool_type = nullptr;
static ASTTypeDecl* string_type = nullptr;

// Vectors2
static ASTTypeDecl* float2_type = nullptr;
static ASTTypeDecl* int2_type = nullptr;
static ASTTypeDecl* double2_type = nullptr;
static ASTTypeDecl* half2_type = nullptr;
static ASTTypeDecl* uint2_type = nullptr;

// Vectors3
static ASTTypeDecl* float3_type = nullptr;
static ASTTypeDecl* int3_type = nullptr;
static ASTTypeDecl* double3_type = nullptr;
static ASTTypeDecl* half3_type = nullptr;
static ASTTypeDecl* uint3_type = nullptr;

// Vectors4
static ASTTypeDecl* float4_type = nullptr;
static ASTTypeDecl* int4_type = nullptr;
static ASTTypeDecl* double4_type = nullptr;
static ASTTypeDecl* half4_type = nullptr;
static ASTTypeDecl* uint4_type = nullptr;

// Matrices2x2
static ASTTypeDecl* float2x2_type = nullptr;
static ASTTypeDecl* int2x2_type = nullptr;
static ASTTypeDecl* double2x2_type = nullptr;
static ASTTypeDecl* half2x2_type = nullptr;
static ASTTypeDecl* uint2x2_type = nullptr;

// Matrices3x2
static ASTTypeDecl* float3x2_type = nullptr;
static ASTTypeDecl* int3x2_type = nullptr;
static ASTTypeDecl* double3x2_type = nullptr;
static ASTTypeDecl* half3x2_type = nullptr;
static ASTTypeDecl* uint3x2_type = nullptr;

// Matrices4x2
static ASTTypeDecl* float4x2_type = nullptr;
static ASTTypeDecl* int4x2_type = nullptr;
static ASTTypeDecl* double4x2_type = nullptr;
static ASTTypeDecl* half4x2_type = nullptr;
static ASTTypeDecl* uint4x2_type = nullptr;

// Matrices2x3
static ASTTypeDecl* float2x3_type = nullptr;
static ASTTypeDecl* int2x3_type = nullptr;
static ASTTypeDecl* double2x3_type = nullptr;
static ASTTypeDecl* half2x3_type = nullptr;
static ASTTypeDecl* uint2x3_type = nullptr;

// Matrices3x3
static ASTTypeDecl* float3x3_type = nullptr;
static ASTTypeDecl* int3x3_type = nullptr;
static ASTTypeDecl* double3x3_type = nullptr;
static ASTTypeDecl* half3x3_type = nullptr;
static ASTTypeDecl* uint3x3_type = nullptr;

// Matrices4x3
static ASTTypeDecl* float4x3_type = nullptr;
static ASTTypeDecl* int4x3_type = nullptr;
static ASTTypeDecl* double4x3_type = nullptr;
static ASTTypeDecl* half4x3_type = nullptr;
static ASTTypeDecl* uint4x3_type = nullptr;

// Matrices2x4
static ASTTypeDecl* float2x4_type = nullptr;
static ASTTypeDecl* int2x4_type = nullptr;
static ASTTypeDecl* double2x4_type = nullptr;
static ASTTypeDecl* half2x4_type = nullptr;
static ASTTypeDecl* uint2x4_type = nullptr;

// Matrices3x4
static ASTTypeDecl* float3x4_type = nullptr;
static ASTTypeDecl* int3x4_type = nullptr;
static ASTTypeDecl* double3x4_type = nullptr;
static ASTTypeDecl* half3x4_type = nullptr;
static ASTTypeDecl* uint3x4_type = nullptr;

// Matrices4x4
static ASTTypeDecl* float4x4_type = nullptr;
static ASTTypeDecl* int4x4_type = nullptr;
static ASTTypeDecl* double4x4_type = nullptr;
static ASTTypeDecl* half4x4_type = nullptr;
static ASTTypeDecl* uint4x4_type = nullptr;

// sampler
static ASTTypeDecl* sampler_type = nullptr;
static ASTTypeDecl* sampler1D_type = nullptr;
static ASTTypeDecl* sampler2D_type = nullptr;
static ASTTypeDecl* sampler3D_type = nullptr;
static ASTTypeDecl* samplerCUBE_type = nullptr;
static ASTTypeDecl* sampler_state_type = nullptr;
static ASTTypeDecl* SamplerState_type = nullptr;

// Texture
static ASTTypeDecl* texture1D_type = nullptr;
static ASTTypeDecl* texture1DArray_type = nullptr;
static ASTTypeDecl* texture2D_type = nullptr;
static ASTTypeDecl* texture2DArray_type = nullptr;
static ASTTypeDecl* texture3D_type = nullptr;
static ASTTypeDecl* texture3DArray_type = nullptr;
static ASTTypeDecl* textureCube_type = nullptr;


void addBuiltInTypesToScope(Parser* parser);

};

#endif
//