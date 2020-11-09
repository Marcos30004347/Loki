#include "BaseType.hpp"
#include <cstdlib>
#include <cctype>
#include <stdlib.h>
#include <stdio.h>

namespace GLSL {

BaseType* parseDeclarationBaseType(Parser* parser) {
    BaseType* type = new BaseType();
    type->name = parser->currentToken()->value;

    switch(parser->currentToken()->type) {
        case Token::TOKEN_VOID: 
        parser->readToken(Token::TOKEN_VOID);
        type->type = BaseType::Type::BASE_TYPE_VOID;
        break;
    
        case Token::TOKEN_BOOL: 
        parser->readToken(Token::TOKEN_BOOL);
        type->type = BaseType::Type::BASE_TYPE_BOOL;
        break;
    
        case Token::TOKEN_INT: 
        parser->readToken(Token::TOKEN_INT);
        type->type = BaseType::Type::BASE_TYPE_INT1X1;
        break; 
    
        case Token::TOKEN_UINT: 
        parser->readToken(Token::TOKEN_UINT);
        type->type = BaseType::Type::BASE_TYPE_UINT;
        break; 

        case Token::TOKEN_FLOAT: 
        parser->readToken(Token::TOKEN_FLOAT);
        type->type = BaseType::Type::BASE_TYPE_FLOAT;
        break; 

        case Token::TOKEN_DOUBLE: 
        parser->readToken(Token::TOKEN_DOUBLE);
        type->type = BaseType::Type::BASE_TYPE_FLOAT;
        break; 

        case Token::TOKEN_VEC2: 
        parser->readToken(Token::TOKEN_VEC2);
        type->type = BaseType::Type::BASE_TYPE_FLOAT2;
        break; 

        case Token::TOKEN_VEC3: 
        parser->readToken(Token::TOKEN_VEC3);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3;
        break; 

        case Token::TOKEN_VEC4: 
        parser->readToken(Token::TOKEN_VEC4);
        type->type = BaseType::Type::BASE_TYPE_FLOAT4;
        break; 

        case Token::TOKEN_DVEC2: 
        parser->readToken(Token::TOKEN_DVEC2);
        type->type = BaseType::Type::BASE_TYPE_FLOAT2;
        break; 

        case Token::TOKEN_DVEC3: 
        parser->readToken(Token::TOKEN_DVEC3);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3;
        break; 

        case Token::TOKEN_DVEC4: 
        parser->readToken(Token::TOKEN_DVEC4);
        type->type = BaseType::Type::BASE_TYPE_FLOAT4;
        break; 

        case Token::TOKEN_IVEC2: 
        parser->readToken(Token::TOKEN_IVEC2);
        type->type = BaseType::Type::BASE_TYPE_INT2;
        break; 

        case Token::TOKEN_IVEC3: 
        parser->readToken(Token::TOKEN_IVEC3);
        type->type = BaseType::Type::BASE_TYPE_INT3;
        break; 

        case Token::TOKEN_IVEC4: 
        parser->readToken(Token::TOKEN_IVEC4);
        type->type = BaseType::Type::BASE_TYPE_INT4;
        break; 

        case Token::TOKEN_UVEC2: 
        parser->readToken(Token::TOKEN_UVEC2);
        type->type = BaseType::Type::BASE_TYPE_UINT2;
        break; 

        case Token::TOKEN_UVEC3: 
        parser->readToken(Token::TOKEN_UVEC3);
        type->type = BaseType::Type::BASE_TYPE_UINT3;
        break; 

        case Token::TOKEN_UVEC4: 
        parser->readToken(Token::TOKEN_UVEC4);
        type->type = BaseType::Type::BASE_TYPE_UINT4;
        break; 

        case Token::TOKEN_BVEC2: 
        parser->readToken(Token::TOKEN_BVEC2);
        type->type = BaseType::Type::BASE_TYPE_BOOL2;
        break; 

        case Token::TOKEN_BVEC3: 
        parser->readToken(Token::TOKEN_BVEC3);
        type->type = BaseType::Type::BASE_TYPE_BOOL3;
        break; 

        case Token::TOKEN_BVEC4: 
        parser->readToken(Token::TOKEN_BVEC4);
        type->type = BaseType::Type::BASE_TYPE_BOOL4;
        break; 


        case Token::TOKEN_MAT2: 
        parser->readToken(Token::TOKEN_MAT2);
        type->type = BaseType::Type::BASE_TYPE_FLOAT2X2;
        break; 

        case Token::TOKEN_MAT3: 
        parser->readToken(Token::TOKEN_MAT3);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3X3;
        break; 

        case Token::TOKEN_MAT4: 
        parser->readToken(Token::TOKEN_MAT4);
        type->type = BaseType::Type::BASE_TYPE_FLOAT4X4;
        break; 

        case Token::TOKEN_DMAT2: 
        parser->readToken(Token::TOKEN_DMAT2);
        type->type = BaseType::Type::BASE_TYPE_FLOAT2X2;
        break; 

        case Token::TOKEN_DMAT3: 
        parser->readToken(Token::TOKEN_DMAT3);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3X3;
        break; 

        case Token::TOKEN_DMAT4: 
        parser->readToken(Token::TOKEN_DMAT4);
        type->type = BaseType::Type::BASE_TYPE_FLOAT4X4;
        break; 

        case Token::TOKEN_MAT2X2: 
        parser->readToken(Token::TOKEN_MAT2X2);
        type->type = BaseType::Type::BASE_TYPE_FLOAT2X2;
        break; 

        case Token::TOKEN_MAT2X3: 
        parser->readToken(Token::TOKEN_MAT2X3);
        type->type = BaseType::Type::BASE_TYPE_FLOAT2X3;
        break; 

        case Token::TOKEN_MAT2X4: 
        parser->readToken(Token::TOKEN_MAT2X4);
        type->type = BaseType::Type::BASE_TYPE_FLOAT2X4;
        break; 

        case Token::TOKEN_MAT3X2: 
        parser->readToken(Token::TOKEN_MAT3X2);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3X2;
        break; 

        case Token::TOKEN_MAT3X3: 
        parser->readToken(Token::TOKEN_MAT3X3);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3X3;
        break; 

        case Token::TOKEN_MAT3X4: 
        parser->readToken(Token::TOKEN_MAT3X4);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3X4;
        break; 

        case Token::TOKEN_MAT4X2: 
        parser->readToken(Token::TOKEN_MAT4X2);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3X2;
        break; 

        case Token::TOKEN_MAT4X3: 
        parser->readToken(Token::TOKEN_MAT4X3);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3X3;
        break; 

        case Token::TOKEN_MAT4X4: 
        parser->readToken(Token::TOKEN_MAT4X4);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3X4;
        break; 


        case Token::TOKEN_DMAT2X2: 
        parser->readToken(Token::TOKEN_DMAT2X2);
        type->type = BaseType::Type::BASE_TYPE_FLOAT2X2;
        break; 

        case Token::TOKEN_DMAT2X3: 
        parser->readToken(Token::TOKEN_DMAT2X3);
        type->type = BaseType::Type::BASE_TYPE_FLOAT2X3;
        break; 

        case Token::TOKEN_DMAT2X4: 
        parser->readToken(Token::TOKEN_DMAT2X4);
        type->type = BaseType::Type::BASE_TYPE_FLOAT2X4;
        break; 

        case Token::TOKEN_DMAT3X2: 
        parser->readToken(Token::TOKEN_DMAT3X2);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3X2;
        break; 

        case Token::TOKEN_DMAT3X3: 
        parser->readToken(Token::TOKEN_DMAT3X3);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3X3;
        break; 

        case Token::TOKEN_DMAT3X4: 
        parser->readToken(Token::TOKEN_DMAT3X4);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3X4;
        break; 

        case Token::TOKEN_DMAT4X2: 
        parser->readToken(Token::TOKEN_DMAT4X2);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3X2;
        break; 

        case Token::TOKEN_DMAT4X3: 
        parser->readToken(Token::TOKEN_DMAT4X3);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3X3;
        break; 

        case Token::TOKEN_DMAT4X4: 
        parser->readToken(Token::TOKEN_DMAT4X4);
        type->type = BaseType::Type::BASE_TYPE_FLOAT3X4;
        break; 


        case Token::TOKEN_SAMPLER1D:
        parser->readToken(Token::TOKEN_SAMPLER1D);
        type->type = BaseType::Type::BASE_TYPE_SAMPLER1D;
        break;
        case Token::TOKEN_SAMPLER2D:
        parser->readToken(Token::TOKEN_SAMPLER2D);
        type->type = BaseType::Type::BASE_TYPE_SAMPLER2D;
        break;
        case Token::TOKEN_SAMPLER3D:
        parser->readToken(Token::TOKEN_SAMPLER3D);
        type->type = BaseType::Type::BASE_TYPE_SAMPLER3D;
        break;
        case Token::TOKEN_SAMPLERCUBE:
        parser->readToken(Token::TOKEN_SAMPLERCUBE);
        type->type = BaseType::Type::BASE_TYPE_SAMPLERCUBE;
        break;
        case Token::TOKEN_SAMPLER1DSHADOW:
        parser->readToken(Token::TOKEN_SAMPLER1DSHADOW);
        type->type = BaseType::Type::BASE_TYPE_SAMPLER1DSHADOW;
        break;
        case Token::TOKEN_SAMPLER2DSHADOW:
        parser->readToken(Token::TOKEN_SAMPLER2DSHADOW);
        type->type = BaseType::Type::BASE_TYPE_SAMPLER2DSHADOW;
        break;
        case Token::TOKEN_SAMPLERCUBESHADOW:
        parser->readToken(Token::TOKEN_SAMPLERCUBESHADOW);
        type->type = BaseType::Type::BASE_TYPE_SAMPLERCUBESHADOW;
        break;
        case Token::TOKEN_SAMPLER1DARRAY:
        parser->readToken(Token::TOKEN_SAMPLER1DARRAY);
        type->type = BaseType::Type::BASE_TYPE_SAMPLER1DARRAY;
        break;
        case Token::TOKEN_SAMPLER2DARRAY:
        parser->readToken(Token::TOKEN_SAMPLER2DARRAY);
        type->type = BaseType::Type::BASE_TYPE_SAMPLER2DARRAY;
        break;
        case Token::TOKEN_SAMPLER1DARRAYSHADOW:
        parser->readToken(Token::TOKEN_SAMPLER1DARRAYSHADOW);
        type->type = BaseType::Type::BASE_TYPE_SAMPLER1DARRAYSHADOW;
        break;
        case Token::TOKEN_SAMPLER2DARRAYSHADOW:
        parser->readToken(Token::TOKEN_SAMPLER2DARRAYSHADOW);
        type->type = BaseType::Type::BASE_TYPE_SAMPLER2DARRAYSHADOW;
        break;
        case Token::TOKEN_ISAMPLER1D:
        parser->readToken(Token::TOKEN_ISAMPLER1D);
        type->type = BaseType::Type::BASE_TYPE_ISAMPLER1D;
        break;
        case Token::TOKEN_ISAMPLER2D:
        parser->readToken(Token::TOKEN_ISAMPLER2D);
        type->type = BaseType::Type::BASE_TYPE_ISAMPLER2D;
        break;
        case Token::TOKEN_ISAMPLER3D:
        parser->readToken(Token::TOKEN_ISAMPLER3D);
        type->type = BaseType::Type::BASE_TYPE_ISAMPLER3D;
        break;
        case Token::TOKEN_ISAMPLERCUBE:
        parser->readToken(Token::TOKEN_ISAMPLERCUBE);
        type->type = BaseType::Type::BASE_TYPE_ISAMPLERCUBE;
        break;
        case Token::TOKEN_ISAMPLER1DARRAY:
        parser->readToken(Token::TOKEN_ISAMPLER1DARRAY);
        type->type = BaseType::Type::BASE_TYPE_ISAMPLER1DARRAY;
        break;
        case Token::TOKEN_ISAMPLER2DARRAY:
        parser->readToken(Token::TOKEN_ISAMPLER2DARRAY);
        type->type = BaseType::Type::BASE_TYPE_ISAMPLER2DARRAY;
        break;
        case Token::TOKEN_USAMPLER1D:
        parser->readToken(Token::TOKEN_USAMPLER1D);
        type->type = BaseType::Type::BASE_TYPE_USAMPLER1D;
        break;
        case Token::TOKEN_USAMPLER2D:
        parser->readToken(Token::TOKEN_USAMPLER2D);
        type->type = BaseType::Type::BASE_TYPE_USAMPLER2D;
        break;
        case Token::TOKEN_USAMPLER3D:
        parser->readToken(Token::TOKEN_USAMPLER3D);
        type->type = BaseType::Type::BASE_TYPE_USAMPLER3D;
        break;
        case Token::TOKEN_USAMPLERCUBE:
        parser->readToken(Token::TOKEN_USAMPLERCUBE);
        type->type = BaseType::Type::BASE_TYPE_USAMPLERCUBE;
        break;
        case Token::TOKEN_USAMPLER1DARRAY:
        parser->readToken(Token::TOKEN_USAMPLER1DARRAY);
        type->type = BaseType::Type::BASE_TYPE_USAMPLER1DARRAY;
        break;
        case Token::TOKEN_USAMPLER2DARRAY:
        parser->readToken(Token::TOKEN_USAMPLER2DARRAY);
        type->type = BaseType::Type::BASE_TYPE_USAMPLER2DARRAY;
        break;
        case Token::TOKEN_SAMPLER2DRECT:
        parser->readToken(Token::TOKEN_SAMPLER2DRECT);
        type->type = BaseType::Type::BASE_TYPE_SAMPLER2DRECT;
        break;
        case Token::TOKEN_SAMPLER2DRECTSHADOW:
        parser->readToken(Token::TOKEN_SAMPLER2DRECTSHADOW);
        type->type = BaseType::Type::BASE_TYPE_SAMPLER2DRECTSHADOW;
        break;
        case Token::TOKEN_ISAMPLER2DRECT:
        parser->readToken(Token::TOKEN_ISAMPLER2DRECT);
        type->type = BaseType::Type::BASE_TYPE_ISAMPLER2DRECT;
        break;
        case Token::TOKEN_USAMPLER2DRECT:
        parser->readToken(Token::TOKEN_USAMPLER2DRECT);
        type->type = BaseType::Type::BASE_TYPE_USAMPLER2DRECT;
        break;
        case Token::TOKEN_SAMPLERBUFFER:
        parser->readToken(Token::TOKEN_SAMPLERBUFFER);
        type->type = BaseType::Type::BASE_TYPE_SAMPLERBUFFER;
        break;
        case Token::TOKEN_ISAMPLERBUFFER:
        parser->readToken(Token::TOKEN_ISAMPLERBUFFER);
        type->type = BaseType::Type::BASE_TYPE_ISAMPLERBUFFER;
        break;
        case Token::TOKEN_USAMPLERBUFFER:
        parser->readToken(Token::TOKEN_USAMPLERBUFFER);
        type->type = BaseType::Type::BASE_TYPE_USAMPLERBUFFER;
        break;
        case Token::TOKEN_SAMPLER2DMS:
        parser->readToken(Token::TOKEN_SAMPLER2DMS);
        type->type = BaseType::Type::BASE_TYPE_SAMPLER2DMS;
        break;
        case Token::TOKEN_ISAMPLER2DMS:
        parser->readToken(Token::TOKEN_ISAMPLER2DMS);
        type->type = BaseType::Type::BASE_TYPE_ISAMPLER2DMS;
        break;
        case Token::TOKEN_USAMPLER2DMS:
        parser->readToken(Token::TOKEN_USAMPLER2DMS);
        type->type = BaseType::Type::BASE_TYPE_USAMPLER2DMS;
        break;
        case Token::TOKEN_SAMPLER2DMSARRAY:
        parser->readToken(Token::TOKEN_SAMPLER2DMSARRAY);
        type->type = BaseType::Type::BASE_TYPE_SAMPLER2DMSARRAY;
        break;
        case Token::TOKEN_ISAMPLER2DMSARRAY:
        parser->readToken(Token::TOKEN_ISAMPLER2DMSARRAY);
        type->type = BaseType::Type::BASE_TYPE_ISAMPLER2DMSARRAY;
        break;
        case Token::TOKEN_USAMPLER2DMSARRAY:
        parser->readToken(Token::TOKEN_USAMPLER2DMSARRAY);
        type->type = BaseType::Type::BASE_TYPE_USAMPLER2DMSARRAY;
        break;
        case Token::TOKEN_SAMPLERCUBEARRAY:
        parser->readToken(Token::TOKEN_SAMPLERCUBEARRAY);
        type->type = BaseType::Type::BASE_TYPE_SAMPLERCUBEARRAY;
        break;
        case Token::TOKEN_SAMPLERCUBEARRAYSHADOW:
        parser->readToken(Token::TOKEN_SAMPLERCUBEARRAYSHADOW);
        type->type = BaseType::Type::BASE_TYPE_SAMPLERCUBEARRAYSHADOW;
        break;
        case Token::TOKEN_ISAMPLERCUBEARRAY:
        parser->readToken(Token::TOKEN_ISAMPLERCUBEARRAY);
        type->type = BaseType::Type::BASE_TYPE_ISAMPLERCUBEARRAY;
        break;
        case Token::TOKEN_USAMPLERCUBEARRAY:
        parser->readToken(Token::TOKEN_USAMPLERCUBEARRAY);
        type->type = BaseType::Type::BASE_TYPE_USAMPLERCUBEARRAY;
        break;
        case Token::TOKEN_IMAGE1D:
        parser->readToken(Token::TOKEN_IMAGE1D);
        type->type = BaseType::Type::BASE_TYPE_IMAGE1D;
        break;
        case Token::TOKEN_IIMAGE1D:
        parser->readToken(Token::TOKEN_IIMAGE1D);
        type->type = BaseType::Type::BASE_TYPE_IIMAGE1D;
        break;
        case Token::TOKEN_UIMAGE1D:
        parser->readToken(Token::TOKEN_UIMAGE1D);
        type->type = BaseType::Type::BASE_TYPE_UIMAGE1D;
        break;
        case Token::TOKEN_IMAGE2D:
        parser->readToken(Token::TOKEN_IMAGE2D);
        type->type = BaseType::Type::BASE_TYPE_IMAGE2D;
        break;
        case Token::TOKEN_IIMAGE2D:
        parser->readToken(Token::TOKEN_IIMAGE2D);
        type->type = BaseType::Type::BASE_TYPE_IIMAGE2D;
        break;
        case Token::TOKEN_UIMAGE2D:
        parser->readToken(Token::TOKEN_UIMAGE2D);
        type->type = BaseType::Type::BASE_TYPE_UIMAGE2D;
        break;
        case Token::TOKEN_IMAGE3D:
        parser->readToken(Token::TOKEN_IMAGE3D);
        type->type = BaseType::Type::BASE_TYPE_IMAGE3D;
        break;
        case Token::TOKEN_IIMAGE3D:
        parser->readToken(Token::TOKEN_IIMAGE3D);
        type->type = BaseType::Type::BASE_TYPE_IIMAGE3D;
        break;
        case Token::TOKEN_UIMAGE3D:
        parser->readToken(Token::TOKEN_UIMAGE3D);
        type->type = BaseType::Type::BASE_TYPE_UIMAGE3D;
        break;
        case Token::TOKEN_IMAGE2DRECT:
        parser->readToken(Token::TOKEN_IMAGE2DRECT);
        type->type = BaseType::Type::BASE_TYPE_IMAGE2DRECT;
        break;
        case Token::TOKEN_IIMAGE2DRECT:
        parser->readToken(Token::TOKEN_IIMAGE2DRECT);
        type->type = BaseType::Type::BASE_TYPE_IIMAGE2DRECT;
        break;
        case Token::TOKEN_UIMAGE2DRECT:
        parser->readToken(Token::TOKEN_UIMAGE2DRECT);
        type->type = BaseType::Type::BASE_TYPE_UIMAGE2DRECT;
        break;
        case Token::TOKEN_IMAGECUBE:
        parser->readToken(Token::TOKEN_IMAGECUBE);
        type->type = BaseType::Type::BASE_TYPE_IMAGECUBE;
        break;
        case Token::TOKEN_IIMAGECUBE:
        parser->readToken(Token::TOKEN_IIMAGECUBE);
        type->type = BaseType::Type::BASE_TYPE_IIMAGECUBE;
        break;
        case Token::TOKEN_UIMAGECUBE:
        parser->readToken(Token::TOKEN_UIMAGECUBE);
        type->type = BaseType::Type::BASE_TYPE_UIMAGECUBE;
        break;
        case Token::TOKEN_IMAGEBUFFER:
        parser->readToken(Token::TOKEN_IMAGEBUFFER);
        type->type = BaseType::Type::BASE_TYPE_IMAGEBUFFER;
        break;
        case Token::TOKEN_IIMAGEBUFFER:
        parser->readToken(Token::TOKEN_IIMAGEBUFFER);
        type->type = BaseType::Type::BASE_TYPE_IIMAGEBUFFER;
        break;
        case Token::TOKEN_UIMAGEBUFFER:
        parser->readToken(Token::TOKEN_UIMAGEBUFFER);
        type->type = BaseType::Type::BASE_TYPE_UIMAGEBUFFER;
        break;
        case Token::TOKEN_IMAGE1DARRAY:
        parser->readToken(Token::TOKEN_IMAGE1DARRAY);
        type->type = BaseType::Type::BASE_TYPE_IMAGE1DARRAY;
        break;
        case Token::TOKEN_IIMAGE1DARRAY:
        parser->readToken(Token::TOKEN_IIMAGE1DARRAY);
        type->type = BaseType::Type::BASE_TYPE_IIMAGE1DARRAY;
        break;
        case Token::TOKEN_UIMAGE1DARRAY:
        parser->readToken(Token::TOKEN_UIMAGE1DARRAY);
        type->type = BaseType::Type::BASE_TYPE_UIMAGE1DARRAY;
        break;
        case Token::TOKEN_IMAGE2DARRAY:
        parser->readToken(Token::TOKEN_IMAGE2DARRAY);
        type->type = BaseType::Type::BASE_TYPE_IMAGE2DARRAY;
        break;
        case Token::TOKEN_IIMAGE2DARRAY:
        parser->readToken(Token::TOKEN_IIMAGE2DARRAY);
        type->type = BaseType::Type::BASE_TYPE_IIMAGE2DARRAY;
        break;
        case Token::TOKEN_UIMAGE2DARRAY:
        parser->readToken(Token::TOKEN_UIMAGE2DARRAY);
        type->type = BaseType::Type::BASE_TYPE_UIMAGE2DARRAY;
        break;
        case Token::TOKEN_IMAGECUBEARRAY:
        parser->readToken(Token::TOKEN_IMAGECUBEARRAY);
        type->type = BaseType::Type::BASE_TYPE_IMAGECUBEARRAY;
        break;
        case Token::TOKEN_IIMAGECUBEARRAY:
        parser->readToken(Token::TOKEN_IIMAGECUBEARRAY);
        type->type = BaseType::Type::BASE_TYPE_IIMAGECUBEARRAY;
        break;
        case Token::TOKEN_UIMAGECUBEARRAY:
        parser->readToken(Token::TOKEN_UIMAGECUBEARRAY);
        type->type = BaseType::Type::BASE_TYPE_UIMAGECUBEARRAY;
        break;
        case Token::TOKEN_IMAGE2DMS:
        parser->readToken(Token::TOKEN_IMAGE2DMS);
        type->type = BaseType::Type::BASE_TYPE_IMAGE2DMS;
        break;
        case Token::TOKEN_IIMAGE2DMS:
        parser->readToken(Token::TOKEN_IIMAGE2DMS);
        type->type = BaseType::Type::BASE_TYPE_IIMAGE2DMS;
        break;
        case Token::TOKEN_UIMAGE2DMS:
        parser->readToken(Token::TOKEN_UIMAGE2DMS);
        type->type = BaseType::Type::BASE_TYPE_UIMAGE2DMS;
        break;
        case Token::TOKEN_IMAGE2DMSARRAY:
        parser->readToken(Token::TOKEN_IMAGE2DMSARRAY);
        type->type = BaseType::Type::BASE_TYPE_IMAGE2DMSARRAY;
        break;
        case Token::TOKEN_IIMAGE2DMSARRAY:
        parser->readToken(Token::TOKEN_IIMAGE2DMSARRAY);
        type->type = BaseType::Type::BASE_TYPE_IIMAGE2DMSARRAY;
        break;
        case Token::TOKEN_UIMAGE2DMSARRAY:
        parser->readToken(Token::TOKEN_UIMAGE2DMSARRAY);
        type->type = BaseType::Type::BASE_TYPE_UIMAGE2DMSARRAY;
        break;
        case Token::TOKEN_ATOMIC_UINT:
        parser->readToken(Token::TOKEN_ATOMIC_UINT);
        type->type = BaseType::Type::BASE_TYPE_ATOMIC_UINT;
        break;
        case Token::TOKEN_STRING:
        parser->readToken(Token::TOKEN_STRING);
        type->type = BaseType::Type::BASE_TYPE_STRING;
        break;
        default:
        if(parser->scope->getStructDefinition(parser->currentToken()->value) == nullptr) {
            printf("Undefined type '%s' at line '%u'!\n", parser->currentToken()->value, parser->currentToken()->line);
            exit(-1);
        }
        parser->readToken(Token::TOKEN_IDENTIFIER);
        type->type = BaseType::Type::BASE_TYPE_USER_DEFINED;
    }

    return type;
}

bool isDeclaration(Parser* parser) {
    return parser->currentToken()->type == Token::TOKEN_IDENTIFIER || 
    (parser->currentToken()->type >= Token::TOKEN_TYPES_START
        && parser->currentToken()->type <= Token::TOKEN_TYPES_END);
}

}

