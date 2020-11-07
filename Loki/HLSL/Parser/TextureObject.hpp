#ifndef TEXTURE_OBJECT
#define TEXTURE_OBJECT

#include "AST.hpp"
#include "Parser.hpp"

namespace HLSL {

enum TextureObjectType {
    TEXTURE_OBJECT_BUFFER,
    TEXTURE_OBJECT_TEXTURE1D,
    TEXTURE_OBJECT_TEXTURE1D_ARRAY,
    TEXTURE_OBJECT_TEXTURE2D,
    TEXTURE_OBJECT_TEXTURE2D_ARRAY,
    TEXTURE_OBJECT_TEXTURE3D,
    TEXTURE_OBJECT_TEXTURECUBE,
    TEXTURE_OBJECT_TEXTURECUBE_ARRAY,
    TEXTURE_OBJECT_OBJECT2_TYPE,
    TEXTURE_OBJECT_TEXTURE2DMS,
    TEXTURE_OBJECT_TEXTURE2DMS_ARRAY,
};

struct ASTTextureObject: AST {
    explicit ASTTextureObject();
};

// Object2 [<Type, Samples>] Name;
ASTTextureObject* parseTextureObject(Parser* parser);

}

#endif